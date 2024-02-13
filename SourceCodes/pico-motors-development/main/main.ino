#include "spi_setup.h"
#include "pin_config.h"
#include "encoder_interrupts.h"

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  spi_master_setup();
  setup_pwm(); 
  init_encoders();
  init_RPM_timer();
}

void setup1() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  spi_master_setup();
  setup_pwm(); 
  init_encoders();
  init_RPM_timer();
}

void loop() {
  // put your main code here, to run repeatedly:
  drive_all_motors_init(100);

  digitalWrite(DIRECTION_FL, HIGH);
  digitalWrite(DIRECTION_FR, HIGH);

  //Serial.println(FR_mtr_RPM);
}

void loop1()
{

  Serial.print("Yello?");
  auto a = send_data_request(true);

  //Basic Sequence for handling object obstruction 
  if (a == 1)
  {
    Serial.print("OBJECT DETECTED");
    stop_all_motors(); // Stop all Motors

    //INITAL PROTOTYPE, KEEP POLLING SPI UNTIL 0 MEANING OBJECT IS CLEARED SO YOU CAN CONTINUE MOVING
    while (send_data_request(true) == 1)
    {
      Serial.print("Waiting for object to clear...");
    }

    drive_all_motors_init(100);
  }
  
  delay(1000);
}
