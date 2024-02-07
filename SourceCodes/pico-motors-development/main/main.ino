#include "spi_setup.h"
#include "pin_config.h"

void setup() {
  // Setup SPI interface
  spi_setup();
  setup_pwm(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
