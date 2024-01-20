#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

void increase_duty_cycle(void);

void turn_theta(float angle);

void turn_90_left(void);
void turn_90_right(void);

void control_left_motor(float PWM);
void control_right_motor(float PWM);

void drive_motors_straight(void);

void stop_car(void);

int get_duty_cycle(void);

int get_duty_cycle(void);

#endif