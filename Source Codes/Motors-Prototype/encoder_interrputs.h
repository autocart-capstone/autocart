#ifndef ENCODER_INTERRUPTS_H
#define ENCODER_INTERRUPTS_H

extern int FL_turn_pulses;
extern int BL_turn_pulses;
extern int FR_turn_pulses;
extern int BR_turn_pulses;

extern int FL_speed_pulses;
extern int BL_speed_pulses;
extern int FR_speed_pulses;
extern int BR_speed_pulses;

extern float FL_mtr_RPM;
extern float BL_mtr_RPM;
extern float FR_mtr_RPM;
extern float BR_mtr_RPM;

void init_encoders(void);
void init_RPM_timer(void);

void reset_encoders(void);

void Start_PIT(void);
void Stop_PIT(void);

#endif
