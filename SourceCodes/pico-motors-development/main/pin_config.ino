#include "pin_config.h"
#include "calculations.h"

//Struct to store values of duty cycle. 
static struct duty_cycles {
  int TL, BL; // Front and Back left
  int TR, BR; // Front and Back right
}duty_cycles;


static const uint8_t motors_pins[4] = {PWM_TL, PWM_BL, PWM_TR, PWM_BR}; 


void setup_pwm()
{
  pinMode(PWM_TL, OUTPUT);
  pinMode(PWM_BL, OUTPUT);
  pinMode(PWM_TR, OUTPUT);
  pinMode(PWM_BR, OUTPUT);   
}

//Temp Function for storing PWM
void check_and_set_pin(unsigned int pwm_pin, unsigned int duty_cycle)
{
  switch (pwm_pin)
  {
    case PWM_TL:
      duty_cycles.TL = duty_cycle;
      break;
    case PWM_BL:
      duty_cycles.BL = duty_cycle;
      break;
    case PWM_TR:
      duty_cycles.TR = duty_cycle;
      break;
    case PWM_BR:
      duty_cycles.BR = duty_cycle;
      break;
  }
}

/* This method to contol PWM */
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

void stop_all_motors()
{
  for (int i = 0; i < (sizeof(motors_pins) / sizeof(motors_pins[0])); i++)
  {
    stop_motor(motors_pins[i]);  
  }
}

/* The initial PWM we want to start the motors at */
void drive_all_motors_init(uint8_t duty_cycle)
{
  for (int i = 0; i < (sizeof(motors_pins) / sizeof(motors_pins[0])); i++)
  {
    set_pwm_duty_cycle(motors_pins[i], duty_cycle);  
  }
}

void drive_straight(int PWM) {

  control_left_motors(PWM, PWM);
  control_right_motors(PWM, PWM);

  /* Drive right side forwards*/
  digitalWrite(DIRECTION_FR, HIGH);
  digitalWrite(DIRECTION_BR, LOW);

  /* Drive left side forwards*/
  digitalWrite(DIRECTION_FL, HIGH);
  digitalWrite(DIRECTION_BL, LOW);
}

void pivot_left() {
  
  /* Drive left side backwards*/
  digitalWrite(DIRECTION_FL, LOW);
  digitalWrite(DIRECTION_BL, HIGH);
  
  /* Drive right side forwards*/
  digitalWrite(DIRECTION_FR, HIGH);
  digitalWrite(DIRECTION_BR, LOW);
  
  // Stub for detecting when we have turned 90 deg
}

void pivot_right() {
  
  /* Drive left side forwards*/
  digitalWrite(DIRECTION_FL, HIGH);
  digitalWrite(DIRECTION_BL, LOW);
  
  /* Drive right side backwards*/
  digitalWrite(DIRECTION_FR, LOW);
  digitalWrite(DIRECTION_BR, HIGH);
  
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

int pivot_theta(float angle) {

	bool turning_right = false; 
	
	if(angle > 270) {
		turning_right = true;
		angle = 360 - angle;
	} 
	
	if(turning_right) {
		pivot_right();
	} else {
		pivot_left();
	}
	
	return calculate_pulses_for_angle(angle);
}

void control_left_motors(float T_PWM, float B_PWM) {
  set_pwm_duty_cycle(PWM_TL, T_PWM);
  set_pwm_duty_cycle(PWM_BL, B_PWM);
}

void control_right_motors(float T_PWM, float B_PWM) {
  set_pwm_duty_cycle(PWM_TR, T_PWM);
  set_pwm_duty_cycle(PWM_BR, B_PWM);
}

// Getter function for the 'state' variable
enum states getState() {
    return state;
}

// Setter function for the 'state' variable
void setState(enum states newState) {
    state = newState;
}