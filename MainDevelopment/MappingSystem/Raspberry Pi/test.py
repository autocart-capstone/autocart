from time import sleep
from smbus2 import SMBus

channel = 1
address = 0x12

bus = SMBus(channel)

#data_to_send = (0,0,3) #FORWARD
#data = bytes(data_to_send) #SEND
#bus.write_i2c_block_data(address, 0, list(data))

PICO_CMD_STOP = 0
PICO_CMD_TURN_LEFT = 1
PICO_CMD_TURN_RIGHT = 2
PICO_CMD_FWD = 3
PICO_CMD_BWD = 4

PICO_ANGLE_PADDING = list(int.to_bytes(0, length=2))

data= PICO_ANGLE_PADDING + [PICO_CMD_STOP]
bus.write_i2c_block_data(address, 0, data)
sleep(0.1)

input("press enter to go forward")

for i in range(7):
    angle_bytes = list(int.to_bytes(i*10, length=2))
    data= angle_bytes + [PICO_CMD_FWD]
    bus.write_i2c_block_data(address, 0, data)
    sleep(0.1)

input("press enter to go stop")

data= PICO_ANGLE_PADDING + [PICO_CMD_STOP]
bus.write_i2c_block_data(address, 0, data)
sleep(0.1)