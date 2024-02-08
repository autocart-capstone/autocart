#include "spi_setup.h"
#include "pin_config.h"
#include "encoder_interrupts.h"

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  spi_setup();
  setup_pwm(); 
  init_encoders();
  init_RPM_timer();
}

void loop() {
  // put your main code here, to run repeatedly:
  set_pwm_duty_cycle(PWM_TL, 100);
  set_pwm_duty_cycle(PWM_TR, 100);

  set_pwm_duty_cycle(PWM_BL, 100);
  set_pwm_duty_cycle(PWM_BR, 100);

  digitalWrite(DIRECTION_FL, HIGH);
  digitalWrite(DIRECTION_FR, HIGH);

  Serial.println(FR_mtr_RPM);


}
