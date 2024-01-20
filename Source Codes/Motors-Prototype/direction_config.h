#ifndef DIRECTION_CONFIG_H
#define DIRECTION_CONFIG_H

void init_direction_pins(void);

#define MASK(x) (1UL << (x))

// Left motor is attached backwards (When using IN3/IN4 to send forwards, will go backwards)
// On L298N, OUT1/OUT4 are power, OUT2/OUT3 are gnd for motors

// output pins (left) 
#define PTE20_PIN  (20) // x- Forwards
#define PTE21_PIN  (21) // -x Backwards

// output pins (right)
#define PTE22_PIN  (22) // x- Forwards
#define PTE23_PIN  (23) // -x Backwards


#endif