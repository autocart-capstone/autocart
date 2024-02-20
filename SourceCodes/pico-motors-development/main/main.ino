#include "spi_setup.h"
#include "pin_config.h"
#include "encoder_interrupts.h"

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  spi_master_setup();
  setup_pwm(); 
  setState(STOPPED);
}

void setup1() {
  Serial.begin(115200);
  init_encoders();
  init_RPM_timer();
}

void loop() {
  // put your main code here, to run repeatedly:
  // drive_all_motors_init(50);
    if (Serial.available() > 0) {
        char command = Serial.read();
        handleSerialCommand(command);
    }

  int turn_pulses = 0;
  int pivot_pulses = 0;
  switch(getState()) {
    case 1: // Turning
      reset_encoders();
      turn_pulses = turn_theta(10);
      if (FL_turn_pulses != turn_pulses) {
          // Continue turning
      } else {
          // Turning complete, move to the next state
          setState(RECEIVING);
      }
      break;

    case 2: // Pivoting
      reset_encoders();
      pivot_pulses = pivot_theta(10) / 2;
      if (FL_turn_pulses != pivot_pulses) {
          // Continue pivoting
      } else {
          // Pivot complete, move to the next state
          setState(RECEIVING);
      }
      break;

    case 3: // Striaght 
      drive_straight(60);
      break;

    case 4: // Stopped
      stop_all_motors();
      break;

    case 5: // Recieving
      // Todo
      break;

    default:
      // Todo
      break;
  }

}

void loop1()
{
  
  Serial.println(BR_turn_pulses);
  Serial.print("Yello?");
  /*
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
  */
}

void handleSerialCommand(char command) {
    switch (command) {
        case '1':
            setState(ANGLE);
            Serial.println("Set state to ANGLE");
            break;

        case '2':
            setState(PIVOT);
            Serial.println("Set state to PIVOT");
            break;

        case '3':
            setState(STRAIGHT);
            Serial.println("Set state to STRAIGHT");
            break;

        case '4':
            setState(STOPPED);
            Serial.println("Set state to STOPPED");
            break;

        // Add more cases for additional commands if needed

        default:
            Serial.println("Invalid command. Available commands: 1, 2, 3, 4");
            break;
    }
}