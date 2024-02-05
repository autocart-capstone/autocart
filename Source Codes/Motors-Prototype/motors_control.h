#ifndef MOTORS_CONTROL_H
#define MOTORS_CONTROL_H

enum states {
	ANGLE = 1, 
	PIVOT = 2, 
	STRAIGHT = 3, 
	STOPPED = 4
};

extern enum states state;

void control_duty_cycle(int front_left, int back_left, int front_right, int back_right);

int turn_theta(float angle);
int pivot_theta(float angle);

void pivot_left(void);
void pivot_right(void);

void control_left_motors(float F_PWM, float B_PWM);
void control_right_motors(float F_PWM, float B_PWM);

void drive_motors_straight(void);

void stop_car(void);

struct duty_cycles get_duty_cycle(void);

float get_next_theta(void);

#endif