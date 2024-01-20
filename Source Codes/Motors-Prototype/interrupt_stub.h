#ifndef INTERRUPT_STUB_H
#define INTERRUPT_STUB_H

#define pulses_per_rev 3

extern int encoder_pulses;

void init_timer(void);

void Start_PIT(void);

void Stop_PIT(void);

void reset_encoder(void);

#endif