#include <I2S.h>
#include "pffft.h"
#include "sound_correlation.h"
#include <math.h> // fabsf
#include <limits> // max int

I2S i2s_in(INPUT);

const int sampleRate = 48000;

size_t sound_in_ind = NUMBER_OF_SAMPLES_TO_RECORD; // start disabled

uint32_t last_interrupt = 0;
uint32_t samples_to_skip = 0;

void onReceive()
{
  last_interrupt = micros();
  while (true)
  {
    int32_t l, r;
    int read_successful = i2s_in.read(&l, false);
    if (!read_successful)
    {
      break;
    }
    i2s_in.read(&r, false);
    int16_t good_bits = ((l << 4) & 0xFFFF0000) >> 16; // This seems to sound the best? Trial and error

    if (sound_in_ind < NUMBER_OF_SAMPLES_TO_RECORD && samples_to_skip == 0)
    {
      recorded_sound[sound_in_ind] = (float)good_bits / fabsf((float)std::numeric_limits<int16_t>::min());
      sound_in_ind += 1;
    }
    else if (samples_to_skip > 0)
    {
      samples_to_skip -= 1;
    }
  }
}

PFFFT_Setup *pffft_setup;

void setup_sound_in()
{
  i2s_in.setBCLK(12); // WS / LRCLK has to be 13, BCLK+1
  i2s_in.setDATA(11);
  i2s_in.setBitsPerSample(32);
  i2s_in.onReceive(onReceive);
  i2s_in.setBuffers(3, 0, 0); // 3 buffers (minimum), 0 buffer length (it will set the default), 0 silence sample

  if (!i2s_in.begin(48000))
  {
    Serial.println("Failed to initialize I2S in!");
    while (1)
      ; // do nothing
  }
  pffft_setup = pffft_new_setup(FFT_SIZE, PFFFT_REAL);
  if (!pffft_setup)
  {
    Serial.println("Failed to initialize pffft!");
    while (1)
      ; // do nothing
  }
}
void start_recording_sound()
{
  sound_in_ind = 0;
  float time_dif = micros() - last_interrupt;
  float skip = (time_dif * ((float)sampleRate / 1000000));
  samples_to_skip = (uint32_t)skip;
}

bool is_done_recording_sound()
{
  return sound_in_ind >= NUMBER_OF_SAMPLES_TO_RECORD;
}

int correlate_sound()
{
  // FFT in-place the recorded sound
  pffft_transform_ordered(pffft_setup, recorded_sound, recorded_sound, NULL, PFFFT_FORWARD);
  // For a real FFT (see https://en.wikipedia.org/wiki/Fast_Fourier_transform#FFT_algorithms_specialized_for_real_or_symmetric_data)
  // The 0th index freq and Nth have 0 imaginary component
  // Pffft took advantage of this and packed the Nth frequency into the 0th indexe's imaginary component
  // First entry (first two floats) is equal to F(0)+i*F(n/2+1)
  // Put this back to how its supposed to be, first entry F(0)+i*0 and Nth F(N)+i*0

  // recorded_sound is actually NUMBER_OF_SAMPLES_TO_RECORD+2 (CONV_BUFFER_SIZE) long
  recorded_sound[CONV_BUFFER_SIZE - 2] = recorded_sound[1];
  recorded_sound[1] = 0;

  float correlation[CONV_BUFFER_SIZE];
  for (int i = 0; i < CONV_BUFFER_SIZE; i += 2)
  {
    // complex multiplication
    int r_ind = i;
    int i_ind = i + 1;
    correlation[r_ind] = recorded_sound[r_ind] * sound_samples_fft_conj[r_ind] - recorded_sound[i_ind] * sound_samples_fft_conj[i_ind];
    correlation[i_ind] = recorded_sound[r_ind] * sound_samples_fft_conj[i_ind] + recorded_sound[i_ind] * sound_samples_fft_conj[r_ind];
  }

  // Redo the packing
  correlation[1] = correlation[CONV_BUFFER_SIZE - 2];
  // IFFT in-place
  pffft_transform_ordered(pffft_setup, correlation, correlation, NULL, PFFFT_BACKWARD);

  // get index of max correlation
  int max_ind = 0;
  float max_val = fabsf(correlation[0]);
  for (int i = 1; i < VALID_CORRELATION_LENGTH; i++)
  {
    if (fabsf(correlation[i]) > max_val)
    {
      max_val = fabsf(correlation[i]);
      max_ind = i;
    }
  }
  return max_ind;
}

void print_recorded_sound_to_serial()
{
  Serial.printf("bytes\n");
  Serial.printf("%i\n", NUMBER_OF_SAMPLES_TO_RECORD);
  Serial.write((byte *)recorded_sound, NUMBER_OF_SAMPLES_TO_RECORD * 4); // 32-bit per float, 4 bytes
}
