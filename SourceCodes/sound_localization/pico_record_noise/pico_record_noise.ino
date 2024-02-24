#include "record_sound.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  digitalWrite(LED_BUILTIN, 1);
  
  Serial.printf("Started! Clock speed: %i\n", rp2040.f_cpu());
  setup_sound_in();
}

void loop() {
  start_recording_sound();
  while (!is_done_recording_sound()); // delay until done recording sound
  print_recorded_sound_to_serial();
}
