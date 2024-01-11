#include "MKL25Z4.h"
#include "pwm_config.h"

void init_enable() {
	
  SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; /* enable clock for port D */
  SIM->SCGC5 |=  SIM_SCGC5_PORTE_MASK; /* enable clock for port E */
	
	PORTD->PCR[PTD2_PIN] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTD->PCR[PTD3_PIN] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	PORTD->PCR[PTD5_PIN] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	
	
	PORTE->PCR[PTE20_PIN] |= PORT_PCR_MUX(1);
	PORTE->PCR[PTE21_PIN] |= PORT_PCR_MUX(1);
	
	PTE->PDDR |= MASK(PTE20_PIN);
	PTE->PDDR |= MASK(PTE21_PIN);
	
	NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192, gives the port the priority
	NVIC_ClearPendingIRQ(PORTD_IRQn); //Clear any pending IRQs
	NVIC_EnableIRQ(PORTD_IRQn); //Enable IRQ for Port D
}

void PORTD_IRQHandler(void) {
    // clear pending interrupts
    NVIC_ClearPendingIRQ(PORTD_IRQn);
	
    if ((PORTD->ISFR & MASK(PTD2_PIN) && !(PORTD->ISFR & MASK(PTD3_PIN)) && !(PORTD->ISFR & MASK(PTD5_PIN)))) {
			PTE->PCOR = MASK(PTE21_PIN);
			PTE->PSOR = MASK(PTE20_PIN);
    }
		
		if ((PORTD->ISFR & MASK(PTD3_PIN) && !(PORTD->ISFR & MASK(PTD2_PIN)) && !(PORTD->ISFR & MASK(PTD5_PIN)))) {
			PTE->PCOR = MASK(PTE20_PIN);
			PTE->PSOR = MASK(PTE21_PIN);
    }
		
		else if ((PORTD->ISFR & MASK(PTD5_PIN) && !(PORTD->ISFR & MASK(PTD3_PIN)) && !(PORTD->ISFR & MASK(PTD2_PIN)))) {
			PTE->PCOR = MASK(PTE20_PIN);
			PTE->PCOR = MASK(PTE21_PIN);
    }
		
    // clear status flags 
    PORTD->ISFR = 0xffffffff;
}