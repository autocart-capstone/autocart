#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pwm_config.h"
#include "pwm_control.h"
#include "interrupt_stub.h"
#include "direction_config.h"
#include "MKL25Z4.h"

/*----- Measurements of small cart -----

	Wheel Diameter = 2.5 in = 6.35 cm
	Cart Width (Pivot Radius) = 13.3 cm 
		Pivot Diameter = 26.6 cm

*/ 

#define PI 3.14159
#define wheel_diam 6.35
#define pivot_diam 26.6

static float wheel_circ = wheel_diam * PI;
static float pivot_circ = pivot_diam * PI;

static int var_left_duty_cycle = 40;
static int var_right_duty_cycle = 40;

static bool turning = false;
static float pulses_for_theta;
static int starting_pulse; 

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
	 
	/*Generate PWM with a 0% duty cycle by writing into CNV which is the percent we are high vs low*/
	/*Using a 12V source, if duty cycle is 30%, 3.6V is being driving to the 3-6V DC motor*/
	 
	drive_motors_straight();
	 
	/*Channel 0, Motor 1*/
	//control_right_motor(var_right_duty_cycle);
	/*Channel 2, Motor 2*/
	//control_left_motor(var_left_duty_cycle);
}

void turn_theta(float angle) {
	// Calculations for two wheels (prototype)
	
	bool right = false; 
	turning = true;
	starting_pulse = encoder_pulses;
	
	if(angle > 270) {
		right = true;
	} 
	
	// rounding here, might need to change
	float pulses_per_full_pivot = pulses_per_rev * (pivot_circ / wheel_circ);
	
	pulses_for_theta = (angle / 360) * (pulses_per_full_pivot);
	
	float RPM_factor = (pulses_for_theta / pulses_per_rev);
	
	if(right) {
		control_right_motor(var_right_duty_cycle - (var_right_duty_cycle * RPM_factor));
	} else {
		control_left_motor(var_left_duty_cycle - (var_left_duty_cycle * RPM_factor));
	}
	
}

void turn_90_left() {
	
	/* Drive Motor 1 backwards*/
	PTE->PSOR = MASK(PTE20_PIN);
	PTE->PCOR = MASK(PTE21_PIN);
	
	/* Drive Motor 2 forwards*/
	PTE->PSOR = MASK(PTE22_PIN);
	PTE->PCOR = MASK(PTE23_PIN);
	
	// Stub for detecting when we have turned 90 deg
	for(int i = 0; i < 10000000; i++);
	
	drive_motors_straight();
}

void turn_90_right() {
	
	/* Drive Motor 1 forwards*/
	PTE->PCOR = MASK(PTE20_PIN);
	PTE->PSOR = MASK(PTE21_PIN);
	
	/* Drive Motor 2 backwards*/
	PTE->PCOR = MASK(PTE22_PIN);
	PTE->PSOR = MASK(PTE23_PIN);
	
	// Stub for detecting when we have turned 90 deg
	for(int i = 0; i < 10000000; i++);
	
	drive_motors_straight();
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
	PTE->PCOR = MASK(PTE20_PIN);
	PTE->PCOR = MASK(PTE21_PIN);
	
	PTE->PCOR = MASK(PTE22_PIN);
	PTE->PCOR = MASK(PTE23_PIN);
	
	for(int i = 0; i < 1000000; i++);
}

int get_duty_cycle() {
	return var_left_duty_cycle;
}

int main(){	
	init_PWM();
	
	init_timer();
	
	init_direction_pins();

	Start_PIT();
	
	/* Start motors running at 50% */ 
	TPM0->CONTROLS[2].CnV = (50 * TPM0->MOD) / 100;
	TPM0->CONTROLS[0].CnV = (50 * TPM0->MOD) / 100;
	
	drive_motors_straight();
	
	while(1) {
		if(turning) {
			
		/* 
		Stub implementation for detecting pulses elapsed. Car is properly oriented when
		pulses elapsed reach the calculated value for theta  
		
		Cannot be certain that we will be begining a turn from the beginning of a new rotation (encoder_pulses = 0), 
		so we must account for this by finding which pulse to stop at, regardless of what pulse we start at
		*/
			while(encoder_pulses != ((starting_pulse + (int) round(pulses_for_theta)) % pulses_per_rev)) { 	
				/*
					This is a rough implementation with rounding, idealy we want to avoid as much rounding as possible
				*/
			}
			turning = false;
			drive_motors_straight();
		}
	}
	
	Stop_PIT();
	
	return 0;
	
	//TPM0->CONTROLS[2].CnV = (DUTY_CYCLE * TPM0->MOD) / 100;
}