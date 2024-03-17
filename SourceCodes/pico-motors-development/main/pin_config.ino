#include "pin_config.h"
#include "calculations.h"

#include <cstring>

#define MAX_DISABLED_PINS 4

//Struct to store values of duty cycle.
static struct duty_cycles {
  int FL, BL;  // Front and Back left
  int FR, BR;  // Front and Back right
} duty_cycles;

static int disabled_gpio_pins[MAX_DISABLED_PINS];

//Temp Function for storing PWM
void check_and_set_pin(unsigned int pwm_pin, unsigned int duty_cycle) {
  switch (pwm_pin) {
    case PWM_BWD_FL:
    case PWM_FWD_FL:
      duty_cycles.FL = duty_cycle;
      break;
    case PWM_BWD_BL:
    case PWM_FWD_BL:
      duty_cycles.BL = duty_cycle;
      break;
    case PWM_BWD_FR:
    case PWM_FWD_FR:
      duty_cycles.FR = duty_cycle;
      break;
    case PWM_BWD_BR:
    case PWM_FWD_BR:
      duty_cycles.BR = duty_cycle;
      break;
  }
}

bool check_pin_disabled(unsigned int pin) {
  for (int i = 0; i < MAX_DISABLED_PINS; i++) {
    if (disabled_gpio_pins[i] == pin) {
      return true;
    }
  }
  return false;
}

/* The initial PWM we want to start the motors at */
void drive_all_motors_init(uint8_t duty_cycle) {
  for (int i = 0; i < NUM_MOTORS; i++) {
    set_pwm_duty_cycle(PWM_FWD[i], duty_cycle);
    set_pwm_duty_cycle(PWM_BWD[i], duty_cycle);
  }
}

/* This method to contol PWM */
void set_pwm_duty_cycle(unsigned int pwm_pin, unsigned int duty_cycle) {
  // Check to see if the pin is disabled
  if (check_pin_disabled(pwm_pin)) {
    analogWrite(pwm_pin, 0);
  } else {
    analogWrite(pwm_pin, duty_cycle);  //set duty cycle to passed in value
  }
  check_and_set_pin(pwm_pin, duty_cycle);
}

void drive_forwards() {
  int pins_to_disable[] = { PWM_BWD_FL, PWM_BWD_BL, PWM_BWD_FR, PWM_BWD_BR }; 
  memcpy(disabled_gpio_pins, pins_to_disable, sizeof(pins_to_disable));
}

void drive_backwards() {
  int pins_to_disable[] = { PWM_FWD_FL, PWM_FWD_BL, PWM_FWD_FR, PWM_FWD_BR };
  memcpy(disabled_gpio_pins, pins_to_disable, sizeof(pins_to_disable));
}

void drive_left() {
  int pins_to_disable[] = { PWM_FWD_FL, PWM_FWD_BR, PWM_BWD_BL, PWM_BWD_FR };
  memcpy(disabled_gpio_pins, pins_to_disable, sizeof(pins_to_disable));
}

void drive_right() {
  int pins_to_disable[] = { PWM_BWD_FL, PWM_FWD_BR, PWM_BWD_BL, PWM_FWD_FR };
  memcpy(disabled_gpio_pins, pins_to_disable, sizeof(pins_to_disable));
}

void stop_motors() {
  for(int i = 0; i < 4; i++) {
    analogWrite(PWM_FWD[i], 0);
    analogWrite(PWM_BWD[i], 0);
  }
}

void pivot_left() {
  int pins_to_disable[] = { PWM_FWD_FL, PWM_FWD_BL, PWM_BWD_FR, PWM_BWD_BR };
  memcpy(disabled_gpio_pins, pins_to_disable, sizeof(pins_to_disable));
}

void pivot_right() {
  int pins_to_disable[] = { PWM_BWD_FL, PWM_BWD_BL, PWM_FWD_FR, PWM_FWD_BR };
  memcpy(disabled_gpio_pins, pins_to_disable, sizeof(pins_to_disable));
}

int pivot_theta(float angle) {
  bool turning_right = false;

  if (angle > 270) {
    turning_right = true;
    angle = 360 - angle;
  }

  if (turning_right) {
    pivot_right();
  } else {
    pivot_left();
  }

  return calculate_pulses_for_angle(angle);
}


// Calculations for two wheels (prototype)
int turn_theta(float angle) {
  bool turning_right = false;

  if (angle > 270) {
    turning_right = true;
    angle = 360 - angle;
  }

  int pulses = calculate_pulses_for_angle(angle);

  Serial.print("ANGLE ");
  Serial.println(angle);

  Serial.print("PULSES ");
  Serial.println(pulses);
  // ANGLE = 60, PULSES = 59, RPM_FACTOR = 0.00. might be a integer division, pulses per rev - 90
  float RPM_factor = (pulses / PULSES_PER_REV);
  Serial.print("RPM FACTOR ");
  Serial.println(RPM_factor);
  if (turning_right) {
    control_left_motors(duty_cycles.FL + (duty_cycles.FL * RPM_factor),
                        duty_cycles.BL + (duty_cycles.BL * RPM_factor));
  } else {
    control_right_motors(duty_cycles.FR + (duty_cycles.FR * RPM_factor),
                         duty_cycles.BR + (duty_cycles.BR * RPM_factor));
  }

  Serial.print("FL: ");
  Serial.println(duty_cycles.FL);

  Serial.print("BL: ");
  Serial.println(duty_cycles.BL);

  Serial.print("FR: ");
  Serial.println(duty_cycles.FR);

  Serial.print("BR: ");
  Serial.println(duty_cycles.BR);

  return pulses;
}

void control_left_motors(float T_PWM, float B_PWM) {
  set_pwm_duty_cycle(PWM_FWD_FL, T_PWM);
  set_pwm_duty_cycle(PWM_FWD_BL, B_PWM);
}

void control_right_motors(float T_PWM, float B_PWM) {
  set_pwm_duty_cycle(PWM_FWD_FR, T_PWM);
  set_pwm_duty_cycle(PWM_FWD_BR, B_PWM);
}

// Getter function for the 'state' variable
States getState() {
  return state;
}

// Setter function for the 'state' variable
void setState(States newState) {
  reset_encoders();
  stateChange = true;
  state = newState;
}
