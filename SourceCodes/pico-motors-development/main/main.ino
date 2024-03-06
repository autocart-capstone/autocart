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
  for (int i = 0; i < 4; i++) {

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

    Serial.print(i);
    Serial.print(" ");
    Serial.print(adjusted_PWM);
    Serial.print(" ");
    // Set the PWM, and update struct
    set_pwm_duty_cycle(PWM[i], adjusted_PWM);
    
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
  setup_pwm(); 
  init_i2c();
  setState(STOPPED);
  init_encoders();
  init_RPM_timer();
}

void setup1() {
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  //drive_all_motors_init(100);
  Serial.print(200);
  Serial.print(", ");
  Serial.print(-10);
  Serial.print(", ");

  Serial.println(getMotorRPM(0));
  Serial.println(FL_speed_pulses);

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

  //float vel2 = getMotorRPM(2); 
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
      PID_controller();
      setTarget(80); // arg is RPM
      drive_straight();
      //Serial.println(vel2);


      // Serial.print(digitalRead(ENCODER_FL));
      // Serial.print(digitalRead(ENCODER_FR));
      // Serial.print(digitalRead(ENCODER_BL));
      // Serial.print(digitalRead(ENCODER_BR));

      // Serial.print("Front Left ");
      // Serial.print(FL_speed_pulses);
      // Serial.print(" ");
      // Serial.print("Back Left ");
      // Serial.print(BL_speed_pulses);
      // Serial.print(" ");
      // Serial.print("Front Right ");
      // Serial.print(FR_speed_pulses);
      // Serial.print(" ");
      // Serial.print("Back Right ");
      // Serial.println(BR_speed_pulses);

      break;

    case 4: // Stopped
      PID_controller();
      setTarget(0);
      stop_motors();
      break;

    case 5: // Recieving
      // Todo
      break;

    default:
      // Todo
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
            setState(STOPPED);
            Serial.println("Set state to STOPPED");
            break;

        default:
            Serial.println("Invalid command. Available commands: 1, 2, 3, 4");
            break;
    }
}


void loop1()
{}
