#include "pin_config.h"
#include "i2c_setup.h"
#include "encoder_interrupts.h"

static int turn_pulses = 0;
static int pivot_pulses = 0; 
static long prevT = 0;
static float velFilt[4] = {0, 0, 0, 0};
static float velPrev[4] = {0, 0, 0, 0}; 

static float eintegral[4] = {0, 0, 0, 0}; 

/* Method needs to be tested to ensure that we can hit 0 RPM and target RPM on each motor */
void PID_controller() {
  long currT = micros();
  float deltaT = ((float) (currT-prevT)) / 1.0e6; 
  prevT = currT; 

  //  Apply controller to each motor
  for (int i = 0; i < NUM_MOTORS; i++) {

    // Target velocity (RPM)
    float vt = 230;

    // Get current velocity in RPM (udpates every second on RPM calc interrupt)
    float vel = FL_mtr_RPM; 

    // Low-pass filter (25 Hz cutoff)
    velFilt[i] = 0.854*velFilt[i] + 0.0728*vel + 0.0728*velPrev[i];
    velPrev[i] = vel;

    /* -------- Proportional Controller -------- */
    float kp = 1; // proportional constant, needs to be tuned. increasing provides more power
    float e = vt - velFilt[i]; // error


    /* -------- Integral Controller -------- */
    float ki = 1; // Integral constant. increasing provides more power
    eintegral[i] = eintegral[i] + e*deltaT; // Update integral with difference


    float u = kp*e + ki*eintegral[i]; // Control signal

    // Set motor speed
    int adjusted_PWM = (int) fabs(u);
    if(adjusted_PWM > 255) {
      adjusted_PWM = 255;
    }

    set_pwm_duty_cycle(DIRECTION_FL, adjusted_PWM);
    
    Serial.print(vt);
    Serial.print(" ");
    delay(1);
  }
}

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  setup_pwm(); 
  init_i2c();
  setState(STOPPED);
  drive_all_motors_init(20);
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
      pivot_pulses = pivot_theta(turning_angle) / 2;
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


void loop1()
{}
