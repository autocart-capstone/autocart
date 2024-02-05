#include "kiss_fftr.h"
#include "sound_correlation0.h"
#include <math.h>
#include "Arduino.h"

kiss_fftr_cfg kissfft_forw;
kiss_fftr_cfg kissfft_back;

void setup_sound_in() {
  kissfft_forw = kiss_fftr_alloc(FFT_SIZE, false, NULL, NULL);
  kissfft_back = kiss_fftr_alloc(FFT_SIZE, true, NULL, NULL);
  if (!kissfft_forw || !kissfft_back) {
    Serial.println("Failed to initialize kissfft!");
    while (1); // do nothing
  }
}

int correlate_sound()
{
  // FFT in-place the recorded sound
  int pre_fft = micros();

  int32_t *recorded_sound_int = (int32_t *)recorded_sound;
  kiss_fft_cpx *recorded_sound_fft = (kiss_fft_cpx *)recorded_sound_int;
  kiss_fftr(kissfft_forw, recorded_sound_int, recorded_sound_fft);

  Serial.printf("fft took: %i micros\n", micros()-pre_fft);

  int pre_mult = micros();
  int32_t correlation_int[CONV_BUFFER_SIZE];
  kiss_fft_cpx *correlation = (kiss_fft_cpx *)correlation_int;
  kiss_fft_cpx *sound_samples_fft_conj_cmplx = (kiss_fft_cpx *)sound_samples_fft_conj;
  for (int i = 0; i < FFT_SIZE/2+1; i++)
  {
    correlation[i].r = recorded_sound_fft[i].r * sound_samples_fft_conj_cmplx[i].r - recorded_sound_fft[i].i * sound_samples_fft_conj_cmplx[i].i;
    correlation[i].i = recorded_sound_fft[i].r * sound_samples_fft_conj_cmplx[i].i + recorded_sound_fft[i].i * sound_samples_fft_conj_cmplx[i].r;
  }

  Serial.printf("multiplication took: %i micros\n", micros()-pre_mult);

  // IFFT in-place
  int pre_ifft = micros();
  kiss_fftri(kissfft_back, correlation, correlation_int);
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
  //Serial.printf("bytes\n");
  //Serial.printf("%i\n", NUMBER_OF_SAMPLES_TO_RECORD);
  //Serial.write((byte *)correlation, NUMBER_OF_SAMPLES_TO_RECORD * 4); // 32-bit per float, 4 bytes
  return max_ind;
}

void print_recorded_sound_to_serial() {
  //Serial.printf("bytes\n");
  //Serial.printf("%i\n", NUMBER_OF_SAMPLES_TO_RECORD);
  //Serial.write((byte*)recorded_sound, NUMBER_OF_SAMPLES_TO_RECORD*4); // 32-bit per float, 4 bytes
}
