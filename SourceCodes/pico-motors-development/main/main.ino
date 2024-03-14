#include "pin_config.h"
#include "i2c_setup.h"
#include "encoder_interrupts.h"

static int turn_pulses = 0;
static int pivot_pulses = 0; 

static long prevT = 0;
static int vt = 0; // target velocity 
static float velFilt[4] = {0, 0, 0, 0};
static float velPrev[4] = {0, 0, 0, 0}; 
static float eintegral[4] = {0, 0, 0, 0}; 
static float uPrevious[4] = {0, 0, 0, 0};

static int adjusted_PWMs[4] = {0, 0, 0, 0};

bool stateChange = true;

/* Method needs to be tested to ensure that we can hit 0 RPM and target RPM on each motor */
void PID_controller() {
  long currT = micros();
  float deltaT = ((float) (currT-prevT)) / 1.0e6; 
  prevT = currT; 

  //  Apply controller to each motor
  for (int i = 1; i < 4; i++) {
    // Get current velocity in RPM (udpates every second on RPM calc interrupt)
    noInterrupts();
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

  // Serial.print(vt);
  // Serial.print(", ");
  // Serial.print(velFilt[0]);
  // Serial.print(", ");
  // Serial.print(velFilt[1]);
  // Serial.print(", ");
  // Serial.print(velFilt[2]);
  // Serial.print(", ");
  // Serial.print(velFilt[3]);
  // Serial.println();
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

  // //drive_all_motors_init(100);
  // Serial.print(200);
  // Serial.print(", ");
  // Serial.print(-10);
  // Serial.print(", ");
  
  if (Serial.available() > 0) {
      char command = Serial.read();
      handleSerialCommand(command);
  }

  /*  only straight and stopped states use PID controller, as the controller ensures that all the wheels operate 
      at a given target RPM. turning requires one side to slow dowm, and as such would need different target for 
      each side, which is extra. 

      currently, the PID controller will set PWM in the struct, so it will be used in turning, and can be reverted
      to after turning is finsihed 
  */

  switch(getState()) {    
   
    case STOP:
      stateChange = false;

      if(check_all_motor_RPM(0)) {
        stop_motors();
        PID_controller(); 
      } else {
        PID_controller(); 
        setTarget(0);
      }
      break;

    case PIVOT_LEFT:
      stateChange = false;

      pivot_pulses = pivot_theta(90) / 2; /*TODO: ADJUST ALGORITHM FOR TURNING*/
      pivot_left();
      if (getAvgPulsesLeft() < pivot_pulses && getAvgPulsesRight() < pivot_pulses) {
          // Continue pivoting
      } else {
          setState(FORWARD);
      }
      break;

    case PIVOT_RIGHT:
      stateChange = false;

      pivot_pulses = pivot_theta(90) / 2; /*TODO: ADJUST ALGORITHM FOR TURNING*/
      pivot_right();
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
      PID_controller();
      setTarget(60);
      //drive_all_motors_init(120);
      break;

    case BACKWARD:
      if(stateChange) {
        kickStartMotors();
        stateChange = false;
      }
      drive_backwards();
      PID_controller();
      setTarget(60);
      //drive_all_motors_init(120);
      break;

    case ADJUST:
      stateChange = false;
      // On-the-fly adjustment with received angle. 
      // Might need to move this to set state method for integration so we dont keep reading new updates 
      turn_pulses = turn_theta(get_turning_angle()); 
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
          set_turning_angle(30);
          break;

        case '4':
          //Adjust in the left direction 30 degrees. 
          set_turning_angle(330);
          break;

        case '5':
          setState(PIVOT_LEFT);
          drive_left();
          Serial.println("Set state to PIVOT_LEFT");
          break;

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
          break;

        default:
            Serial.println("Invalid command. Available commands: 0, 1, 2, 3, 4, ... 9");
            break;
    }
}
