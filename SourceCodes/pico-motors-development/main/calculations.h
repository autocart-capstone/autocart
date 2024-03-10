#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#define WHEEL_DIAM 9.7f
#define PIVOT_DIAM 18.67f

//Width middle of wheel: 21.59
//Height middle of wheel: 30.48

int calculate_pulses_for_angle(float angle);

float calculate_RPM(int pulses_elapsed);

#endif
