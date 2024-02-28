#include <RFM69.h>
#include <SPI.h>
#include "transceiver_speaker.h"

RFM69 radio = RFM69(CS_PIN, INTRPT_PIN);
String receivedData = "";
unsigned long clockAdjust = 0;

void setupRfm69() {
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
}

void sendPing(int target, char* msg) {
  Serial.printf("Sending ping to node %d\n", TONODEID);
  if (USEACK) {
    bool success = radio.sendWithRetry(target, msg, strlen(msg), 0, 2); //last 2 arguments: 0 retries, 2ms wait time for ACK
     if (success) {
         Serial.printf("ACK received!\n");
     } else {
         Serial.printf("no ACK received :(\n");
     }
  } else {
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

  Serial.print("Ping received from node ");
  Serial.print(radio.SENDERID, DEC);
  Serial.print(": [");

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

void waitForTimeSync() {
  unsigned long masterTimeBegin;
  unsigned long timeDiff;
  unsigned long nodeTimeBegin = micros();
  Serial.printf("my node start time: %lu\n", nodeTimeBegin);
  
  receivePing();
  // Convert received data to unsigned long int
  char rcvbuf[receivedData.length() + 1];
  receivedData.toCharArray(rcvbuf, receivedData.length() + 1);
  rcvbuf[receivedData.length()] = '\0';
  masterTimeBegin = strtoul(rcvbuf, NULL, 10);
  Serial.printf("master start time: %lu\n", masterTimeBegin);
  
  // Get time difference
  timeDiff = nodeTimeBegin - masterTimeBegin;
  Serial.printf("time difference %d\n", timeDiff);
  // Save this time difference value to adjust clock later
  clockAdjust = timeDiff / 1000;  // change from micros to millis
}

void waitForStartSignal() {
  unsigned long waitMs = 2000;
  unsigned long waitBegin = millis() + clockAdjust;
  while ( ((millis() + clockAdjust) - waitBegin) != waitMs ) {
    Serial.print(".");
  }
  Serial.println();
}
