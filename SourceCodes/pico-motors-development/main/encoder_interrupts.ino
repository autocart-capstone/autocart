#include "encoder_interrupts.h"
#include "calculations.h"
#include "pin_config.h"
// Requires installation of MBED_RPI_PICO_TimerInterrupt library (tools -> Manage Libraries)
// https://github.com/khoih-prog/MBED_RPI_PICO_TimerInterrupt?tab=readme-ov-file#use-arduino-library-manager
#include "MBED_RPi_Pico_ISR_Timer.h"
#include "MBED_RPi_Pico_TimerInterrupt.h"

// Period for timer in usec (0.1s)
#define TIMER_PERIOD 100000L

/* variables to track encoder pulses elapsed for turning */
volatile int FL_turn_pulses = 0;
volatile int BL_turn_pulses = 0;
volatile int FR_turn_pulses = 0;
volatile int BR_turn_pulses = 0;

/* variables to track pulses over a period to track RPM */
volatile int FL_speed_pulses = 0;
volatile int BL_speed_pulses = 0;
volatile int FR_speed_pulses = 0;
volatile int BR_speed_pulses = 0;

// FL, BL, FR, BR
float motor_RPM[NUM_MOTORS] = { 0, 0, 0, 0 };

void init_encoders() {

  pinMode(ENCODER_FL, INPUT);
  pinMode(ENCODER_BL, INPUT);
  pinMode(ENCODER_FR, INPUT);
  pinMode(ENCODER_BR, INPUT);

  digitalWrite(ENCODER_FL, INPUT_PULLDOWN);
  digitalWrite(ENCODER_BL, INPUT_PULLDOWN);
  digitalWrite(ENCODER_FR, INPUT_PULLDOWN);
  digitalWrite(ENCODER_BR, INPUT_PULLDOWN);

  /* Attach interrutps to encoder input pins */
  attachInterrupt(digitalPinToInterrupt(ENCODER_FL), FL_encoder_IRQHandler, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BL), BL_encoder_IRQHandler, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_FR), FR_encoder_IRQHandler, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BR), BR_encoder_IRQHandler, RISING);
}

void init_RPM_timer() {
  MBED_RPI_PICO_Timer ITimer(0);
  // interval (in us), callback is ISR
  ITimer.attachInterruptInterval(TIMER_PERIOD, TimerHandler);
}

void reset_encoders() {
  FL_turn_pulses = 0;
  BL_turn_pulses = 0;
  FR_turn_pulses = 0;
  BR_turn_pulses = 0;
}

void FL_encoder_IRQHandler() {
  FL_turn_pulses++;
  FL_speed_pulses++;
}

void BL_encoder_IRQHandler() {
  BL_turn_pulses++;
  BL_speed_pulses++;
}

void FR_encoder_IRQHandler() {
  FR_turn_pulses++;
  FR_speed_pulses++;
}

void BR_encoder_IRQHandler() {
  BR_turn_pulses++;
  BR_speed_pulses++;
}

float getMotorRPM(int mtr_index) {
  return motor_RPM[mtr_index];
}

bool check_all_motor_RPM(int RPM) {
  for (int i = 1; i < NUM_MOTORS; i++) {
    if (getMotorRPM(i) != RPM) {
      return false;
    }
  }
  return true;
}

int getAvgPulsesLeft() {
  // BL_turn_pulses replaced with FL_turn_pulses since motor encoder is broken
  return (BL_turn_pulses + BL_turn_pulses) / 2;
}

int getAvgPulsesRight() {
  return (FR_turn_pulses + BR_turn_pulses) / 2;
}

// Never use Serial.print inside this mbed ISR. Will hang the system
void TimerHandler(uint alarm_num) {
  // Always call this for MBED RP2040 before processing ISR
  TIMER_ISR_START(alarm_num);

  motor_RPM[0] = calculate_RPM(FL_speed_pulses);
  motor_RPM[1] = calculate_RPM(BL_speed_pulses);
  motor_RPM[2] = calculate_RPM(FR_speed_pulses);
  motor_RPM[3] = calculate_RPM(BR_speed_pulses);

  FL_speed_pulses = 0;
  BL_speed_pulses = 0;
  FR_speed_pulses = 0;
  BR_speed_pulses = 0;

  // Always call this for MBED RP2040 after processing ISR
  TIMER_ISR_END(alarm_num);
}
