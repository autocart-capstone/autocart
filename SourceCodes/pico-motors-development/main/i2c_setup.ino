#include <Wire.h>
#include "i2c_setup.h"
#include "pin_config.h"

const byte PICO_I2C_SDA = 0;
const byte PICO_I2C_SCL = 1;

uint32_t received_angle;

//Initially, point of interest is expected to be directly ahead, so 0 degrees (where right is 90 degrees and left is 270).
uint32_t previous_angle = 0;

//Define
arduino::MbedI2C mywire(PICO_I2C_SDA, PICO_I2C_SCL);

void init_i2c() {
  mywire.begin(I2C_ADDRESS);       // Initialize I2C communication with address 0x12
  mywire.onReceive(receiveEvent);  // Register receiveEvent function
}

// Variables to store received tuple elements
int received_data[4];

// Function to receive data
void receiveEvent(int bytes) {
  int index = 0;
  while (mywire.available()) {
    // Read received byte
    int c = mywire.read();
    Serial.println(c);
    //Get 3 bytes
    // Interface: First two bytes are the angle, third byte is the state we want to be in.
    received_data[index++] = c;
    if (index == 4) {
      Serial.println("-------------");
      processMessage(received_data);
      index = 0;
    }
  }
  // Process received data
}

void processMessage(int* data) {
  // Print received tuple elements
  // The angle to the point of interest.

  received_angle = (data[MSB_ANGLE_INDEX] << 8) | (data[LSB_ANGLE_INDEX]);
  States state = (States)data[STATE_INDEX];
  Serial.print("Recieved Angle: ");
  Serial.println(received_angle);

  Serial.print("Recieved State: ");
  Serial.println(state);

  if (received_angle > 1 && received_angle < 359) {
    // Angle has changed significantly, set state to adjusting.
    if ((getState() == PIVOT_LEFT || getState() == PIVOT_RIGHT) && state != STOP) {
      // Do Nothing
    } else {
      Serial.println("changed state to ADJUST ");
      set_turning_angle(received_angle);
      setState(ADJUST);
    }
  } else if (state <= BACKWARD) {
    if ((getState() == PIVOT_LEFT || getState() == PIVOT_RIGHT) && state != STOP) {
      Serial.println("currently pivoting");
      // Do Nothing
    } else {
      Serial.print("changed state to  ");
      Serial.println(state);
      setState(state);
    }
  } else {
    Serial.print("Invalid state input: ");
    Serial.println(state);
  }
}

uint32_t get_turning_angle() {
  return received_angle;
}

//FOR DEBUGGING PURPOSES
void set_turning_angle(uint32_t angle) {
  received_angle = angle;
}
