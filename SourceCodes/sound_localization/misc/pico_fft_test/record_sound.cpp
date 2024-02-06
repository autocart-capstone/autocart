#include "src/kissfft/kiss_fftr.h"
#include "src/sound_correlation/sound_correlation0.h"
#include "src/sound_samples/sound_samples0.h"
#include <math.h>
#include <Arduino.h>

kiss_fftr_cfg kissfft_cfg_fwd = NULL;
kiss_fftr_cfg kissfft_cfg_bwd = NULL;

void setup_sound_in() {
  kissfft_cfg_fwd = kiss_fftr_alloc(FFT_SIZE, false, NULL, NULL);
  if (!kissfft_cfg_fwd) {
    Serial.println("Failed to initialize kissfft fwd!");
    while (1); // do nothing
  }
  kissfft_cfg_bwd = kiss_fftr_alloc(FFT_SIZE, true, NULL, NULL);
  if (!kissfft_cfg_bwd) {
    Serial.println("Failed to initialize kissfft bwd!");
    while (1); // do nothing
  }
  int32_t *recorded_sound_int = (int32_t *)recorded_sound;
  for (int i = 0; i < SOUND_SAMPLES_LEN; i++) {
    recorded_sound_int[i+300] = ((int32_t)sound_samples[i]) << 6;
  }
  Serial.printf("Free heap: %i (bytes)", rp2040.getFreeHeap());
}

int32_t correlation_int[CONV_BUFFER_SIZE];
kiss_fft_cpx* correlation_fft = (kiss_fft_cpx*)correlation_int;

int correlate_sound()
{
    // FFT in-place the recorded sound
  int pre_fft = micros();

  int32_t *recorded_sound_int = (int32_t *)recorded_sound;
  kiss_fft_cpx *recorded_sound_fft = (kiss_fft_cpx *)recorded_sound;
  kiss_fftr(kissfft_cfg_fwd, recorded_sound_int, recorded_sound_fft);

  Serial.printf("fft took: %i micros\n", micros()-pre_fft);

  int pre_mult = micros();
  kiss_fft_cpx *sound_samples_fft_conj_cmplx = (kiss_fft_cpx *)sound_samples_fft_conj;
  for (int i = 0; i < FFT_SIZE/2+1; i++)
  {
    correlation_fft[i].r = recorded_sound_fft[i].r * sound_samples_fft_conj_cmplx[i].r - recorded_sound_fft[i].i * sound_samples_fft_conj_cmplx[i].i;
    correlation_fft[i].i = recorded_sound_fft[i].r * sound_samples_fft_conj_cmplx[i].i + recorded_sound_fft[i].i * sound_samples_fft_conj_cmplx[i].r;
  }

  Serial.printf("multiplication took: %i micros\n", micros()-pre_mult);
  // IFFT in-place
  int pre_ifft = micros();
  kiss_fftri(kissfft_cfg_bwd, correlation_fft, correlation_int);
  Serial.printf("ifft took: %i micros\n", micros()-pre_ifft);
  
  // get index of max correlation
  int pre_find_max = micros();
  int max_ind = 0;
  int32_t max_val = abs(correlation_int[0]);
  for (int i = 1; i < VALID_CORRELATION_LENGTH; i++)
  {
    if (abs(correlation_int[i]) > max_val)
    {
      max_val = abs(correlation_int[i]);
      max_ind = i;
    }
  }
  Serial.printf("find max took: %i micros\n", micros()-pre_find_max);
  Serial.printf("max ind: %i\n", max_ind);
  Serial.printf("bytes\n");
  Serial.printf("%i\n", VALID_CORRELATION_LENGTH*4);
  Serial.write((byte *)correlation_int, VALID_CORRELATION_LENGTH*4);
  return max_ind;
}

void print_recorded_sound_to_serial() {
  //Serial.printf("bytes\n");
  //Serial.printf("%i\n", NUMBER_OF_SAMPLES_TO_RECORD);
  //Serial.write((byte*)recorded_sound, NUMBER_OF_SAMPLES_TO_RECORD*4); // 32-bit per float, 4 bytes
}
