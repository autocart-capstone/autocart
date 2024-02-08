#include <RFM69.h>
#include <SPI.h>
#include "transceiver_speaker.h"

RFM69 radio = RFM69(CS_PIN, INTRPT_PIN);

void setup_rfm69() {
  bool init_ant_success = radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  if (init_ant_success) {
    Serial.printf("Node %d ready\n", MYNODEID);
  } else {
    Serial.printf("Failed to initialize Antenna Node %d\n", MYNODEID);
    while (1); // do nothing
  }
  // Set bit rate to 250kbps
  radio.writeReg(0x03,0x00);
  radio.writeReg(0x04,0x80);
  radio.setHighPower(); // Always use this for RFM69HCW

  pinMode(CS_PIN,OUTPUT);
  digitalWrite(CS_PIN,LOW);

  pinMode(INTRPT_PIN,INPUT);
  digitalWrite(INTRPT_PIN,LOW);
}

/**
 * NOT USED!
*/
void sendPing() {
  // Serial.printf("Sending ping to node %d\n", TONODEID);
  if (USEACK) {
    bool success = radio.sendWithRetry(TONODEID, "s", 1, 0, 10); // 0 retries, 4 ms wait time
    // if (success) {
    //     Serial.printf("ACK received!\n");
    // } else {
    //     Serial.printf("no ACK received :(\n");
    //     // sendPing();
    // }
  }
  else {
    // Serial.printf("Sending without ack\n");
    // radio.send(TONODEID, "g", 1);
    // Serial.printf("Sent!\n");
  }
}

void receivePing() {
  // Serial.println("Waiting for ping from receiver (microphone)...");
  while(!radio.receiveDone()){
    // do nothing
  }

  // Serial.print("Ping received from node ");
  // Serial.print(radio.SENDERID, DEC);
  // Serial.print(": [");

  // Send an ACK if requested.
  if (radio.ACKRequested()) {
    radio.sendACK();
    // Serial.printf("ACK sent\n");
  }
}
