#include <MKL25Z4.H>
#include "user_defs.h"
#include "LEDs.h"
#include <time.h>

volatile uint32_t msTicks; // counts the number of SysTick interrupts
volatile uint32_t time_elapsed;
volatile int32_t start_time;
volatile int32_t end_time;
volatile int32_t start_time_r;
volatile int32_t end_time_r;
volatile int32_t start_time_l;
volatile int32_t end_time_l;
volatile int32_t count = 0;
volatile int32_t right_count = 0;
volatile int32_t left_count = 0;


void init_echo(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; /* enable clock for port D */

	//Pull Enable, IRQC --> Rising Edge Interrupts 
	PORTD->PCR[FRONT_ECHO] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x09);
	//Pull Select --> Pull Down
	PORTD->PCR[FRONT_ECHO] &= ~PORT_PCR_PS_MASK;
	
	/* Set port D switch bit to inputs */
	PTD->PDDR &= ~MASK(FRONT_ECHO);
	
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; /* enable clock for port A */

	//Pull Enable, IRQC --> Rising Edge Interrupts 
	PORTA->PCR[LEFT_ECHO] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x09);
	//Pull Select --> Pull Down
	PORTA->PCR[LEFT_ECHO] &= ~PORT_PCR_PS_MASK;
	//Pull Enable, IRQC --> Rising Edge Interrupts 
	PORTA->PCR[RIGHT_ECHO] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x09);
	//Pull Select --> Pull Down
	PORTA->PCR[RIGHT_ECHO] &= ~PORT_PCR_PS_MASK;
	
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(FRONT_ECHO);
	
	

	/* Enable Interrupts */
	NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192, gives the port the priority
	NVIC_ClearPendingIRQ(PORTD_IRQn); //Clear any pending IRQs
	NVIC_EnableIRQ(PORTD_IRQn); //Enable IRQ for Port D
	
	NVIC_SetPriority(PORTA_IRQn, 64); // 0, 64, 128 or 192, gives the port the priority
	NVIC_ClearPendingIRQ(PORTA_IRQn); //Clear any pending IRQs
	NVIC_EnableIRQ(PORTA_IRQn); //Enable IRQ for Port A
}


void init_buzzer(void) {
    // Enable clock to Port C
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

    // Set PTC2 as GPIO
    PORTC->PCR[BUZZER_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTC->PCR[BUZZER_PIN] |= PORT_PCR_MUX(1);

    // Set PTC2 as output
    GPIOC->PDDR |= (1 << BUZZER_PIN);

    // Configure TPM1 for PWM
    SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

    // Use MCGFLLCLK as the clock source for TPM1
    SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    // Set TPM1 clock source to the fixed frequency clock
    TPM1->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);

    // Set TPM1 to count up
    TPM1->SC |= TPM_SC_CPWMS_MASK;

    // Set TPM1 to PWM mode
    TPM1->CONTROLS[0].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;

    // Set the period of the PWM signal
    TPM1->MOD = 1000; // Adjust this value to set the PWM period

	// Set the PWM frequency (1000Hz)
    TPM1->CONTROLS[0].CnV = TPM1->MOD / 1000;

}

int Threshold[NUM_RANGE_STEPS] = {12000, 9000, 6000, 3000, 1000, 0};

const int Colors[NUM_RANGE_STEPS][3] = {{ 1, 1, 1}, // white
																	{ 1, 0, 1}, // magenta
																	{ 1, 0, 0}, // red
																	{ 1, 1, 0}, // yellow
																	{ 0, 0, 1}, // blue
																	{ 0, 1, 0}};// green
																	 

void Display_Left(int b) {
	if(b < 3000 && 0 < b) {
		Green_On(1);
	}
	else {
		Green_On(0);
	}
}

void Display_Front(int b) {
	if(b < 3000 && 0 < b) {
		Red_On(1);
	}
	else {
		Red_On(0);
	}
}

void Display_Right(int b) {
	if(b < 3000 && 0 < b) {
		Blue_On(1);
	}
	else {
		Blue_On(0);
	}
}


void SysTick_Handler(void) {
    msTicks++;
}

uint32_t read_time_elapsed() {
    return msTicks;
}

//Port D IRQ HANDLER
void PORTD_IRQHandler(void) {
   //start_time = read_time_elapsed();
   NVIC_ClearPendingIRQ(PORTD_IRQn);
	 start_time = count;
   while(PTD->PDIR & MASK(FRONT_ECHO)){
		 count++;
	 }	
	 end_time = count;
	 Display_Front(end_time - start_time);

	// end_time = read_time_elapsed();
	 PORTD->ISFR = 0xffffffff;

}

void PORTA_IRQHandler(void) {
	//start_time = read_time_elapsed();
  NVIC_ClearPendingIRQ(PORTA_IRQn);
	start_time_l = left_count;
	start_time_r = right_count;
	
  while(PTA->PDIR & MASK(RIGHT_ECHO) || PTA->PDIR & MASK(LEFT_ECHO)){
		if (PTA->PDIR & MASK(RIGHT_ECHO)) {
			right_count++;
		}
		else if (PTA->PDIR & MASK(LEFT_ECHO)) {
			left_count++;
		}
	}	
	end_time_l = left_count;
	end_time_r = right_count;
	Display_Left(end_time_l - start_time_l);
	Display_Right(end_time_r - start_time_r);

	// end_time = read_time_elapsed();
	PORTA->ISFR = 0xffffffff;
}
