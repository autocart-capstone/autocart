#ifndef INTERRUPT_STUB_H
#define INTERRUPT_STUB_H

#define MASK(x) (1UL << (x))

void init_timer(void);

void Start_PIT(void);

void Stop_PIT(void);


#endif