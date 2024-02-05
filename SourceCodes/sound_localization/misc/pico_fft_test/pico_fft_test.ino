#include "record_sound.h"

void setup() {
 
  digitalWrite(LED_BUILTIN, 1);

  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  //Serial.println("Ok!");

  setup_sound_in();
  Serial.printf("correlation start\n");
  int start = micros();
  correlate_sound();
  int end = micros();
  Serial.printf("correlation end, took: %i microseconds\n", end-start);
}

void loop() {
  
}
