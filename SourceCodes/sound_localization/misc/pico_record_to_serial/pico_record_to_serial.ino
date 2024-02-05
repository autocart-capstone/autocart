
#include "record_sound.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  digitalWrite(LED_BUILTIN, 1);
  
  setup_sound_in();
}

bool first = true;
size_t buffer_ind = 0;
byte buffer[64];

void loop() {
  if (Serial.available() > 0) {
    char r = Serial.read();
    if (r == 'r') {
      for (int i = 48000*2*5; i > 0; i--) {
        int16_t sample = get_sample();
        buffer[buffer_ind] = (sample >> 0) & 0xFF;
        buffer_ind++;
        buffer[buffer_ind] = (sample >> 8) & 0xFF;
        buffer_ind++;
        //buffer[buffer_ind] = (sample >> 16) & 0xFF;
        //buffer_ind++;
        //buffer[buffer_ind] = (sample >> 24) & 0xFF;
        //buffer_ind++;
        if (buffer_ind == 64) {
          Serial.write(buffer, 64);
          buffer_ind = 0;
        }
      }
      if (buffer_ind > 0) {
        Serial.write(buffer, buffer_ind);
      }
    }
  }
}
