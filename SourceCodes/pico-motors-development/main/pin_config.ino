#include "pin_config.h"
#include "calculations.h"

void setup_pwm()
{
  pinMode(PWM_TL, OUTPUT);
  pinMode(PWM_BL, OUTPUT);
  pinMode(PWM_TR, OUTPUT);
  pinMode(PWM_BR, OUTPUT);   
}

//Struct to store values of duty cycle. 
static struct duty_cycles {
  int TL, BL; // Front and Back left
  int TR, BR; // Front and Back right
}duty_cycles;

//Temp Function for storing PWM
void check_and_set_pin(unsigned int pwm_pin, unsigned int duty_cycle)
{
  switch (pwm_pin)
  {
    case PWM_TL:
      duty_cycles.TL = duty_cycle;
    case PWM_BL:
      duty_cycles.BL = duty_cycle;
    case PWM_TR:
      duty_cycles.TR = duty_cycle;
    case PWM_BR:
      duty_cycles.BR = duty_cycle;
  }
}

void set_pwm_duty_cycle(unsigned int pwm_pin, unsigned int duty_cycle)
{
  analogWrite(pwm_pin, (255 * duty_cycle) / 100); //set duty cycle to passed in value
  check_and_set_pin(pwm_pin, duty_cycle);
}

void stop_motor(unsigned int pwm_pin)
{
  analogWrite(pwm_pin, 0); //Set duty cycle to 0 to stop specified motor.
  check_and_set_pin(pwm_pin, 0);
}

void pivot_left() {
  
  /* Drive Motor 1 backwards*/
  digitalWrite(DIRECTION_LF, 1);
  digitalWrite(DIRECTION_LB, 0);
  
  /* Drive Motor 2 forwards*/
  digitalWrite(DIRECTION_RF, 1);
  digitalWrite(DIRECTION_RB, 0);
  
  // Stub for detecting when we have turned 90 deg
}

void pivot_right() {
  
  /* Drive Motor 1 forwards*/
  digitalWrite(DIRECTION_LF, 0);
  digitalWrite(DIRECTION_LB, 1);
  
  /* Drive Motor 2 backwards*/
  digitalWrite(DIRECTION_RF, 0);
  digitalWrite(DIRECTION_RB, 1);
  
  // Stub for detecting when we have turned 90 deg
}

// Calculations for two wheels (prototype)
int turn_theta(float angle) {

  bool turning_right = false; 
  
  if(angle > 270) {
    turning_right = true;
    angle = 360 - angle;
  } 

  int pulses = calculate_pulses_for_angle(angle);
  float RPM_factor = (pulses / PULSES_PER_REV);
  
  if(turning_right) {
    control_right_motors(duty_cycles.TR - (duty_cycles.TR * RPM_factor), 
                         duty_cycles.BR - (duty_cycles.BR * RPM_factor));
  } else {
    control_left_motors(duty_cycles.TL - (duty_cycles.TL * RPM_factor), 
                        duty_cycles.BL - (duty_cycles.BL * RPM_factor));
  }
  
  return pulses;
}

void control_left_motors(float T_PWM, float B_PWM) {
  set_pwm_duty_cycle(PWM_TL, T_PWM);
  set_pwm_duty_cycle(PWM_BL, B_PWM);
}

void control_right_motors(float T_PWM, float B_PWM) {
  set_pwm_duty_cycle(PWM_TR, T_PWM);
  set_pwm_duty_cycle(PWM_BR, B_PWM);
}
