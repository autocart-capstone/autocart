#ifndef USER_DEFS_H
#define USER_DEFS_H

#define MASK(x) (1UL << (x))

void init_echo(void);
void init_buzzer(void);
void INIT_TRIGGER(void);
void Display_Range(int b);
void Display_Left(int b);
void Display_Front(int b);
void Display_Right(int b);
void PORTD_IRQHandler(void);
void PORTA_IRQHandler(void);
	
#define FRONT_ECHO (6) //Port D Pin 6
#define FRONT_TRIGGER (1) //Port B Pin 1
#define BUZZER_PIN (2) //Port C Pin 2
#define LEFT_ECHO (1) //PORT A Pin 1
#define LEFT_TRIGGER (3) //PORT B Pin 3
#define RIGHT_ECHO (2) //PORT A Pin 2
#define RIGHT_TRIGGER (2) //PORT B Pin 2

#define NUM_RANGE_STEPS (6) //6 different colours 

#define TPM_MODULE TPM0
#define TPM_CHANNEL 1 

#define RED (0)
#define GREEN (1)
#define BLUE (2)

#endif
// *******************************ARM University Program Copyright ? ARM Ltd 2013*************************************   
