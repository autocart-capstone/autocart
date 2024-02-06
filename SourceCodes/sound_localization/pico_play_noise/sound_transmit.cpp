#include "sound_transmit.h"
#include <I2S.h>
#include "sound_samples.h"

I2S i2s_out(OUTPUT);
const int sampleRate = 48000;

size_t sound_out_ind = SOUND_SAMPLES_LEN; // silence at first
uint32_t last_interrupt_ticks = 0;              // Time in microseconds of the last "onTransmit" interrupt
uint32_t samples_to_skip = 0;             // amount of samples to skip before sending samples

void onTransmit()
{
  last_interrupt_ticks = micros();
  while (true)
  {
    int32_t sample;
    if (sound_out_ind < SOUND_SAMPLES_LEN && samples_to_skip == 0)
    {
      // sample = sound | sound << 16; // 16 bits for L channel, 16 bits for R channel
      sample = sound_samples[sound_out_ind] << 16; // sample is 32-bit audio, shift 16 bit sound to most significant bits of 32-bit sample
      sample /= 16;                                // make sound less loud
    }
    else
    {
      sample = 0;
    }

    int write_succesful = i2s_out.write(sample, false); // L channel
    if (!write_succesful)
    {
      break;
    }
    i2s_out.write(sample, false); // R channel

    if (sound_out_ind < SOUND_SAMPLES_LEN && samples_to_skip == 0)
    {
      sound_out_ind += 1;
    }
    else if (samples_to_skip > 0)
    {
      samples_to_skip -= 1;
    }
  }
}

void setup_i2s_sound_out()
{
  i2s_out.setBCLK(20); // WS / LRCLK has to be 21, BCLK+1
  i2s_out.setDATA(22);
  i2s_out.setBitsPerSample(32);
  i2s_out.onTransmit(onTransmit);
  i2s_out.setBuffers(3, 0, 0); // 3 buffers (minimum), 0 buffer length (it will set the default), 0 silence sample

  if (!i2s_out.begin(sampleRate))
  {
    Serial.println("Failed to initialize I2S out!");
    while (1)
      ; // do nothing
  }
}
void start_transmitting_sound()
{
  sound_out_ind = 0;
  float time_dif = micros() - last_interrupt_ticks;
  float skip = (time_dif * ((float)sampleRate / 1000000));
  // Serial.println(skip);
  samples_to_skip = (uint32_t)skip;
}

bool is_done_transmitting_sound()
{
  return sound_out_ind >= SOUND_SAMPLES_LEN;
}
