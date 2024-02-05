#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>

#include "pin_config.h"
#include "encoder_interrputs.h"
#include "common.h"
#include "calculations.h"
#include "motors_control.h"
#include "MKL25Z4.h"

/*----- Measurements of small cart -----

	Wheel Diameter = 2.5 in = 6.35 cm
	Cart Width (Pivot Radius) = 13.3 cm 
		Pivot Diameter = 26.6 cm
*/ 

static struct duty_cycles {
	int FL, BL; // Front and Back left
	int FR, BR; // Frnot and Back right
}duty_cycles;

enum states state = STOPPED;

/*Increases the duty cycle by increments of 10 percent on each PIT timer interrupt*/
void control_duty_cycle(int front_left, int back_left, int front_right, int back_right) {
	duty_cycles.FL = front_left;
	duty_cycles.BL = back_left;
	duty_cycles.FR = front_right;
	duty_cycles.BR = back_right;
}

// Calculations for two wheels (prototype)
int turn_theta(float angle) {

	bool turning_right = false; 
	
	if(angle > 270) {
		turning_right = true;
		angle = 360 - angle;
	} 
	
	int pulses = calculate_pulses_for_angle(angle);
	float RPM_factor = (pulses / pulses_per_rev);
	
	if(turning_right) {
		control_right_motors(duty_cycles.FR - (duty_cycles.FR * RPM_factor), 
													duty_cycles.BR - (duty_cycles.BR * RPM_factor));
	} else {
		control_left_motors(duty_cycles.FL - (duty_cycles.FL * RPM_factor), 
													duty_cycles.BL - (duty_cycles.BL * RPM_factor));
	}
	
	return pulses;
}

int pivot_theta(float angle) {

	bool turning_right = false; 
	
	if(angle > 270) {
		turning_right = true;
		angle = 360 - angle;
	} 
	
	if(turning_right) {
		pivot_right();
	} else {
		pivot_left();
	}
	
	return calculate_pulses_for_angle(angle);
}

void pivot_left() {
	
	/* Drive Motor 1 backwards*/
	PTE->PSOR = MASK(PTE20_PIN_LF);
	PTE->PCOR = MASK(PTE21_PIN_LB);
	
	/* Drive Motor 2 forwards*/
	PTE->PSOR = MASK(PTE22_PIN_RF);
	PTE->PCOR = MASK(PTE23_PIN_RB);
	
	// Stub for detecting when we have turned 90 deg
}

void pivot_right() {
	
	/* Drive Motor 1 forwards*/
	PTE->PCOR = MASK(PTE20_PIN_LF);
	PTE->PSOR = MASK(PTE21_PIN_LB);
	
	/* Drive Motor 2 backwards*/
	PTE->PCOR = MASK(PTE22_PIN_RF);
	PTE->PSOR = MASK(PTE23_PIN_RB);
	
	// Stub for detecting when we have turned 90 deg
}

void control_left_motors(float F_PWM, float B_PWM) {
		TPM0->CONTROLS[0].CnV = (B_PWM * TPM0->MOD) / 100;
		TPM0->CONTROLS[3].CnV = (F_PWM * TPM0->MOD) / 100;
}

void control_right_motors(float F_PWM, float B_PWM) {
		TPM0->CONTROLS[2].CnV = (F_PWM * TPM0->MOD) / 100;
		TPM0->CONTROLS[4].CnV = (B_PWM * TPM0->MOD) / 100;
}

void drive_motors_straight() {
	
	// Set left motor to spin forwards
	PTE->PCOR = MASK(PTE20_PIN_LF);
	PTE->PSOR = MASK(PTE21_PIN_LB);
	
	// Set right motor to spin forwards
	PTE->PSOR = MASK(PTE22_PIN_RF);
	PTE->PCOR = MASK(PTE23_PIN_RB);
	
	// Set to same duty cycle
	control_left_motors(duty_cycles.FL, duty_cycles.BL);
	control_right_motors(duty_cycles.FR, duty_cycles.BR);
}

void stop_car() {
	// Stop left motor
	PTE->PCOR = MASK(PTE20_PIN_LF);
	PTE->PCOR = MASK(PTE21_PIN_LB);
	
	// Stop right motor
	PTE->PCOR = MASK(PTE22_PIN_RF);
	PTE->PCOR = MASK(PTE23_PIN_RB);
}

struct duty_cycles get_duty_cycle() {
	return duty_cycles;
}

/* stub implementation for queue */
float get_next_theta(void) {
	return 20.0f;
}
