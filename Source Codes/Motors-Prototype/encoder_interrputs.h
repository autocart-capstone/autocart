#ifndef ENCODER_INTERRUPTS_H
#define ENCODER_INTERRUPTS_H

#define MASK(x) (1UL << (x))

#define pulses_per_rev 3
#define PTA1_PIN (1)
#define PTA2_PIN (2)

extern int encoder_pulses;

void init_encoder(void);
void reset_encoder(void);

#endif ENCODER_INTERRUPTS_H
