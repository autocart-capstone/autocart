#include <math.h>

#include "calculations.h"
#include "common.h"


static float wheel_circ = wheel_diam * PI;
static float pivot_circ = pivot_diam * PI;

static float period = 1; // period of timer in seconds (can delete the var if we select 1 s timer interrupts)

int calculate_pulses_for_angle(float angle) {
	float pulses_per_full_pivot = pulses_per_rev * (pivot_circ / wheel_circ);
	float pulses_for_theta = (angle / 360) * (pulses_per_full_pivot);
	
	return round(pulses_for_theta);
}

int calculate_RPM(int pulses_elapsed) {
	/* to calculate the RPM from the pulses, we need to know how many pulses happened 
		 in a given period of time, ie 1 sec. With this, we can find the frequency of the
		 pulses, and then calculate with the formula below. 
	
		 will likely need to implement a timer to interrupt and send the total pulses to this 
		 method. the timer will pretty much define the peroid. 
	
		 In the timer we can keep track of the pulses that happen on each side of the cart, and
		 calculate the RPM individaully. (do we need to know RPM of both sides, or is just one 
		 sufficient?) 
	*/
	
	float RPM = (pulses_elapsed * period) / pulses_per_rev;
	
	return RPM;
}

/* create method to determine if we need to slowdown/stop if an object is in our path.
	 We findout if there is an object infornt of us if it's angle is in the range of maybe 
	 30 degrees, and, based on it's distance, we need to be able to slow the cart down accordingly
*/