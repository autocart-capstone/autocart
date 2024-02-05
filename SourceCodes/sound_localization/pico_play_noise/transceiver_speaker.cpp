#include <RFM69.h>
#include <SPI.h>
#include <vector>
#include "transceiver_speaker.h"

// uint32_t counter = 0;
// float total_RTT = 0;
// std::vector<int> counter_array;
// std::vector<int> RTT_array;

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
  radio.writeReg(0x03,0x00);
  radio.writeReg(0x04,0x80);
  radio.setHighPower(); // Always use this for RFM69HCW

  pinMode(CS_PIN,OUTPUT);
  digitalWrite(CS_PIN,LOW);

  pinMode(INTRPT_PIN,INPUT);
  digitalWrite(INTRPT_PIN,LOW);
}

void sendPing() {
  /* Serial.printf("Enter y\n");
  char input = 'n';
  do { 
    if (Serial.available() > 0) {
      input = Serial.read();
    }
  } while (input != 'y'); */

  Serial.printf("Sending ping to node %d\n", TONODEID);

  if (USEACK) {
    // unsigned long time1 = micros();
    bool success = radio.sendWithRetry(TONODEID, "s", 1, 0, 10); // 0 retries, 4 ms wait time
    // unsigned long time2 = micros();
    // unsigned long RTT = time2 - time1;
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
        // sendPing();
    }
  }
  else {
    Serial.printf("Sending without ack\n");
    radio.send(TONODEID, "g", 1);
    Serial.printf("Sent!\n");
  }
}

void receivePing() {
  // //Record start time of waiting for the ping from microphone
  // const unsigned long startTime = micros();
  // // Set timeout duration
  // unsigned long timeoutDuration = 1000000;  // 1 second timeout

  Serial.println("Waiting for ping from receiver (microphone)...");

  while(!radio.receiveDone()){
    // if(timeout_occurred(startTime, timeoutDuration)) {
    //   return;
    // }
    // do nothing
  }

  Serial.print("Ping received from node ");
  Serial.print(radio.SENDERID, DEC);
  Serial.print(": [");

  for (byte i = 0; i < radio.DATALEN; i++)
    Serial.printf("%c", (char)radio.DATA[i]);
  Serial.printf("]\n");

  // RSSI => smaller numbers mean higher power.
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
