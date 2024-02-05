#include "sound_transmit.h"
#include <I2S.h>


I2S i2s_out(OUTPUT);
const int sampleRate = 48000; 

void setup_i2s_sound_out() {
  i2s_out.setBCLK(20); // WS / LRCLK has to be 21, BCLK+1
  i2s_out.setDATA(22);
  i2s_out.setBitsPerSample(32);
  i2s_out.setBuffers(18, 0, 0); // 3 buffers (minimum), 0 buffer length (it will set the default), 0 silence sample

  if (!i2s_out.begin(sampleRate)) {
    Serial.println("Failed to initialize I2S out!");
    while (1); // do nothing
  }
}

void transmit_sample(uint16_t s) {
  int32_t sample = s << 16;
   
  i2s_out.write32(sample, sample); // write to both L and R channel
}
