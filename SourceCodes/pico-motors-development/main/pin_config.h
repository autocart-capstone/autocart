#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

enum states {
	ANGLE = 1, 
	PIVOT = 2, 
	STRAIGHT = 3, 
	STOPPED = 4,
  RECEIVING = 5, // Default state
  BRAKING = 6
};

enum states state = RECEIVING;

// PWM-Drive
// Board Left Side
#define PWM_TL 6
#define PWM_BL 7
// Board Right Side
#define PWM_BR 26
#define PWM_TR 27

// FWD of the board is USB connection

// PWM-direction
// Board Left Side
#define DIRECTION_FL (13) // x- Forwards
#define DIRECTION_BL (12) // -x Backwards
// Board Right Side
#define DIRECTION_FR (18) // x- Forwards
#define DIRECTION_BR (19) // -x Backwards

// Encoder Pins
// Board Left Side
#define ENCODER_FL (9)
#define ENCODER_BL (11)
// Board Right Side
#define ENCODER_FR (21)
#define ENCODER_BR (20)

#define PWM_FREQ 50
#define NUM_MOTORS 4 

const int encoders[4] = {ENCODER_FL, ENCODER_BL, ENCODER_FR, ENCODER_BR};
const int PWM[4] = {PWM_TL, PWM_BL, PWM_TR, PWM_BR};
const int directions[4] = {DIRECTION_FL, DIRECTION_BL, DIRECTION_FR, DIRECTION_BR};

void setup_pwm();

void drive_all_motors_init(uint8_t duty_cycle);

void set_pwm_duty_cycle(unsigned int pwm_pin, unsigned int duty_cycle);

void drive_straight(int PWM);

void stop_motors();

void pivot_left();

void pivot_right();

int pivot_theta(float angle);

int turn_theta(float angle);

void setState(enum states newState);

int get_pwm(unsigned int pwm_pin);

states getState();

#endif
