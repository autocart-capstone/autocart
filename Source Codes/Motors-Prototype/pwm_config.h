#ifndef PWM_CONFIG_H
#define PWM_CONFIG_H

void init_PWM();

void init_enable();

#define MASK(x) (1UL << (x))

#define PTD0_PIN (0)
#define PTD1_PIN (1)

// output pins
#define PTE20_PIN  (20)
#define PTE21_PIN  (21)

#endif