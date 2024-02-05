#include "transceiver_mic.h"
#include "record_sound.h"

bool waiting_for_transmitter = true;
const int num_speaker = 4;
int target_speaker = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);

  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  delay(3000); // delay long enough for serial to get set up

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
  waiting_for_transmitter = false;

  if (waiting_for_transmitter || !is_done_recording_sound()) { //if not done listening for the sound
    return; // keep looping
  }

  print_recorded_sound_to_serial();
  // sendPing();
  waiting_for_transmitter = true;
  // receive();
  delay(1000);
}
