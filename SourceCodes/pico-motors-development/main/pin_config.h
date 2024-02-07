#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

void setup_pwm();

void set_pwm_duty_cycle(unsigned int pwm_pin, unsigned int duty_cycle);

void stop_motor(unsigned int pwm_pin);

//PWM-Drive
#define PWM_TL 6
#define PWM_BL 7
#define PWM_BR 26
#define PWM_TR 27

//Encoder
#define PULSES_PER_REV 3

//PWM-direction
#define DIRECTION_LB (12) // -x Backwards
#define DIRECTION_LF (13) // x- Forwards
#define DIRECTION_RB (19) // -x Backwards
#define DIRECTION_RF (18) // x- Forwards

#define PWM_FREQ 50

#endif
