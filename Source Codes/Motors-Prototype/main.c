#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pin_config.h"
#include "encoder_interrputs.h"
#include "common.h"
#include "motors_control.h"
#include "spi_setup.h"
#include "MKL25Z4.h"

int main(){	
	init_PWM();
	
	//init_timer();
	init_direction_pins();
	init_encoders();
	init_RPM_timer();
	SPI_init();
	
	Start_PIT();
	
	__enable_irq();
	
	/* Start motors running at 50% */ 
	TPM0->CONTROLS[2].CnV = (50 * TPM0->MOD) / 100;
	TPM0->CONTROLS[0].CnV = (50 * TPM0->MOD) / 100;
	
	drive_motors_straight();
	
	float num1, num2;
	
	while(1) {
		/* test values to view RPM in debug */
		num1 = mtr_1_RPM;
		num2 = mtr_2_RPM;
		
		switch(state) { 
			case 1: // Turning
				/* 
				Stub implementation for detecting pulses elapsed. Car is properly oriented when
				pulses elapsed reach the calculated value for theta  
				
				Cannot be certain that we will be begining a turn from the beginning of a new rotation (encoder_pulses = 0), 
				so we must account for this by finding which pulse to stop at, regardless of what pulse we start at
			
				we must reset the encoder each time, so we count up to the required amount of pulses for our action. if we were to try and
				reset the counter each time we finished a rotation, it would be a lot more complicated to wait for more than [pulses_per_rev] pulses. 
					Getting the RPM from encoder becomes more difficult this way, however, since we are 'randomly' resetting the count, we would
					most likely need another variable to keep track of total spins (in a timeframe maybe?) for determining speed
				*/
				 
				reset_encoders();
				int num_pulses_turn = turn_theta(get_next_theta());
				while(enc_1_turn_pulses != num_pulses_turn) { 	
					/*
						This is a rough implementation with rounding, idealy we want to avoid as much rounding as possible
					*/
				}
				drive_motors_straight();
				break;
				
			case 2: //  Pivot
				reset_encoders();
				/* we can divide by two here as in a pivot, the wheels each drive in opposite directions, which halves the turning radius. 
					 so each wheel only needs to turn half as much as if we were making a smooth turn */
				int num_pulses_pivot = pivot_theta(get_next_theta()) / 2;
				while(enc_1_turn_pulses != num_pulses_pivot) { 	
					/*
						This is a rough implementation with rounding, idealy we want to avoid as much rounding as possible
					*/
				}
				drive_motors_straight();
				break;
			
			case 3: 
				// TODO straight
				break;
			
			case 4:
				// TODO stopped
				break;
		}

	}
	
	Stop_PIT();
	
	return 0;
	
	//TPM0->CONTROLS[2].CnV = (DUTY_CYCLE * TPM0->MOD) / 100;
}