#ifndef CALCULATIONS_H
#define CALCULATIONS_H

// verify the measurements (should be in cm)
#define WHEEL_DIAM 9.7f   // cm   
#define PIVOT_DIAM 38.1f  // cm 

// Width middle of wheel: 21.59 cm 
// length middle of wheel: 30.48 cm 

int calculate_pulses_for_angle(float angle);

float calculate_RPM(int pulses_elapsed);

#endif
