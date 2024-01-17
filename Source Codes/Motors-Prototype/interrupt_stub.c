#include "MKL25Z4.h"
#include "pwm_config.h"
#include "pwm_control.h"
#include "interrupt_stub.h"
/*
- Stubs data received from either UART from Lidar directly. Stub of choice was a counting timer. Can be updated later. 
*/
void init_timer()
{
		// Enable clock to PIT module
		SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
		
		// Enable module, freeze timers in debug mode
		PIT->MCR &= ~PIT_MCR_MDIS_MASK;
		PIT->MCR |= PIT_MCR_FRZ_MASK;
		
		//Initialize PIT0 to count down from argument 
		//Example:
		/*
			period_us = 625 us * (24MHz -> 24e6/1s OR 0.0416 us (1/24MHz))))
		  This means we do 24e6 periods in 1 second so one period is 0.0416us
		  We have 15,000 in the LDV so every 0.0416us we go down by 1. 
		*/
	
		PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(2000000*24); // 24 MHz clock frequency

		// No chaining
		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK;
		
		// Generate interrupts
		PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

		/* Enable Interrupts */
		NVIC_SetPriority(PIT_IRQn, 128); // 0, 64, 128 or 192
		NVIC_ClearPendingIRQ(PIT_IRQn); 
		NVIC_EnableIRQ(PIT_IRQn);	
}

void Start_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}


void PIT_IRQHandler() {
	//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);
	
	// check to see which channel triggered interrupt 
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		
		if(get_duty_cycle() >= 70) {
			turn_right();
		}
		else if(get_duty_cycle() >= 50) {
			turn_left();
		}
		
		increase_duty_cycle();
		
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
	}
}

