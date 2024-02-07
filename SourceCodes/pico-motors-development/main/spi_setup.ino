#include <SPI.h>
#include "spi_setup.h"

#define SLAVE_SELECT_PIN 15

void spi_setup()
{
  Serial.begin(9600); // Initialize Serial communication
  pinMode(SLAVE_SELECT_PIN, INPUT); // Set Slave Select pin as input
  attachInterrupt(digitalPinToInterrupt(SLAVE_SELECT_PIN), onDataReceived, LOW); // Attach interrupt to the Slave Select pin
  /*
  MOSI: Pin 3 (GP4)
  MISO: Pin 4 (GP5)
  SCK: Pin 5 (GP6)
  */
  SPI.begin(); // Initialize SPI communication
}

void onDataReceived()
{
  byte data = SPI.transfer(0);
  Serial.print(data);  
}
