#include <I2S.h>
#include "record_sound.h"

I2S i2s_in(INPUT);

const int sampleRate = 48000;

void setup_sound_in() {
  i2s_in.setBCLK(12); // WS / LRCLK has to be 13, BCLK+1
  i2s_in.setDATA(11);
  i2s_in.setBitsPerSample(32);
  i2s_in.setBuffers(18, 0, 0); // 3 buffers (minimum), 0 buffer length (it will set the default), 0 silence sample
 
  if (!i2s_in.begin(48000)) {
    Serial.println("Failed to initialize I2S in!");
    while (1); // do nothing
  }
}

int16_t get_sample() {
  int32_t l, r;
  i2s_in.read32(&l, &r);
  int16_t good_bits = ((l << 4) & 0xFFFF0000) >> 16;
  return good_bits;
}

int32_t get_full_sample() {
  int32_t l, r;
  i2s_in.read32(&l, &r);
  return l;
}
