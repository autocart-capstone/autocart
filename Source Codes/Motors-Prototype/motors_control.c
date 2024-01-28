#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>

#include "pin_config.h"
#include "interrupt_stub.h"
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

static int var_left_duty_cycle = 40;
static int var_right_duty_cycle = 40;

enum states state = STOPPED;

/*Increases the duty cycle by increments of 10 percent on each PIT timer interrupt*/
void increase_duty_cycle()
{
   if (var_left_duty_cycle >= 100 || var_right_duty_cycle >= 100)
	 {
		  var_left_duty_cycle = 0;
			var_right_duty_cycle = 0;
	 }
	 else
	 {
			var_left_duty_cycle += 10;
			var_right_duty_cycle += 10;
	 }
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
		control_right_motor(var_right_duty_cycle - (var_right_duty_cycle * RPM_factor));
	} else {
		control_left_motor(var_left_duty_cycle - (var_left_duty_cycle * RPM_factor));
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
	PTE->PSOR = MASK(PTE20_PIN);
	PTE->PCOR = MASK(PTE21_PIN);
	
	/* Drive Motor 2 forwards*/
	PTE->PSOR = MASK(PTE22_PIN);
	PTE->PCOR = MASK(PTE23_PIN);
	
	// Stub for detecting when we have turned 90 deg
}

void pivot_right() {
	
	/* Drive Motor 1 forwards*/
	PTE->PCOR = MASK(PTE20_PIN);
	PTE->PSOR = MASK(PTE21_PIN);
	
	/* Drive Motor 2 backwards*/
	PTE->PCOR = MASK(PTE22_PIN);
	PTE->PSOR = MASK(PTE23_PIN);
	
	// Stub for detecting when we have turned 90 deg
}

void control_left_motor(float PWM) {
		TPM0->CONTROLS[2].CnV = (PWM * TPM0->MOD) / 100;
}

void control_right_motor(float PWM) {
		TPM0->CONTROLS[0].CnV = (PWM * TPM0->MOD) / 100;

}

void drive_motors_straight() {
	
	// Set left motor to spin forwards
	PTE->PCOR = MASK(PTE20_PIN);
	PTE->PSOR = MASK(PTE21_PIN);
	
	// Set right motor to spin forwards
	PTE->PSOR = MASK(PTE22_PIN);
	PTE->PCOR = MASK(PTE23_PIN);
	
	// Set to same duty cycle
	control_left_motor(var_left_duty_cycle);
	control_right_motor(var_right_duty_cycle);
}

void stop_car() {
	
	// Stop left motor
	PTE->PCOR = MASK(PTE20_PIN);
	PTE->PCOR = MASK(PTE21_PIN);
	
	// Stop right motor
	PTE->PCOR = MASK(PTE22_PIN);
	PTE->PCOR = MASK(PTE23_PIN);
}

int get_duty_cycle() {
	return var_left_duty_cycle;
}

/* stub implementation for queue */
float get_next_theta(void) {
	return 20.0f;
}
