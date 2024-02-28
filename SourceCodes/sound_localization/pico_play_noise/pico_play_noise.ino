#include "sound_transmit.h"
#include "transceiver_speaker.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  rp2040.enableDoubleResetBootloader();

  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  digitalWrite(LED_BUILTIN, 1);

  setupRfm69();
  setup_i2s_sound_out();
  set_sound_divider(64);
  waitForTimeSync();
  waitForStartSignal();
  start_transmitting_sound(); // This will play the sound in a loop
}

void loop() {}
