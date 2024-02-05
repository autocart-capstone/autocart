
#include "sound_transmit.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  digitalWrite(LED_BUILTIN, 1);
  
  setup_i2s_sound_out();
}

bool first = true;
int16_t sample = 0;
byte buffer[64];

void loop() {
  int read = Serial.readBytes(buffer, 64);
for (int i = 0; i < read; i++) {
    if (first) {
      sample = buffer[i];
    } else {
      sample |= buffer[i] <<8;
      transmit_sample(sample);
    }
    first = !first;
  }
}
