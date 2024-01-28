#include "direction_config.h"
#include "common.h"
#include "MKL25Z4.h"

void init_direction_pins() {
	
	/* Enable Port D clock Gating */ 
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; 
	
	PORTE->PCR[PTE20_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT E pin 20 to use ALT1 which is GPIO*/
	PORTE->PCR[PTE20_PIN]|= PORT_PCR_MUX(1);
	
	PORTE->PCR[PTE21_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT E pin 21 to use ALT1 which is GPIO*/
	PORTE->PCR[PTE21_PIN]|= PORT_PCR_MUX(1);
	
	PORTE->PCR[PTE22_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT E pin 22 to use ALT1 which is GPIO*/
	PORTE->PCR[PTE22_PIN]|= PORT_PCR_MUX(1);
	
	PORTE->PCR[PTE23_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT E pin 23 to use ALT1 which is GPIO*/
	PORTE->PCR[PTE23_PIN]|= PORT_PCR_MUX(1);
	
	/*Set Pins to Output*/
	PTE->PDDR |= MASK(PTE20_PIN)| MASK(PTE21_PIN) | MASK(PTE22_PIN)| MASK(PTE23_PIN);
	
}
