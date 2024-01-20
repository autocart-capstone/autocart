#include <MKL25Z4.H>
#include "spi_setup.h""
#include "rx_queue.h"

/*
To configure the KL25z module controlling the motors as a slave. 
*/

Q_T RxQ;
uint8_t CR_received = 0;
void SPI_init(void){
  
		uint32_t divisor = 0;
	
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; //Turn on clock to D module
    SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;  //Enable SPI0 clock
	
		SPI0_C1 &= ~SPI_C1_SPE_MASK; //Disable SPI for config
  
		PORTD->PCR[PORTD0] &= ~PORT_PCR_MUX_MASK; //Set PTD0 to mux 2 [SPI0_PCS0]         
		PORTD->PCR[PORTD0] |= PORT_PCR_MUX(1);
		
		PORTD->PCR[PORTD1] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[PORTD1] |= PORT_PCR_MUX(0x2); //Set PTD1 to mux 2 [SPI0_SCK]
	
		PORTD->PCR[PORTD2] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[PORTD2] |= PORT_PCR_MUX(0x2); //Set PTD2 to mux 2 [SPI0_MOSI]
	
		PORTD->PCR[PORTD3] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[PORTD3] |= PORT_PCR_MUX(0x2); //Set PTD3 to mux 2 [SPIO_MISO]
		
		//PTD2 will act as the slave in (Master Out Slave In)
		//PTD3 will act as the slave out (Master in Slave Out)
  
    SPI0_C1 |= SPI_C1_MSTR(0); //Set SPI0 to Slave
		SPI0_C2 = 0x00U;
				
		/*
		//Leave blank for now, I assume this is dependent on the master as well. 
		divisor = BUS_CLOCK/(baud_rate*16);
  
    SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));
		*/
		
		SPI0_BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x00));
		  
    SPI0_C1 |= SPI_C1_SPE_MASK; //Enable SPI0
		
		SPI0_C1 |= SPI_C1_SPIE_MASK; //Enable Slave Receive Interrupts, when (SPRF is set) receive buffer is full we interrupt
		SPI0_C1 |= SPI_C1_SPTIE_MASK; //Enable Slave Transmit, when (SPTEF is set) transmit buffer is empty, we interrupt.
		
			/*Enable interrupts for SPI0 */
			NVIC_SetPriority(SPI0_IRQn, 128); // 0, 64, 128 or 192
			NVIC_ClearPendingIRQ(SPI0_IRQn); 
			NVIC_EnableIRQ(SPI0_IRQn);
}


void SPI0_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(SPI0_IRQn);
	if (SPI0->S & SPI_S_SPTEF_MASK) { //Transmit Buffer is empty
		// can send back a response
		/*
		if (!Q_Empty(&TxQ)) {
			UART2->D = Q_Dequeue(&TxQ); //Write-Only so we know it's the Tx buffer
		} else {
			// queue is empty so disable transmitter
			UART2->C2 &= ~UART_C2_TIE_MASK;
		}
		//TODO: Implement Queue
		*/
	}
	if (SPI0->S & SPI_S_SPRF_MASK) { //Receive buffer full
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
	}
}

uint8_t	get_theta_and_distance(void) {
	return Q_Dequeue(&RxQ);
}
