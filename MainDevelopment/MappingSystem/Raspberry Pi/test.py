
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

bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_STOP])
sleep(0.1)

input("press enter to go forward")

for i in range(10):
    bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_FWD])
    sleep(0.1)

#input()

print("adjusting right")
for i in range(150000):
    angle_bytes = list(int.to_bytes(10, length=2))
    bus.write_i2c_block_data(address, 0, angle_bytes + [PICO_CMD_FWD])
    sleep(0.1)
exit(1)

print("adjusting left")
for i in range(50):
    angle_bytes = list(int.to_bytes(345, length=2))
    bus.write_i2c_block_data(address, 0, angle_bytes + [PICO_CMD_FWD])
    sleep(0.1)


bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_STOP])
sleep(0.1)

exit()
#angle_bytes = list(int.to_bytes(350, length=2))
bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_TURN_LEFT])
sleep(0.1)

while(True):
    angle_bytes = list(int.to_bytes(350, length=2))
    bus.write_i2c_block_data(address, 0, angle_bytes + [PICO_CMD_FWD])
    sleep(0.1)


input("press enter to go stop")

bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_STOP])
sleep(0.1)
