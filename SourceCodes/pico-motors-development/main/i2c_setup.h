#ifndef I2C_SETUP_H
#define I2C_SETUP_H

void init_i2c();

#define I2C_ADDRESS (0x12)

#define MSB_ANGLE_INDEX (1)
#define LSB_ANGLE_INDEX (2)
#define STATE_INDEX (3)  //Refer to pin_config.h for the numbering

uint32_t get_turning_angle();

void set_turning_angle(uint32_t angle);

#endif
