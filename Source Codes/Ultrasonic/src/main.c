#include <MKL25Z4.H>
#include "user_defs.h"
#include "LEDs.h"
#include <time.h>


void INIT_TRIGGER(void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[FRONT_TRIGGER] &= ~PORT_PCR_MUX_MASK; //Clears what's currently in the PCR MUX         
	PORTB->PCR[FRONT_TRIGGER] |= PORT_PCR_MUX(1); // PORT_PCR_MUX(001) is for the Pin Mux Control, 001 sets IR Pin as GPIO 
	PTB->PDDR |= MASK(FRONT_TRIGGER); //PDDR or Port Data Direction Register, Inputs -> 0, Outputs ->1. This SETS (1) the specified bits (configuring it as outputs)
	
	// start off with Trigger turned off
	PTB->PCOR = MASK(FRONT_TRIGGER); //Turn off Trigger
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[LEFT_TRIGGER] &= ~PORT_PCR_MUX_MASK; //Clears what's currently in the PCR MUX         
	PORTB->PCR[LEFT_TRIGGER] |= PORT_PCR_MUX(1); // PORT_PCR_MUX(001) is for the Pin Mux Control, 001 sets IR Pin as GPIO 
	PTB->PDDR |= MASK(LEFT_TRIGGER); //PDDR or Port Data Direction Register, Inputs -> 0, Outputs ->1. This SETS (1) the specified bits (configuring it as outputs)
	
	// start off with Trigger turned off
	PTB->PCOR = MASK(RIGHT_TRIGGER); //Turn off Trigger
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[RIGHT_TRIGGER] &= ~PORT_PCR_MUX_MASK; //Clears what's currently in the PCR MUX         
	PORTB->PCR[RIGHT_TRIGGER] |= PORT_PCR_MUX(1); // PORT_PCR_MUX(001) is for the Pin Mux Control, 001 sets IR Pin as GPIO 
	PTB->PDDR |= MASK(RIGHT_TRIGGER); //PDDR or Port Data Direction Register, Inputs -> 0, Outputs ->1. This SETS (1) the specified bits (configuring it as outputs)
	
	// start off with Trigger turned off
	PTB->PCOR = MASK(RIGHT_TRIGGER); //Turn off Trigger
}

void init_tpm(void){
	  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; // Enable TPM0 clock

    TPM0->SC = 0; // Disable the TPM counter

    TPM0->MOD = 0xFFFF; // Set the modulo value to the maximum

    TPM0->SC |= TPM_SC_PS(7); // Prescaler of 128
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // Select the source for the TPM counter as the system clock (01 - MCGFLLCLK)
    TPM0->SC |= TPM_SC_CMOD(1); // Select the internal input clock for TPM
}

void init_systick() {
    SysTick_Config(SystemCoreClock / 1000); // Configure SysTick to interrupt every millisecond
}

void Delay_us(volatile unsigned int time_del) {
	// This is a very imprecise and fragile implementation!
	time_del = 9*time_del + time_del/2; 
	while (time_del--) {
		;
	}
}
/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	INIT_TRIGGER();
	init_echo();
	//init_buzzer();
	Init_RGB_LEDs();
	init_tpm();
	//SystemCoreClockUpdate(); // Update SystemCoreClock variable
  //init_systick(); // Initialize SysTick

	__enable_irq();
	
	Green_On(0);
	Red_On(0);
	Blue_On(0);
	
	Delay_us(100);


	while(1){

		PTB->PSOR = MASK(FRONT_TRIGGER); //Turn ON Front Trigger
		Delay_us(10);
		PTB->PCOR = MASK(FRONT_TRIGGER); //Turn OFF Front Trigger
		
		Delay_us(1000);
		
		PTB->PSOR = MASK(LEFT_TRIGGER); //Turn ON Left Trigger
		Delay_us(10);
		PTB->PCOR = MASK(LEFT_TRIGGER); //Turn OFF Left Trigger
		
		Delay_us(1000);
		
		
		PTB->PSOR = MASK(RIGHT_TRIGGER); //Turn ON Right Trigger
		Delay_us(10);
		PTB->PCOR = MASK(RIGHT_TRIGGER); //Turn OFF Right Trigger
		
		Delay_us(1000);
	}
}

// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************
