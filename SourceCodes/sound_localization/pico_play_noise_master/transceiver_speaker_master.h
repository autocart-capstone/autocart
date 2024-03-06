#ifndef TRANSCEIVER_SPEAKER_H
#define TRANSCEIVER_SPEAKER_H

#include <RFM69.h>

#define NETWORKID     0   // Must be the same for all nodes (0 to 255)
#define MYNODEID      100   // My node ID (0 to 255)
#define TOALLNODE     0   // Destination node ID (0 to 254, 0 = broadcast)
#define FREQUENCY     RF69_915MHZ
#define USEACK        true // Request ACKs or not
#define CS_PIN        17    // in PICO
#define INTRPT_PIN    2     // in PICO

void setupRfm69();
void sendPing(int target, char* msg);
void receivePing();
void sendBroadcast(String in);
#endif
