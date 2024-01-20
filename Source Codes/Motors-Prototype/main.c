#include <math.h>
#include <stdbool.h> 

#include "pwm_config.h"
#include "pwm_control.h"
#include "interrupt_stub.h"
#include "direction_config.h"
#include "MKL25Z4.h"

/*
//Instead of hardcoding duty cycle, will make it variable based on interrupts. 
#define DUTY_CYCLE (50)
*/

#define pulses_for_360 12
#define circle 360

#define pulses_for_wheel_rotation 3
#define turn_time 4

static int var_left_duty_cycle = 40;
static int var_right_duty_cycle = 40;


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

void turn_theta(int angle) {
	// Calculations for two wheels (prototype)
	
	bool right = false; 
	
	if(angle > 270) {
		right = true;
	} 
	
	float pulses_for_theta = ((float) angle / (float) circle) * (pulses_for_360);
	
	/* int pulses_per_second = pulses_for_theta / turn_time; */
	
	float RPM_factor = (pulses_for_theta / pulses_for_wheel_rotation);
	
	if(right) {
		control_right_motor(var_right_duty_cycle - (var_right_duty_cycle * RPM_factor));
	} else {
		control_left_motor(var_left_duty_cycle - (var_left_duty_cycle * RPM_factor));
	}
	
	for(int i = 0; i < 10000000; i++);
	
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

int main()
{	
	init_PWM();
	init_timer();
	init_direction_pins();

	Start_PIT();
	
	
	/* Start motors running at 50% */ 
	TPM0->CONTROLS[2].CnV = (50 * TPM0->MOD) / 100;
	TPM0->CONTROLS[0].CnV = (50 * TPM0->MOD) / 100;
	
	drive_motors_straight();
	
	while(1) {
	
	}
	
	Stop_PIT();
	
	return 0;
	
	//TPM0->CONTROLS[2].CnV = (DUTY_CYCLE * TPM0->MOD) / 100;
}