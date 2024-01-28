#include "pin_config.h"
#include "common.h"
#include "MKL25Z4.h"

void init_PWM(void) {
	/* Enable Port D clock Gating */ 
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; 
	
	PORTD->PCR[PTD0_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT D pin 0 to use ALT4 which is TPM0_CH0*/
	PORTD->PCR[PTD0_PIN]|= PORT_PCR_MUX(4);
	
	PORTD->PCR[PTD1_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT D pin 1 to use ALT4 which is TPM0_CH1*/
	PORTD->PCR[PTD1_PIN]|= PORT_PCR_MUX(4);

	PORTD->PCR[PTD2_PIN]&= ~PORT_PCR_MUX_MASK; 
	/*Set PORT D pin 2 to use ALT4 which is TPM0_CH2*/
	PORTD->PCR[PTD2_PIN]|= PORT_PCR_MUX(4);
	
	/*Enable the clock for TPM0 by masking bit 25*/
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK; 
	
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK; 
	
	/*Clear PLLFLLSEL clock select so don't divide by two and use MCGFLLCLK, refer to page 124 in manual*/
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	
	/*Set as MCGFLLCLK*/
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); 
	
	//TPM1->CONTROLS->CnV = (50 * TPM1->MOD) / 100; 
	
	/*Modulo value 48000000/128 = 375000/7500 = 50 Hz*/
	/*48Mhz divided by 128 which is the prescalre set in SC register below*/
	/*375kHz, counter goes up once every clock tick and we only count up to 7500 to get the period which is now 50 Hz*/
	/*Period is 0.02 seconds, and this happens 50 times in one second hence 50 Hz*/
	TPM0->MOD = 7500; 
	
	TPM0->SC &= ~((TPM_SC_PS_MASK | TPM_SC_CMOD_MASK));
	/*Set prescaler to 128 and set LPTPM to increment on every clock tick*/
	TPM0->SC |= TPM_SC_PS(7) | TPM_SC_CMOD(1);
	/*Count up to 7500 and then reset to 0 instead of counting back down from 7500*/
	/*IN up-count: TOF bit is set when we hit 7499, we reset the period*/
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK); 
	
	/*Set ELSB as 1 and MSB as 1 for Center Aligned PWM so we're high-true pulses*/
	TPM0_C0SC &= ~((TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK)); 
	TPM0_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
	
	TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK)); 
	TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
}

void init_direction_pins(void) {
	
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