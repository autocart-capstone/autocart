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

/* Method needs to be tested to ensure that we can hit 0 RPM and target RPM on each motor */
void PID_controller() {
  long currT = micros();
  float deltaT = ((float) (currT-prevT)) / 1.0e6; 
  prevT = currT; 

  //  Apply controller to each motor
  for (int i = 1; i < 4; i++) {

    // Get current velocity in RPM (udpates every second on RPM calc interrupt)
    float vel = getMotorRPM(i); 

    // Low-pass filter (25 Hz cutoff)
    velFilt[i] = 0.854*velFilt[i] + 0.0728*vel + 0.0728*velPrev[i];
    velPrev[i] = vel;

    /* -------- Proportional Component -------- */
    float kp = 0.28; // proportional constant, needs to be tuned. increasing provides more power
    float e = vt - velFilt[i]; // error

    /* -------- Integral Component -------- */
    float ki = 0.7; // Integral constant. increasing provides more power
    eintegral[i] = eintegral[i] + e*deltaT; // Update integral with difference

    float u = kp*e + ki*eintegral[i]; // Control signal

    // Set motor speed
    int adjusted_PWM = (int) fabs(u);
    if(adjusted_PWM > 255) {
      adjusted_PWM = 255;
    }
    // Set the PWM, and update struct
    set_pwm_duty_cycle(PWM_FWD[i], adjusted_PWM);
    set_pwm_duty_cycle(PWM_BWD[i], adjusted_PWM);

    Serial.print(i);
    Serial.print("   |   ");
    Serial.println(adjusted_PWM);

    // Encoder for FL motor broken, set to the same speed as BL motor
    if(i == 1) {
      set_pwm_duty_cycle(PWM_FWD[i-1], adjusted_PWM);
      set_pwm_duty_cycle(PWM_BWD[i-1], adjusted_PWM);
    }
    
  }
  Serial.print(vt);
  Serial.print(" ");
  Serial.print(velFilt[0]);
  Serial.print(" ");
  Serial.print(velFilt[1]);
  Serial.print(" ");
  Serial.print(velFilt[2]);
  Serial.print(" ");
  Serial.print(velFilt[3]);
  Serial.println();
  delay(1);
}

void setup() {
  Serial.begin(115200);
  // Setup SPI inteFRace
  // setup_pwm(); 
  init_i2c();
  init_encoders();
  init_RPM_timer();
}

void setup1() {
  Serial.begin(115200);
}

void loop() {
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

  setTarget(100); 
  switch(getState()) {
   
    case STOP:
      stop_motors();
      break;

    case LEFT:
      PID_controller();
      drive_left();
      break;

    case RIGHT:
      PID_controller();
      drive_right();
      break;

    case FORWARD:
      PID_controller();
      drive_forwards();
      break;

    case BACKWARD:
      PID_controller();
      drive_backwards();
      break;
  }
}

void setTarget(int target) {
  vt = target;
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
          setState(STOP);
          Serial.println("Set state to STOPPED");
          break;

        case '5':
          setState(RECEIVING);
          Serial.println("Set state to RECEIVING");
          break;

        case '6':
          setState(LEFT);
          drive_left();
          Serial.println("Set state to LEFT");
          break;

        case '7':
          setState(RIGHT);
          drive_right();
          Serial.println("Set state to RIGHT");
          break;

        case '8':
          setState(FORWARD);
          drive_forwards();
          Serial.println("Set state to FORWARD");
          break;

        case '9':
          setState(BACKWARD);
          drive_backwards();
          Serial.println("Set state to BACKWARD");
          break;
       
        case '0':
          setState(STOP);
          stop_motors();
          Serial.println("Set state to STOP");
          break;

        default:
            Serial.println("Invalid command. Available commands: 1, 2, 3, 4");
            break;
    }
}


void loop1()
{}
