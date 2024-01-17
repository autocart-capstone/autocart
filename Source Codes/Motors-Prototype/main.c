#include "pwm_config.h"
#include "pwm_control.h"
#include "interrupt_stub.h"
#include "MKL25Z4.h"

/*
//Instead of hardcoding duty cycle, will make it variable based on interrupts. 
#define DUTY_CYCLE (50)
*/

static int var_left_duty_cycle = 0;
static int var_right_duty_cycle = 0;

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

void turn_left() {
	control_left_motor(0);
	// Stub for detecting when we have turned 90 deg
	for(int i = 0; i < 1000000; i++);
	
	drive_motors_straight();
}

void turn_right() {
	control_right_motor(0);
	// Stub for detecting when we have turned 90 deg
	for(int i = 0; i < 1000000; i++);
	
	drive_motors_straight();
}

void control_left_motor(int PWM) {
		TPM0->CONTROLS[2].CnV = (PWM * TPM0->MOD) / 100;
}

void control_right_motor(int PWM) {
		TPM0->CONTROLS[0].CnV = (PWM * TPM0->MOD) / 100;

}

void drive_motors_straight() {
	control_left_motor(var_left_duty_cycle);
	control_right_motor(var_right_duty_cycle);
}

void stop_car() {
	control_right_motor(0);
	control_left_motor(0);
}

int get_duty_cycle() {
	return var_left_duty_cycle;
}

int main()
{	
	init_PWM();
	init_timer();

	Start_PIT();
	
	
	/* Start motors running at 50% */ 
	TPM0->CONTROLS[2].CnV = (50 * TPM0->MOD) / 100;
	TPM0->CONTROLS[0].CnV = (50 * TPM0->MOD) / 100;
	
	while(1) {
	
	}
	
	Stop_PIT();
	
	return 0;
	
	//TPM0->CONTROLS[2].CnV = (DUTY_CYCLE * TPM0->MOD) / 100;
}