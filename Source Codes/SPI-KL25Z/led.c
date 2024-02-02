#include <MKL25Z4.H>
#include "led.h"

void init_RGB_LEDs(void) {
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);            
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);     
	
	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
}

void control_LED(uint8_t cmd) {
	if (cmd == STOP){
			PTB->PCOR = MASK(RED_LED_POS);
	} else {
			PTB->PSOR = MASK(RED_LED_POS);
	}

	if (cmd == GO){
			PTD->PCOR = MASK(BLUE_LED_POS);
	} else {
			PTD->PSOR = MASK(BLUE_LED_POS);
	}
}	
