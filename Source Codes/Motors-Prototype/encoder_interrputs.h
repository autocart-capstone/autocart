#ifndef ENCODER_INTERRUPTS_H
#define ENCODER_INTERRUPTS_H

extern int enc_1_turn_pulses;
extern int enc_2_turn_pulses;

extern int enc_1_speed_pulses;
extern int enc_2_speed_pulses;

extern float mtr_1_RPM;
extern float mtr_2_RPM;

void init_encoders(void);
void init_RPM_timer(void);

void reset_encoders(void);

void Start_PIT(void);
void Stop_PIT(void);


#endif
