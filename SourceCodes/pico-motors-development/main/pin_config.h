#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

void setup_pwm();

void set_pwm_duty_cycle(unsigned int pwm_pin, unsigned int duty_cycle);

void stop_motor(unsigned int pwm_pin);

void drive_motors_straight();

void drive_all_motors_init(uint8_t duty_cycle);

void stop_all_motors();

void pivot_right();

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
#define ENCODER_FL (10)
#define ENCODER_BL (11)
// Board Right Side
#define ENCODER_FR (20)
#define ENCODER_BR (21)

#define PWM_FREQ 50

#endif
