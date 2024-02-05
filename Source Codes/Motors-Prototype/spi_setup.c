#include <MKL25Z4.H>
#include "spi_setup.h"
#include "led.h"

//#define QUEUE_NEEDED
#define LED_DEMO

/*
To configure the KL25z module controlling the motors as a slave. 
*/

void SPI_init(void){
  	
		// enable clock gate for spi module
	  SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;
	  // enable PORT
	  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
  	
  	// disable SPI
  	SPI1_C1 &= ~SPI_C1_SPE_MASK;
 
  	// configure I/O to SPI function
  	PORTE_PCR1 &= ~PORT_PCR_MUX_MASK;
		PORTE_PCR1 |= PORT_PCR_MUX(2)|PORT_PCR_DSE_MASK;			  //Use PTE1 as SPI1_MOSI
    PORTE_PCR2 &= ~PORT_PCR_MUX_MASK;
		PORTE_PCR2 |= PORT_PCR_MUX(2)|PORT_PCR_DSE_MASK;			  //Use PTE2 as SPI1_SCK
    PORTE_PCR4 &= ~PORT_PCR_MUX_MASK;
		PORTE_PCR4 = PORT_PCR_MUX(2)|PORT_PCR_DSE_MASK;			    //Use PTE4 as SPI1_SS_b 
    
    SPI1_C1 &= ~ SPI_C1_CPHA_MASK;		
		 //SPI1_C1 = (SPI_C1_CPOL_MASK | SPI_C1_CPHA_MASK); /* Set Configuration register */
	   //SPI1_C1 = (SPI_C1_CPOL_MASK ); //CPOL=1,CPHA=0
	  SPI1_C1 = (SPI_C1_CPHA_MASK );//CPOL=0,CPHA=1;
  	//SPI1_C2 = 0x00U;                     /* Set Configuration register */
		
    //SPI1_BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x00)); /* Set baud rate register */
		
		SPI1_C1 |= SPI_C1_SPIE_MASK;
    SPI1_C1 |= SPI_C1_SPE_MASK;          /* Enable device */
		
		/*Enable interrupts for SPI0 */
		NVIC_SetPriority(SPI1_IRQn, 128); // 0, 64, 128 or 192
		NVIC_ClearPendingIRQ(SPI1_IRQn); 
		NVIC_EnableIRQ(SPI1_IRQn);
}
void SPI1_IRQHandler(void) {
	
	uint8_t c = 0x00;
	
	NVIC_ClearPendingIRQ(SPI1_IRQn);
	
	if (SPI1->S & SPI_S_SPRF_MASK)//Receive buffer full
	{
		c = SPI1_D; //read the value in the buffer. Current implementation is:
		/*
		* c == 0x01 -> GO
		* c == 0x00 -> STOPPED
		* bypass queue for now
		*/
		control_LED(c);
	}
}
	