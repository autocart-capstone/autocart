#ifndef SPI_SETUP_H
#define SPI_SETUP_H

void SPI_init();

uint8_t	get_theta_and_distance(void);

#define PORTD0 (0)
#define PORTD1 (1)
#define PORTD2 (2)
#define PORTD3 (3)

#define BUS_CLOCK (24e6)

#endif