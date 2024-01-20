#ifndef PWM_CONFIG_H
#define PWM_CONFIG_H

void init_PWM(void);

void init_enable(void);

#define MASK(x) (1UL << (x))

#define PTD0_PIN (0)
#define PTD1_PIN (1)
#define PTD2_PIN (2)

#endif