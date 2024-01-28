#include "encoder_interrputs.h"
#include "common.h"
#include "MKL25Z4.h"

int encoder_pulses = 0;
int total_pulses = 0;

// Can add paramter for pin if all encoders are on same port
void init_encoder() {
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; 
	
	PORTA->PCR[PTA1_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT B pin 3 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA1_PIN]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);
	
	PORTA->PCR[PTA2_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT B pin 3 to use ALT1 which is GPIO*/
	PORTA->PCR[PTA2_PIN]|= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0x0a);;
	
	PTA->PDDR &= ~MASK(PTA1_PIN);
	PTA->PDDR &= ~MASK(PTA2_PIN);
	
	
	NVIC_SetPriority(PORTA_IRQn, 0); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);	
}

void reset_encoder() {
	encoder_pulses = 0;
}

void PORTA_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	
	// encoder 1
	if(PORTA->ISFR & MASK(PTA1_PIN)) {
		
		encoder_pulses++;
		
	// encoder 2
	} else if (PORTA->ISFR & MASK(PTA2_PIN)) {
		
		encoder_pulses++;
		
		//Do nothing
	}
	
	PORTA->ISFR = 0xffffffff;
	
	
}