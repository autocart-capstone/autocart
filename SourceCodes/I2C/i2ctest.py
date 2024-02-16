#RPi Pinouts

import smbus
import time

channel = 1
address = 0x12

bus = smbus.SMBus(channel)

while True:
    data_to_send = (42, 100, 200)
    data_bytes = bytes(data_to_send)
    bus.write_i2c_block_data(address, 0, list(data_bytes))
    print("send/n")
    time.sleep(1)
