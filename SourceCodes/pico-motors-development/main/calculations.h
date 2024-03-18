#ifndef CALCULATIONS_H
#define CALCULATIONS_H

/* Cart Measurements 
    length middle of wheel: 30.48 cm 
    Width middle of wheel: 21.59 cm 
 */

#define WHEEL_DIAM 9.7f   // cm
#define PIVOT_DIAM 38.1f  // cm

float calculate_pulses_for_angle(float angle);

float calculate_RPM(int pulses_elapsed);

#endif
