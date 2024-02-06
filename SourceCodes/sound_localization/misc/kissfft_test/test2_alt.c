
#include "kiss_fftr.h"
#include "sound_correlation0.h"
#include "sound_samples0.h"
#include <math.h>
#include <stdio.h>
#include <limits>

const int sampleRate = 48000;

kiss_fftr_cfg kissfft_forw;
kiss_fftr_cfg kissfft_back;

void setup()
{
  kissfft_forw = kiss_fftr_alloc(FFT_SIZE, false, NULL, NULL);
  kissfft_back = kiss_fftr_alloc(FFT_SIZE, true, NULL, NULL);
}

int correlate_sound()
{
  kiss_fft_cpx *sound_samples_fft_cmplx = (kiss_fft_cpx *)sound_samples_fft;

  kiss_fftr(kissfft_forw, (int32_t *)sound_samples_fft, sound_samples_fft_cmplx);

  for (int i = 0; i < FFT_SIZE / 2 + 1; i++)
  {
    // take conjugate
    sound_samples_fft_cmplx[i].i *= -1;
    // printf("%08X %08X\n", sound_samples_fft_cmplx[i].r, sound_samples_fft_cmplx[i].i);
  }

  // FFT in-place the recorded sound
  int32_t *recorded_sound_int = (int32_t *)recorded_sound;
  kiss_fft_cpx *recorded_sound_fft = (kiss_fft_cpx *)recorded_sound_int;
  kiss_fftr(kissfft_forw, recorded_sound_int, recorded_sound_fft);

  int32_t correlation_int[CONV_BUFFER_SIZE];
  kiss_fft_cpx *correlation = (kiss_fft_cpx *)correlation_int;
  for (int i = 0; i < FFT_SIZE / 2 + 1; i++)
  {
    correlation[i].r = recorded_sound_fft[i].r * sound_samples_fft_cmplx[i].r - recorded_sound_fft[i].i * sound_samples_fft_cmplx[i].i;
    correlation[i].i = recorded_sound_fft[i].r * sound_samples_fft_cmplx[i].i + recorded_sound_fft[i].i * sound_samples_fft_cmplx[i].r;
  }

  // IFFT in-place
  kiss_fftri(kissfft_back, correlation, correlation_int);

  // get index of max correlation
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
  for (int i = 1; i < VALID_CORRELATION_LENGTH; i++)
  {
    printf("%i\n", correlation_int[i]);
  }

  return max_ind;
}

int main(int argc, char const *argv[])
{
  setup();
  for (int i = 0; i < SOUND_SAMPLES_LEN; i++)
  {
    recorded_sound[i + 300] = sound_samples[i] << 6;
  }
  int index = correlate_sound();
  printf("index: %i\n", index);
  return 0;
}
