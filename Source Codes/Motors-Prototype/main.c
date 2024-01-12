#include "pwm_config.h"
#include "interrupt_stub.h"
#include "MKL25Z4.h"

/*
//Instead of hardcoding duty cycle, will make it variable based on interrupts. 
#define DUTY_CYCLE (50)
*/

int var_duty_cycle = 0;

/*Increases the duty cycle by increments of 10 percent on each PIT timer interrupt*/
void increase_duty_cycle()
{
   if (var_duty_cycle >= 100)
	 {
		  var_duty_cycle = 0;
	 }
	 else
	 {
	    var_duty_cycle += 10;
	 }
}

int main()
{
	var_duty_cycle = 0;
	
	init_PWM();
	init_timer();
	
	/*Generate PWM with a 0% duty cycle by writing into CNV which is the percent we are high vs low*/
	/*Using a 12V source, if duty cycle is 30%, 3.6V is being driving to the 3-6V DC motor*/
	/*Channel 0*/
	TPM0->CONTROLS[0].CnV = (var_duty_cycle * TPM0->MOD) / 100;
	
	Start_PIT();
	
	while(1) {
	
	}
	
	Stop_PIT();
	
	return 0;
	
	//TPM0->CONTROLS[2].CnV = (DUTY_CYCLE * TPM0->MOD) / 100;
}