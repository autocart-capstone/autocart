#include "calculations.h"
#include "pin_config.h"
#include <math.h>

static const float wheel_circ = WHEEL_DIAM * PI;
static const float pivot_circ = PIVOT_DIAM * PI;

static const float period = 0.25;

int calculate_pulses_for_angle(float angle){
  float pulses_per_full_pivot = PULSES_PER_REV * (pivot_circ / wheel_circ);
  float pulses_for_theta = (angle / 360) * (pulses_per_full_pivot);
  
  return round(pulses_for_theta);
}

float calculate_RPM(int pulses_elapsed) {
  /* to calculate the RPM from the pulses, we need to know how many pulses happened 
     in a given period of time, ie 1 sec. With this, we can find the frequency of the
     pulses, and then calculate with the formula below. 
  
     will likely need to implement a timer to interrupt and send the total pulses to this 
     method. the timer will pretty much define the peroid. 
  
     In the timer we can keep track of the pulses that happen on each side of the cart, and
     calculate the RPM individaully. (do we need to know RPM of both sides, or is just one 
     sufficient?) 
  */
  
  float RPM = (pulses_elapsed * 60) / (period * PULSES_PER_REV);
  
  return RPM;
}
