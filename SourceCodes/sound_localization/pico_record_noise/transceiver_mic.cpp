#include <RFM69.h>
#include <SPI.h>
#include "transceiver_mic.h"

uint32_t counter = 0;
float total_RTT = 0;
std::vector<int> counter_array;
std::vector<int> RTT_array;

RFM69 radio = RFM69(CS_PIN, INTRPT_PIN);

void setup_rfm69() {
  bool init_ant_success = radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  if (init_ant_success) {
    Serial.printf("Node %d ready\n", MYNODEID);
  } else {
    Serial.printf("Failed to initialize Antenna Node %d\n", MYNODEID);
    while (1); // do nothing
  }
  // Set bit rate
  radio.writeReg(0x03, 0x00);
  radio.writeReg(0x04, 0x80);
  radio.setHighPower(); // Always use this for RFM69HCW

  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, LOW);

  pinMode(INTRPT_PIN, INPUT);
  digitalWrite(INTRPT_PIN, LOW);
}

void sendPing(int target) {
  /* Serial.printf("Enter y\n");
  char input = 'n';
  do { 
    if (Serial.available() > 0) {
      input = Serial.read();
    }
  } while (input != 'y'); */

  Serial.printf("\nSending ping to node %d\n", target);

  if (USEACK) {
    unsigned long time1 = micros();
    bool success = radio.sendWithRetry(TONODEID, "e", 1, 0, 2); //send character "m" (length 1) to TONODEID, 0 retries, 2ms wait time for ACK
    unsigned long time2 = micros();
    unsigned long RTT = time2 - time1;
    // Serial.printf("\tRTT: %d us\n", RTT);
    // counter++; //This works
    // total_RTT += RTT;

    // counter_array.push_back(counter);
    // RTT_array.push_back(RTT);

    // for (size_t i = 0; i < counter_array.size(); ++i) {
    //   Serial.printf("Run number: %d\n", counter_array[i]);
    // }

    // for (size_t j = 0; j < RTT_array.size(); ++j) {
    //   Serial.printf("RTT value: %d\n", RTT_array[j]);
    // }

    // Serial.printf("The current run number is: %d\n", counter); //This works
    // Serial.printf("The average RTT is currently: %f us\n", static_cast<float>(total_RTT)/counter);


    if (success) {
        Serial.printf("ACK received!\n");
    } else {
        Serial.printf("no ACK received :(\n");
        sendPing(2);
    }
  } else {
    Serial.printf("Sending without ack\n");
    radio.send(TONODEID, "m", 1); //send character "m" (length 1) to TONODEID
    Serial.printf("Sent!\n");
  }
}

void receivePing() {
  // Serial.printf("Waiting for ping from transmitter (speaker) to start listening...\n");

  while (!radio.receiveDone()) {
    // if(timeout_occurred(startTime, timeoutDuration)) {
    //   return;
    // }
    // do nothing
  }

  Serial.printf("Ping received from node %d: [", radio.SENDERID);

  for (byte i = 0; i < radio.DATALEN; i++)
    Serial.printf("%c", (char)radio.DATA[i]);
  Serial.printf("]\n");

  Serial.printf("RSSI : %d\n", radio.RSSI);

  // Send an ACK if requested.
  if (radio.ACKRequested()) {
    radio.sendACK();
    Serial.printf("ACK sent\n");
  }
}

bool timeout_occurred(unsigned long startTime, unsigned long timeoutDuration) {
    // Get current time
    unsigned long endTime = micros();
    unsigned long elapsedTime = endTime - startTime;

    if (elapsedTime >= timeoutDuration) {
        Serial.printf("Timeout occurred after %d s\n", timeoutDuration/1000000);
        return true;
    } else {
        // Operation completed within the timeout
        return false;
    }
}
