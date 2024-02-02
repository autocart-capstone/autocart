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
#define PTD0_PIN (0)
#define PTD1_PIN (1)
#define PTD2_PIN (2)


/* MOTOR CONTROL PINS */
// output pins (left) 
#define PTE20_PIN  (20) // x- Forwards
#define PTE21_PIN  (21) // -x Backwards

// output pins (right)
#define PTE22_PIN  (22) // x- Forwards
#define PTE23_PIN  (23) // -x Backwards

// On L298N, OUT1/OUT4 are power, OUT2/OUT3 are gnd for motors


/* ENCODER PINS */
#define PTA1_PIN (1)
#define PTA2_PIN (2)


#endif