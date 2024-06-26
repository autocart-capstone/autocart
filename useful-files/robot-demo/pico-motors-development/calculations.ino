#include "calculations.h"
#include "pin_config.h"
#include <math.h>

static const float wheel_circ = WHEEL_DIAM * PI;
static const float pivot_circ = PIVOT_DIAM * PI;

static const float period = 0.10;

/* Method to calucalate the required encoder pulses to turn a given angle */
float calculate_pulses_for_angle(float angle) {
  float pulses_per_full_pivot = PULSES_PER_REV * (pivot_circ / wheel_circ);
  float pulses_for_theta = (angle / 360) * (pulses_per_full_pivot);

  return pulses_for_theta;
}

/* Method to calculate the current RPM of a wheel given the pulses over a period of 0.1s */
float calculate_RPM(int pulses_elapsed) {
  float RPM = (pulses_elapsed * 60) / (period * PULSES_PER_REV);
  return RPM;
}
