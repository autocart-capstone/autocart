#include <Wire.h>
#include "i2c_setup.h"
#include "pin_config.h"

const byte PICO_I2C_SDA = 0;
const byte PICO_I2C_SCL = 1;

uint32_t received_angle;
uint32_t turning_angle;
int32_t turning_distance;

uint32_t previous_angle;

//Define
arduino::MbedI2C mywire(PICO_I2C_SDA, PICO_I2C_SCL);

void init_i2c() {
  previous_angle = 0;
  mywire.begin(I2C_ADDRESS); // Initialize I2C communication with address 0x12
  mywire.onReceive(receiveEvent); // Register receiveEvent function
}

// Variables to store received tuple elements
int received_data[3];

// Function to receive data
void receiveEvent(int bytes) {
  int index = 0;
  while (mywire.available()) {
    // Read received byte
    int c = mywire.read();
    // Store received byte in array
    received_data[index++] = c;
  }

  // Process received data
  processMessage(received_data); // Assuming 3 elements in tuple
}

void processMessage(int* data) {
  // Print received tuple elements

  received_angle = (data[MSB_ANGLE_INDEX] << 8) | (data[LSB_ANGLE_INDEX]);
  Serial.print("Angle: ");
  Serial.println(received_angle);
  
  turning_distance = data[DISTANCE_INDEX];

  Serial.print("Distance: ");
  Serial.println(turning_distance);
  Serial.println();

  if ((turning_angle > (previous_angle - 5)) || (turning_angle < (previous_angle + 5)))
  {
    //Do nothing if the angle hasn't changed significantly, continue receiving. 
  }
  else
  {
    //Perform a turn
    previous_angle = turning_angle;
    drive_straight(70);
    setState(PIVOT);   
  }
}