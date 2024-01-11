#include "pwm_config.h"
#include "MKL25Z4.h"

#define DUTY_CYCLE (50)


int main()
{
	
	init_PWM();
	init_enable();
	/*Generate PWM with a 50% duty cycle by writing into CNV which is the percent we are high vs low*/
	/*Using a 12V source, if duty cycle is 30%, 3.6V is being driving to the 3-6V DC motor*/
	/*Channel 0*/
	TPM0->CONTROLS[0].CnV = (DUTY_CYCLE * TPM0->MOD) / 100; 
	
	while(1) {
	}
	
	return 0;
	
	//TPM0->CONTROLS[2].CnV = (DUTY_CYCLE * TPM0->MOD) / 100;
}