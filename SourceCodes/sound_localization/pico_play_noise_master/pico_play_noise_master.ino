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
  
  String initial_div = "128";
  sendBroadcast(initial_div);
}

void loop() {
  if (Serial.available() > 0){
    String in = Serial.readStringUntil('\n');
    in.trim();
    
    sendBroadcast(in);
  }
}
