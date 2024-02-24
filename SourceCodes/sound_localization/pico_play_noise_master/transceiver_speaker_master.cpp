#include <RFM69.h>
#include <SPI.h>
#include "transceiver_speaker_master.h"

RFM69 radio = RFM69(CS_PIN, INTRPT_PIN);
String receivedData = "";

void setupRfm69() {
  bool initAntennaSuccess = radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  if (initAntennaSuccess) {
    Serial.printf("Node %d ready\n", MYNODEID);
  } else {
    Serial.printf("Failed to initialize Antenna Node %d\n", MYNODEID);
    while (1); // do nothing
  }
  // Set bit rate to 250kbps
  radio.writeReg(0x03, 0x00);
  radio.writeReg(0x04, 0x80);
  radio.setHighPower(); // Always use this for RFM69HCW
}

void sendPing(int target, char* msg) {
  Serial.printf("Sending ping to node %d\n", target);
//  Serial.printf("size of message: %d", strlen(msg));
  if (USEACK) {
    bool success = radio.sendWithRetry(target, msg, strlen(msg), 0, 5); //last 2 arguments: 0 retries, 2ms wait time for ACK
    if (success) {
      Serial.printf("ACK received!\n");
    } else {
      Serial.printf("no ACK received :(\n");
      //        sendPing(target);
    }
  } else {
    //Serial.printf("Sending without ack\n");
    // radio.send(target, "m", 1); //send character "m" (length 1) to TONODEID
    //Serial.printf("Sent!\n");
  }
}

void receivePing() {
  // Serial.println("Waiting for ping from receiver (microphone)...");
  while(!radio.receiveDone()){
    // do nothing
  }

  Serial.print("Ping received from node ");
  Serial.print(radio.SENDERID, DEC);
  Serial.print(": [");

//  Serial.println(radio.DATALEN);
  for (byte i = 0; i < radio.DATALEN; i++) {
    Serial.printf("%c", (char)radio.DATA[i]);
    receivedData += (char)radio.DATA[i];
  }
  Serial.println("]");
  
  // Send an ACK if requested.
  if (radio.ACKRequested()) {
    radio.sendACK();
    Serial.printf("ACK sent\n");
  }
}

void doTimeSync() {
  unsigned long masterTimeBegin; //4 bytes
  masterTimeBegin = micros();

  if (BROADCAST) {  
    char buf[100];
    sprintf(buf, "%lu", masterTimeBegin);
    Serial.printf("master start time: %s\n", buf);
    sendPing(TOALLNODE, buf);
  }
  else {
    for (int i = 1; i <= NUM_PICO; i++) {
      char buf[60];
      sprintf(buf, "%lu", masterTimeBegin);
      Serial.printf("master start time: %s\n", buf);
      sendPing(i, buf);
    }
  }
}

void waitForStartSignal() {
  unsigned long waitMs = 2000;
  unsigned long startTime = millis();
  while ( (millis() - startTime) != waitMs ) {
    Serial.print('.');
  }
  Serial.println();  
}
