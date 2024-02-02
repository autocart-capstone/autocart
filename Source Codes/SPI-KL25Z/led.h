#include <MKL25Z4.H>

#ifndef LEDS_H
#define LEDS_H

// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)

#define MASK(x) (1UL << (x))

#define STOP (0x01)
#define GO (0x00)

// function prototypes
void control_LED(uint8_t cmd);
void init_RGB_LEDs(void);

#endif 