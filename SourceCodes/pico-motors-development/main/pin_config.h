#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

typedef enum{
	STOP = 0,
  PIVOT_LEFT,
  PIVOT_RIGHT,
  FORWARD,
  BACKWARD,
  ADJUST
} States ;

States state = STOP;

// FWD of the board is USB connection

// PWM-Drive
// Board Left Side Forwards
#define PWM_FWD_FL 6
#define PWM_FWD_BL 7
// Board Left Side Backwards
#define PWM_BWD_FL 5
#define PWM_BWD_BL 13

// Board Right Side Forwards
#define PWM_FWD_FR 27
#define PWM_FWD_BR 26
// Board Right Side Backwards
#define PWM_BWD_FR 28
#define PWM_BWD_BR 18


// PWM-direction -- NOT NEEDED WITH NEW DRIVERS
// Board Left Side
#define DIRECTION_FL (13) // x- Forwards
#define DIRECTION_BL (12) // -x Backwards
// Board Right Side
#define DIRECTION_FR (18) // x- Forwards
#define DIRECTION_BR (19) // -x Backwards

// Encoder Pins
// Board Left Side
#define ENCODER_FL (10)
#define ENCODER_BL (11)
// Board Right Side
#define ENCODER_FR (21)
#define ENCODER_BR (20)

#define PWM_FREQ 50
#define NUM_MOTORS 4 

const int encoders[4] = {ENCODER_FL, ENCODER_BL, ENCODER_FR, ENCODER_BR};
const int PWM_FWD[4] = {PWM_FWD_FL, PWM_FWD_BL, PWM_FWD_FR, PWM_FWD_BR};
const int PWM_BWD[4] = {PWM_BWD_FL, PWM_BWD_BL, PWM_BWD_FR, PWM_BWD_BR};
const int directions[4] = {DIRECTION_FL, DIRECTION_BL, DIRECTION_FR, DIRECTION_BR};

void setup_pwm();

void drive_all_motors_init(uint8_t duty_cycle);

void set_pwm_duty_cycle(unsigned int pwm_pin, unsigned int duty_cycle);

void drive_forwards();

void drive_backwards();

void drive_left(); 

void drive_right();

void stop_motors();

void pivot_left();

void pivot_right();

int pivot_theta(float angle);

int turn_theta(float angle);

void setState(States newState);

States getState();

#endif
