#ifndef COMMON_H
#define COMMON_H

#define MASK(x) (1UL << (x))

/* CONSTANTS */
#define pulses_per_rev 3
/* Define as floats */
#define PI 3.14159f
#define wheel_diam 6.35f
#define pivot_diam 26.6f


/* PWM PINS */
#define PTD1_PIN (1)
/* left */
#define PTD3_PIN_FL (3)
#define PTD0_PIN_BL (0)
/* right */ 
#define PTD2_PIN_FR (2)
#define PTD4_PIN_BR (4)


/* MOTOR CONTROL PINS */
// output pins (left) 
#define PTE20_PIN_LF  (20) // x- Forwards
#define PTE21_PIN_LB  (21) // -x Backwards

// output pins (right)
#define PTE22_PIN_RF  (22) // x- Forwards
#define PTE23_PIN_RB  (23) // -x Backwards

// On L298N, OUT1/OUT4 are power, OUT2/OUT3 are gnd for motors


/* ENCODER PINS */
#define PTA1_PIN_FL (1)
#define PTA2_PIN_BL (2)
#define PTA3_PIN_FR (3)
#define PTA4_PIN_BR (4)


#endif