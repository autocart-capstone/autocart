#include "transceiver_mic.h"
#include "record_sound.h"

const int num_speaker = 4;
int target_speaker = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  rp2040.enableDoubleResetBootloader();
  
  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up
  digitalWrite(LED_BUILTIN, 1);
  
  Serial.printf("Started! Clock speed: %i\n", rp2040.f_cpu());
  setup_rfm69();
  setup_sound_in();
  // receive();
}

// void receive() {
//   waiting_for_transmitter = false;
//   receivePing();
//   start_recording_sound();
// }

void loop() {
  // target_speaker = (target_speaker % num_speaker) + 1;

  sendPing(2);
  start_recording_sound();
  
  while (!is_done_recording_sound()); // delay until done recording sound

  print_recorded_sound_to_serial();
  // sendPing();
  // receive();
  //delay(1000);
}
