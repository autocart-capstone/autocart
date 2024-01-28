#include <MKL25Z4.H>
#include "spi_setup.h""

int main()
{
	init_RGB_LEDs();
	SPI_init();

	while (1)
	{
		//loop indefinitely
	}
}