#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

void increase_duty_cycle();

void turn_theta(int angle);

void turn_90_left();
void turn_90_right();

void control_left_motor(int PWM);
void control_right_motor(int PWM);

void drive_motors_straight();

void stop_car();

int get_duty_cycle();

#endif