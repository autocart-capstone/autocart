#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#define WHEEL_DIAM 6.35f
#define PIVOT_DIAM 26.6f

int calculate_pulses_for_angle(float angle);

float calculate_RPM(int pulses_elapsed);

#endif
