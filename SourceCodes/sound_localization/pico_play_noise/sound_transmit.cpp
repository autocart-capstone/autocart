#include "sound_transmit.h"
#include <I2S.h>
#include "src/sound_samples/sound_samplesA.h"
//#include "src/sound_samples/sound_samplesC.h"

I2S i2s_out(OUTPUT);
const int sampleRate = 48000;

size_t sound_out_ind = SOUND_SAMPLES_LEN; // silence at first
uint64_t last_interrupt_ticks = 0;        // Number of CPU cycles since the last "onTransmit" interrupt
uint32_t samples_to_skip = 0;             // amount of samples to skip before sending samples

void onTransmit()
{
  last_interrupt_ticks = rp2040.getCycleCount64();
  while (true)
  {
    int32_t sample;
    if (sound_out_ind < SOUND_SAMPLES_LEN && samples_to_skip == 0)
    {
      // sample = sound | sound << 16; // 16 bits for L channel, 16 bits for R channel
      sample = sound_samples[sound_out_ind] << 16; // sample is 32-bit audio, shift 16 bit sound to most significant bits of 32-bit sample
      //sample /= 16;                                // make sound less loud
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
      sound_out_ind %= SOUND_SAMPLES_LEN; // Repeat sound when done
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
  uint64_t tick_diff = rp2040.getCycleCount64() - last_interrupt_ticks;
  // Rationale:
  // With the DMA triple-buffering, we always submit a certain amount of samples ahead of time
  // Start transmitting audio after having skipped as many future samples submission as we are currently into the buffer
  // Ex: (s means sample already submitted, e is not submitted, [] is a buffer)
  // [s s s s] [s s s s] [s s s s] [e e e e]
  //    ^                             ^
  //    cur time                      start transmitting here
  // want to start transmitting at cur time, but empty samples (0s) already submitted for the next few buffer. 
  // In the next available buffer, delay sound transmission by 2 samples
  // This is for consistency, this way we always transmit x samples late (x=numbuffers*numsamplesinbuffer).
  float skip = ((float)tick_diff * ((float)sampleRate / (float)rp2040.f_cpu()));
  samples_to_skip = (uint32_t)skip;
  //Serial.printf("delaying by %i samples\n", samples_to_skip);
}

/* bool is_done_transmitting_sound()
{
  return sound_out_ind >= SOUND_SAMPLES_LEN;
} */
