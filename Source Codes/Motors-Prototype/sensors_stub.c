#include "sensors_stub.h"

static char* directions[2] = {"LEFT", "RIGHT"};
static int angles[4] = {20, 60, 340, 300};

static int direction_index = 0; 
static int angles_index = 0;

char* get_next_direction() {
	
	if(direction_index > 1) {
		direction_index = 0; 
	}
	
	return directions[direction_index++];
	
}

int get_next_angle() {
	
	if(angles_index > 3) {
		angles_index = 0; 
	}
	
	return angles[angles_index++];
	
}