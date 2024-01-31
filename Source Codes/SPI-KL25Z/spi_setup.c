#include <MKL25Z4.H>
#include "spi_setup.h""
#include "rx_queue.h"
#include "led.h"

//#define QUEUE_NEEDED
#define LED_DEMO

/*
To configure the KL25z module controlling the motors as a slave. 
*/

Q_T RxQ;
uint8_t CR_received = 0;
void SPI_init(void){
  	
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; //Turn on clock to D module
    SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;  //Enable SPI0 clock
	
		SPI0_C1 &= ~SPI_C1_SPE_MASK; //Disable SPI for config
  
		PORTD->PCR[PORTD0] &= ~PORT_PCR_MUX_MASK; //Set PTD0 to mux 2 [SPI0_PCS0]         
		PORTD->PCR[PORTD0] |= PORT_PCR_MUX(0x2);
		
		PORTD->PCR[PORTD1] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[PORTD1] |= PORT_PCR_MUX(0x2); //Set PTD1 to mux 2 [SPI0_SCK]
	
		PORTD->PCR[PORTD2] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[PORTD2] |= PORT_PCR_MUX(0x2); //Set PTD2 to mux 2 [SPI0_MOSI]
	
		PORTD->PCR[PORTD3] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[PORTD3] |= PORT_PCR_MUX(0x2); //Set PTD3 to mux 2 [SPIO_MISO]
				  
		/* Set Configuration register | Clock Polarity idles high (active high -> needs to match master) | Clock Phase SPSCK occurs at the start of the first cycle*/
		//SPI0_C1 = (SPI_C1_CPOL_MASK | SPI_C1_CPHA_MASK);
		
		SPI0_C1 |= SPI_C1_SPIE_MASK; //Enable Slave Receive Interrupts, when (SPRF is set) receive buffer is full we interrupt
		//SPI0_C1 |= SPI_C1_SPTIE_MASK; //Enable Slave Transmit, when (SPTEF is set) transmit buffer is empty, we interrupt.
		
		//SPI0_BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x00)); //No Baud rate divider
		
		SPI0_C1 |= SPI_C1_SPE_MASK; //Enable SPI0
		
		/*Enable interrupts for SPI0 */
		NVIC_SetPriority(SPI0_IRQn, 128); // 0, 64, 128 or 192
		NVIC_ClearPendingIRQ(SPI0_IRQn); 
		NVIC_EnableIRQ(SPI0_IRQn);
}

void SPI_init_e(void){
  	
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
		SPI1_C1 = (SPI_C1_CPOL_MASK | SPI_C1_CPHA_MASK); /* Set Configuration register */
	 // SPI1_C1 = (SPI_C1_CPOL_MASK ); //CPOL=1,CPHA=0
		//SPI1_C1 = (SPI_C1_CPHA_MASK );//CPOL=0,CPHA=1;
  	SPI1_C2 = 0x00U;                     /* Set Configuration register */
    SPI1_BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x00)); /* Set baud rate register */
    SPI1_C1 |= SPI_C1_SPE_MASK;          /* Enable device */
		
		SPI1_C1 |= SPI_C1_SPIE_MASK;
		
		/*Enable interrupts for SPI0 */
		NVIC_SetPriority(SPI1_IRQn, 128); // 0, 64, 128 or 192
		NVIC_ClearPendingIRQ(SPI1_IRQn); 
		NVIC_EnableIRQ(SPI1_IRQn);
}


void SPI0_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(SPI0_IRQn);
	if (SPI0->S & SPI_S_SPTEF_MASK) { //Transmit Buffer is empty
		/*For this implementation, nothing is being done when trasmit buffer is empty because nothing is being sent back to master...might be changed later*/
	}
	if (SPI0->S & SPI_S_SPRF_MASK) { //Receive buffer full
		
		#ifdef LED_DEMO
		
		c = SPI0_D; //read the value in the buffer. Current implementation is:
		/*
		* c == 0x01 -> GO
		* c == 0x00 -> STOPPED
		* bypass queue for now
		*/
		
		control_LED(c);
		
		#endif
		
		#ifdef QUEUE_NEEDED
		if (!Q_Full(&RxQ)) {
			c = SPI0_D; //Read the value in the buffer and then add it to the queue below. 
			Q_Enqueue(&RxQ, c);
			if (c == '\r') {
				CR_received++;
			}
		} else {
			// error - queue full.
			while (1)
				;
		}
		#endif
		
	}
}

void SPI1_IRQHandler(void) {
	
	uint8_t c;
	
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
	

