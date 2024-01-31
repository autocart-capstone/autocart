#include <MKL25Z4.H>
#include "led.h"

void init_RGB_LEDs(void) {
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);                 
	
	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
}

void control_LED(uint8_t cmd) {
	if (cmd == STOP){
			PTB->PSOR = MASK(GREEN_LED_POS);
			PTB->PCOR = MASK(RED_LED_POS);
	}
	if (cmd == GO){
			PTB->PSOR = MASK(RED_LED_POS); 
			PTB->PCOR = MASK(GREEN_LED_POS);
	}
}	
