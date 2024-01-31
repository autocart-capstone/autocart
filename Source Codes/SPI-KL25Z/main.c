#include <MKL25Z4.H>
#include "spi_setup.h"
#include "led.h"

int main()
{
	init_RGB_LEDs();
	SPI_init_e();

	while (1)
	{
		//loop indefinitely
	}
}