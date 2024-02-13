#ifndef SPI_SETUP_H
#define SPI_SETUP_H

void spi_master_setup();

uint8_t send_data_request(bool objectDetection);

#define SERIAL_BAUDRATE (9600)

#endif
