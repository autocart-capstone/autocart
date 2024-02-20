#ifndef I2C_SETUP_H
#define I2C_SETUP_H

void init_i2c();

#define I2C_ADDRESS (0x12)

#define MSB_ANGLE_INDEX (1)
#define LSB_ANGLE_INDEX (2)
#define DISTANCE_INDEX (3) //in cm

#define STOP_SIGNAL (-1)

extern uint16_t turning_angle;
extern uint16_t turning_distance;

#endif
