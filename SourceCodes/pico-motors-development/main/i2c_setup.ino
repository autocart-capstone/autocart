#include <Wire.h>
#include "i2c_setup.h"
#include "pin_config.h"

const byte PICO_I2C_SDA = 0;
const byte PICO_I2C_SCL = 1;

uint32_t turning_angle;
int32_t turning_distance;

//Define
arduino::MbedI2C mywire(PICO_I2C_SDA, PICO_I2C_SCL);

void init_i2c() {
  mywire.begin(I2C_ADDRESS); // Initialize I2C communication with address 0x12
  mywire.onReceive(receiveEvent); // Register receiveEvent function
}

// Variables to store received tuple elements
int received_data[3];

// Function to receive data
void receiveEvent(int bytes) {
  int c = 0;
  while (mywire.available()) {
    // Read received byte
    c = mywire.read();
  }

  // Process received data
  processMessage((States) c);
}

void processMessage(States state) {
  // Print received tuple elements

  if (state > BACKWARD)
  {
    Serial.print("Invalid state input");
    Serial.print(state);
  }
  else
  {
    setState(state);
  }
}
