#include <SPI.h>
#include "spi_setup.h"

void spi_setup()
{
  SPI.begin(); //initializes the SPI library
  Serial.begin(SERIAL_BAUDRATE);
  SPCR |= _BV(SPE); //SPI is now in slave mode

  SPI.attachInterrupt(); //Enable interrupts for SPI communication
}

ISR (SPI_STC_vect)
{
  volatile byte receive_value = 0;

  receive_value = SPDR; //Set receive value to the buffer value sent by master.

  Serial.print(receive_value); //Print out for now. 
}
