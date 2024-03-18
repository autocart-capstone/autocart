#ifndef ENCODER_INTERRUPTS_H
#define ENCODER_INTERRUPTS_H

#define PULSES_PER_REV 90.0f

extern volatile int FL_turn_pulses;
extern volatile int BL_turn_pulses;
extern volatile int FR_turn_pulses;
extern volatile int BR_turn_pulses;

extern volatile int FL_speed_pulses;
extern volatile int BL_speed_pulses;
extern volatile int FR_speed_pulses;
extern volatile int BR_speed_pulses;

extern float FL_mtr_RPM;
extern float BL_mtr_RPM;
extern float FR_mtr_RPM;
extern float BR_mtr_RPM;

void init_encoders();
void init_RPM_timer();
void reset_encoders();

float getMotorRPM(int mtr_index);
bool check_all_motor_RPM(int RPM);

int getAvgPulsesLeft();
int getAvgPulsesRight();

#endif