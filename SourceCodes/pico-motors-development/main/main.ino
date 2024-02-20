#include "pin_config.h"
#include "i2c_setup.h"
#include "encoder_interrupts.h"

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  setup_pwm(); 
  init_encoders();
  init_RPM_timer();
  init_i2c();
}

void loop() {
  // put your main code here, to run repeatedly:

  drive_motors_straight();
  
  drive_all_motors_init(50);

  delay(2000);

  Serial.print(BR_mtr_RPM);

  //pivot_right();

  //delay(3000);

  //Serial.println(FR_mtr_RPM);
}
/*

void setup1() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  setup_pwm(); 
  init_encoders();
  init_RPM_timer();
  init_i2c();
}

void loop1()
{
  
  delay(1000);
}
*/
