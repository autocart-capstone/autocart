#include "transceiver_speaker_master.h"
#include "sound_transmit.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  rp2040.enableDoubleResetBootloader();
  
  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  digitalWrite(LED_BUILTIN, 1);
  
//  Serial.printf("Started! Clock speed: %i\n", rp2040.f_cpu());
  setupRfm69();
  setup_i2s_sound_out();
  sendBroadcast();
  unsigned long waitMs = 2000;
  unsigned long waitBegin = millis() + clockAdjust;
  while ( ((millis() + clockAdjust) - waitBegin) != waitMs ) {
    Serial.print(".");
  }
  Serial.println();
  // This will play the sound in a loop
  start_transmitting_sound();
}

void loop() {}
