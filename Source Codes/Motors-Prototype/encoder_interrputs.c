#include "encoder_interrputs.h"
#include "common.h"
#include "calculations.h"
#include "MKL25Z4.h"

/* variables to track encoder pulses elapsed for turning */
int enc_1_turn_pulses = 0;
int enc_2_turn_pulses = 0;

/* variables to track pulses over a period to track RPM */
int enc_1_speed_pulses = 0;
int enc_2_speed_pulses = 0;

float mtr_1_RPM = 0;
float mtr_2_RPM = 0;

// Can add paramter for pin if all encoders are on same port
void init_encoders() {
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; 
	
	PORTA->PCR[PTA1_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT B pin 3 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA1_PIN]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);
	
	PORTA->PCR[PTA2_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT B pin 3 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA2_PIN]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);;
	
	PTA->PDDR &= ~MASK(PTA1_PIN);
	PTA->PDDR &= ~MASK(PTA2_PIN);
	
	
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);	
}

void init_RPM_timer() {
			// Enable clock to PIT module
		SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
		
		// Enable module, freeze timers in debug mode
		PIT->MCR &= ~PIT_MCR_MDIS_MASK;
		PIT->MCR |= PIT_MCR_FRZ_MASK;
		
		//Initialize PIT0 to count down from argument 
		/*
			period_us = 625 us * (24MHz -> 24e6/1s OR 0.0416 us (1/24MHz))))
		  This means we do 24e6 periods in 1 second so one period is 0.0416us
		  We have 15,000 in the LDV so every 0.0416us we go down by 1. 
		
		  Initialize Channel 1 to generate interrupts every second to caluclate RPM
		  Channel 1: 1000000 microseconds = 1 seconds 
		*/
		PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(1000000*24); // 24 MHz clock frequency

		// No chaining
		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK;
		
		// Generate interrupts
		PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
		

		/* Enable Interrupts */
		NVIC_SetPriority(PIT_IRQn, 64); // 0, 64, 128 or 192
		NVIC_ClearPendingIRQ(PIT_IRQn); 
		NVIC_EnableIRQ(PIT_IRQn);	
}

void reset_encoders() {
	enc_1_turn_pulses = 0;
	enc_2_turn_pulses = 0;
}

void Start_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PIT(void) {
// Disable counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}

void PIT_IRQHandler() {
	//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);

	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		
		mtr_1_RPM = calculate_RPM(enc_1_speed_pulses);
		mtr_2_RPM = calculate_RPM(enc_2_speed_pulses);
		
		enc_1_speed_pulses = 0;
		enc_2_speed_pulses = 0;
		
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
	}
}

void PORTA_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	
	// encoder 1
	if(PORTA->ISFR & MASK(PTA1_PIN)) {
		
		enc_1_speed_pulses++;
		enc_1_turn_pulses++;
		
	// encoder 2
	}
	if (PORTA->ISFR & MASK(PTA2_PIN)) {
		
		enc_2_speed_pulses++;
		enc_2_turn_pulses++;
	}
	
	PORTA->ISFR = 0xffffffff;
}