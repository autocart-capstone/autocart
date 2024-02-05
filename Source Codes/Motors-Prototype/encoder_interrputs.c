#include "encoder_interrputs.h"
#include "common.h"
#include "calculations.h"
#include "MKL25Z4.h"

/* variables to track encoder pulses elapsed for turning */
int FL_turn_pulses = 0;
int BL_turn_pulses = 0;
int FR_turn_pulses = 0;
int BR_turn_pulses = 0;

/* variables to track pulses over a period to track RPM */
int FL_speed_pulses = 0;
int BL_speed_pulses = 0;
int FR_speed_pulses = 0;
int BR_speed_pulses = 0;

float FL_mtr_RPM = 0;
float BL_mtr_RPM = 0;
float FR_mtr_RPM = 0;
float BR_mtr_RPM = 0;

// Can add paramter for pin if all encoders are on same port
void init_encoders() {
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; 
	
	PORTA->PCR[PTA1_PIN_FL]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT A pin 1 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA1_PIN_FL]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);
	
	PORTA->PCR[PTA2_PIN_BL]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT A pin 2 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA2_PIN_BL]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);;
	
	PORTA->PCR[PTA3_PIN_FR]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT A pin 1 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA3_PIN_FR]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);
	
	PORTA->PCR[PTA4_PIN_BR]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT A pin 2 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA4_PIN_BR]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);;
	
	PTA->PDDR &= ~MASK(PTA1_PIN_FL);
	PTA->PDDR &= ~MASK(PTA2_PIN_BL);
	PTA->PDDR &= ~MASK(PTA3_PIN_FR);
	PTA->PDDR &= ~MASK(PTA4_PIN_BR);
	
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
	FL_turn_pulses = 0;
	BL_turn_pulses = 0;
	FR_turn_pulses = 0;
	BR_turn_pulses = 0;
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
		
		FL_mtr_RPM = calculate_RPM(FL_speed_pulses);
		BL_mtr_RPM = calculate_RPM(BL_speed_pulses);
		FR_mtr_RPM = calculate_RPM(FR_speed_pulses);
		BR_mtr_RPM = calculate_RPM(BR_speed_pulses);
		
		FL_speed_pulses = 0;
		BL_speed_pulses = 0;
		FR_speed_pulses = 0;
		BR_speed_pulses = 0;
		
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
	}
}

void PORTA_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	
	// encoder 1
	if(PORTA->ISFR & MASK(PTA1_PIN_FL)) {
		FL_speed_pulses++;
		FL_turn_pulses++;
	}
	
	// encoder 2
	if (PORTA->ISFR & MASK(PTA2_PIN_BL)) {
		BL_speed_pulses++;
		BL_turn_pulses++;
	}

	// encoder 3
	if(PORTA->ISFR & MASK(PTA3_PIN_FR)) {
		FR_speed_pulses++;
		FR_turn_pulses++;
	}
	
	// encoder 4
	if (PORTA->ISFR & MASK(PTA4_PIN_BR)) {
		BR_speed_pulses++;
		BR_turn_pulses++;
	}
	
	PORTA->ISFR = 0xffffffff;
}