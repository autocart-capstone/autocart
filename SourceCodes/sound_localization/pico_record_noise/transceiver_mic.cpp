#include <RFM69.h>
#include <SPI.h>
#include "transceiver_mic.h"

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
  radio.writeReg(0x03, 0x00);
  radio.writeReg(0x04, 0x80);
  radio.setHighPower(); // Always use this for RFM69HCW

  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, LOW);

  pinMode(INTRPT_PIN, INPUT);
  digitalWrite(INTRPT_PIN, LOW);
}

void sendPing(int target) {
  //Serial.printf("\nSending ping to node %d\n", target);

  if (USEACK) {
    byte msg = "abcdef";
    bool success = radio.sendWithRetry(target, &msg, strlen(msg), 0, 2); //last 2 arguments: 0 retries, 2ms wait time for ACK

    if (success) {
        //Serial.printf("ACK received!\n");
    } else {
        //Serial.printf("no ACK received :(\n");
        sendPing(target);
    }
  } else {
    //Serial.printf("Sending without ack\n");
    // radio.send(target, "m", 1); //send character "m" (length 1) to TONODEID
    //Serial.printf("Sent!\n");
  }
}

/**
 * NOT USED!
*/
void receivePing() {
  // Serial.printf("Waiting for ping from transmitter (speaker) to start listening...\n");
  while (!radio.receiveDone()) {
    // do nothing
  }

  // Serial.printf("Ping received from node %d: [", radio.SENDERID);

  // for (byte i = 0; i < radio.DATALEN; i++)
  //   Serial.printf("%c", (char)radio.DATA[i]);
  // Serial.printf("]\n");

  // Send an ACK if requested.
  if (radio.ACKRequested()) {
    radio.sendACK();
    // Serial.printf("ACK sent\n");
  }
}
