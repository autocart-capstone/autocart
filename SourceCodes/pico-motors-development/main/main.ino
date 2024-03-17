#include "pin_config.h"
#include "i2c_setup.h"
#include "encoder_interrupts.h"

/*  Problems : 
      - Pluses for rotation are not correct in practice, need to increase them for more accurate turns

      - for some reason, when we keep getting signals from the pi, the code breaks where the wheels dont 
        turn at all, and seems to constantly go back into the stopped state (but dont actually as seen in debugging)
        can replicate it by using pi to send signals, and holding down an arrow key. 
      
      - sometimes have an issue where the wheels start of spinning really fast on first run (might be because of inrush current)

      - motors stop bring them all to a stop, but because we call PID_controller, they enable again and we end up with the motors not moving
        but continuing to make sounds
*/ 

static int turn_pulses = 0;
static int pivot_pulses = 0; 

static const int MOVING_SPEED = 100;
static const int TURNING_SPEED = 130;

static long prevT = 0;
static int vt = 0; // target velocity 
static float velFilt[4] = {0, 0, 0, 0};
static float velPrev[4] = {0, 0, 0, 0}; 
static float eintegral[4] = {0, 0, 0, 0}; 
static float uPrevious[4] = {0, 0, 0, 0};

static int adjusted_PWMs[4] = {0, 0, 0, 0};

bool stateChange = true;

void PID_controller() {
  long currT = micros();
  float deltaT = ((float) (currT-prevT)) / 1.0e6; 
  prevT = currT; 

  //  Apply controller to each motor
  for (int i = 1; i < 4; i++) {
    // Get current velocity in RPM (udpates every second on RPM calc interrupt) 
    noInterrupts(); // for syncronization
    float vel = getMotorRPM(i); 
    interrupts();

    // Low-pass filter (25 Hz cutoff)
    velFilt[i] = 0.854*velFilt[i] + 0.0728*vel + 0.0728*velPrev[i];
    velPrev[i] = vel;

    /* -------- Proportional Component -------- */
    float kp = 0.7; // proportional constant, needs to be tuned. increasing provides more power
    float e = vt - velFilt[i]; // error

    /* -------- Integral Component -------- */
    float ki = 2; // Integral constant. increasing provides more power
    eintegral[i] = eintegral[i] + e*deltaT; // Update integral with difference

    float u = (kp*e) + (ki*eintegral[i]); // Control signal
    uPrevious[i] = u;  
    
    int adjusted_PWM = (int) u;
    // u is positive, meaning we need to speed up
    if(adjusted_PWM > 0) {
      if(adjusted_PWM > 255) adjusted_PWM = 255;
    } else { // u is negative, meaning we need to slow down
      adjusted_PWM = uPrevious[i] - u;
    }

    adjusted_PWMs[i] = adjusted_PWM;
  }

  for(int i = 1; i < NUM_MOTORS; i++) {
    set_pwm_duty_cycle(PWM_FWD[i], adjusted_PWMs[i]);
    set_pwm_duty_cycle(PWM_BWD[i], adjusted_PWMs[i]);

    // Encoder for FL motor broken, set to the same speed as BL motor
    if(i == 1) {
      set_pwm_duty_cycle(PWM_FWD[i-1], adjusted_PWMs[i]);
      set_pwm_duty_cycle(PWM_BWD[i-1], adjusted_PWMs[i]);
    }
  }
}

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  // setup_pwm(); 
  init_i2c();
  init_encoders();
  init_RPM_timer();
}

void loop() {

  if (Serial.available() > 0) {
      char command = Serial.read();
      handleSerialCommand(command);
  }

  switch(getState()) {    
   
    case STOP:
      stateChange = false;

      drive_all_motors_init(0);
      stop_motors();
      break;

    case PIVOT_LEFT:
      stateChange = false;

      pivot_pulses = (pivot_theta(90) * 1.25); /*TODO: ADJUST ALGORITHM FOR TURNING*/
      pivot_left();
      drive_all_motors_init(TURNING_SPEED);
      if (getAvgPulsesLeft() < pivot_pulses && getAvgPulsesRight() < pivot_pulses) {
          // Continue pivoting
      } else {
          setState(FORWARD);
      }
      break;

    case PIVOT_RIGHT:
      stateChange = false;

      pivot_pulses = (pivot_theta(90) * 1.4); /*TODO: ADJUST ALGORITHM FOR TURNING*/
      pivot_right();
      drive_all_motors_init(TURNING_SPEED);
      if (getAvgPulsesLeft() < pivot_pulses && getAvgPulsesRight() < pivot_pulses) {
          // Continue pivoting
      } else {
          setState(FORWARD);
      }
      break;

    case FORWARD:
      if(stateChange) {
        kickStartMotors();
        stateChange = false;
      }
      drive_forwards();
      drive_all_motors_init(MOVING_SPEED);
      break;

    case BACKWARD:
      if(stateChange) {
        kickStartMotors();
        stateChange = false;
      }
      drive_backwards();
      drive_all_motors_init(MOVING_SPEED);
      break;

    case ADJUST:
      if(stateChange) {
        stateChange = false;
        turn_pulses = turn_theta(get_turning_angle()) * 2.5;
      }
      // On-the-fly adjustment with received angle. 
      // Might need to move this to set state method for integration so we dont keep reading new updates 
      if (fabs(getAvgPulsesLeft() - getAvgPulsesRight()) < turn_pulses) {
        // Continue turning
      } else {
          setState(FORWARD);
      }
      break;
      
  }
}

void setTarget(int target) {
  vt = target;
}

void kickStartMotors() {
  drive_all_motors_init(120);
  delay(25);
}

void handleSerialCommand(char command) {
    switch (command) {
        case '1':
          setTarget(0);
          break;

        case '2':
          setTarget(60);
          break;

        case '3':
          //Adjust in the right direction 30 degrees.
          Serial.println("SETTING ANGLE");
          set_turning_angle(60);
          break;

        case '4':
          //Adjust in the left direction 30 degrees. 
          set_turning_angle(300);
          break;
// overshoots (30 deg)
        case '5':
          setState(PIVOT_LEFT);
          drive_left();
          Serial.println("Set state to PIVOT_LEFT");
          break;

// undershoots (5 deg)
        case '6':
          setState(PIVOT_RIGHT);
          drive_right();
          Serial.println("Set state to PIVOT_RIGHT");
          break;

        case '7':
          setState(FORWARD);
          drive_forwards();
          Serial.println("Set state to FORWARD");
          break;

        case '8':
          setState(BACKWARD);
          drive_backwards();
          Serial.println("Set state to BACKWARD");
          break;

        case '9':
          setState(ADJUST);
          Serial.println("Set state to ADJUST");
          break;
       
        case '0':
          setState(STOP);
          Serial.println("Set state to STOP");
          stop_motors();
          break;

        default:
          Serial.println("Invalid command. Available commands: 0, 1, 2, 3, 4, ... 9");
          break;
    }
}
