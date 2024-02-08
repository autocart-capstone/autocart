#include "encoder_interrupts.h"
#include "calculations.h"
#include "pin_config.h"
// Requires installation of MBED_RPI_PICO_TimerInterrupt library (tools -> Manage Libraries)
// https://github.com/khoih-prog/MBED_RPI_PICO_TimerInterrupt?tab=readme-ov-file#use-arduino-library-manager
#include "MBED_RPi_Pico_ISR_Timer.h"   
#include "MBED_RPi_Pico_TimerInterrupt.h"

// Period for timer in usec
#define TIMER_PERIOD 1000000L

/* variables to track encoder pulses elapsed for turning */
int FL_turn_pulses = 0;
int BL_turn_pulses = 0;
int FR_turn_pulses = 0;
int BR_turn_pulses = 0;

/* variables to track pulses over a period to track RPM */
int FL_speed_pulses = 0;
int BL_speed_pulses = 0;
int FR_speed_pulses = 0;
int BR_speed_pulses = 0;

float FL_mtr_RPM = 0;
float BL_mtr_RPM = 0;
float FR_mtr_RPM = 0;
float BR_mtr_RPM = 0;


void init_encoders() {

  pinMode(ENCODER_FL, INPUT);
  pinMode(ENCODER_BL, INPUT);
  pinMode(ENCODER_FR, INPUT);
  pinMode(ENCODER_BR, INPUT);

  /* Attach interrutps to encoder input pins */
  attachInterrupt(digitalPinToInterrupt(ENCODER_FL), encoder_IRQHandler, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BL), encoder_IRQHandler, RISING);  
  attachInterrupt(digitalPinToInterrupt(ENCODER_FR), encoder_IRQHandler, RISING);   
  attachInterrupt(digitalPinToInterrupt(ENCODER_BR), encoder_IRQHandler, RISING); 

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

void encoder_IRQHandler() {
  // Front Left Encoder
  if(digitalRead(ENCODER_FL) == HIGH) {
    FL_turn_pulses++;
    FL_speed_pulses++;
  } 
  // Back Left Encoder
  else if(digitalRead(ENCODER_BL) == HIGH) {
    BL_turn_pulses++;
    BL_speed_pulses++;
  } 
  // Front Right Encoder
  else if(digitalRead(ENCODER_FR) == HIGH) {
    FR_turn_pulses++;
    FR_speed_pulses++;
  } 
  // Back Right Encoder
  else if(digitalRead(ENCODER_BR) == HIGH) {
    BR_turn_pulses++;
    BR_speed_pulses++;
  }  

}

// Never use Serial.print inside this mbed ISR. Will hang the system
void TimerHandler(uint alarm_num) {

  // Always call this for MBED RP2040 before processing ISR
  TIMER_ISR_START(alarm_num);

    FL_mtr_RPM = calculate_RPM(FL_speed_pulses);
		BL_mtr_RPM = calculate_RPM(BL_speed_pulses);
		FR_mtr_RPM = calculate_RPM(FR_speed_pulses);
		BR_mtr_RPM = calculate_RPM(BR_speed_pulses);
		
		FL_speed_pulses = 0;
		BL_speed_pulses = 0;
		FR_speed_pulses = 0;
		BR_speed_pulses = 0;
		
  // Always call this for MBED RP2040 after processing ISR
  TIMER_ISR_END(alarm_num);
}