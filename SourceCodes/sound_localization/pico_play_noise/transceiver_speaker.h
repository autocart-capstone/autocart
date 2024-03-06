#ifndef TRANSCEIVER_SPEAKER_H
#define TRANSCEIVER_SPEAKER_H

#define NETWORKID     0   // Must be the same for all nodes (0 to 255)
#define MYNODEID      2   // My node ID (0 to 255)
#define TONODEID      100   // Destination node ID (0 to 254, 255 = broadcast)
#define FREQUENCY     RF69_915MHZ
#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    ""    // Use the same 16-byte key on all nodes
#define USEACK        false  // Request ACKs or not
#define CS_PIN        17    // in PICO
#define INTRPT_PIN    2     // in PICO

void setupRfm69();
void sendPing();
void receivePing();
void checkBroadcast();
#endif
