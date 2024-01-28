#ifndef MOTORS_CONTROL_H
#define MOTORS_CONTROL_H

enum states {
	ANGLE = 1, 
	PIVOT = 2, 
	STRAIGHT = 3, 
	STOPPED = 4
};

extern enum states state;

void increase_duty_cycle(void);

int turn_theta(float angle);
int pivot_theta(float angle);

void pivot_left(void);
void pivot_right(void);

void control_left_motor(float PWM);
void control_right_motor(float PWM);

void drive_motors_straight(void);

void stop_car(void);

int get_duty_cycle(void);

float get_next_angle(void);

#endif