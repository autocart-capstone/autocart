import socket
import struct
import smbus
import os

channel = 1
address = 0x12
bus = smbus.SMBus(channel)

port = 31337
if "KEYBOARD_PORT" in os.environ:
    port = int(os.environ["KEYBOARD_PORT"])
print(f"keyboard listening on port {port}")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', port))
s.listen(1)

with s:
    while True:
        conn, addr = s.accept()
        with conn:
            while True:
                data = conn.recv(1024)
                msg = data.decode()
                split = msg.split()
                pressed = split[0] == "pressed"
                if not pressed:
                    extra_bytes_MSB = list(int.to_bytes(0))
                    extra_bytes_LSB = list(int.to_bytes(0))
                    data_to_send = extra_bytes_MSB + extra_bytes_LSB + list(int.to_bytes(0))
                    print("Sending STOP")
                    bus.write_i2c_block_data(address, 0, data_to_send)
                    continue
            
                key = split[1] # Key.up/down/left/right
                #print(f"{key} pressed:{pressed}")
                # 1 = left
                # 2 = right
                # 3 = forward
                # 4 = back
                # 0 = stop
                if "up" in key:
                    print(f"up pressed:{pressed}")
                    extra_bytes_MSB = list(int.to_bytes(0))
                    extra_bytes_LSB = list(int.to_bytes(0))
                    data_to_send = extra_bytes_MSB + extra_bytes_LSB + list(int.to_bytes(3))
                    bus.write_i2c_block_data(address, 0, data_to_send)
                if "down" in key:
                    print(f"down pressed:{pressed}")
                    extra_bytes_MSB = list(int.to_bytes(0))
                    extra_bytes_LSB = list(int.to_bytes(0))
                    data_to_send = extra_bytes_MSB + extra_bytes_LSB + list(int.to_bytes(4))
                    bus.write_i2c_block_data(address, 0, data_to_send)
                if "right" in key:
                    print(f"right pressed:{pressed}")
                    extra_bytes_MSB = list(int.to_bytes(0))
                    extra_bytes_LSB = list(int.to_bytes(0))
                    data_to_send = extra_bytes_MSB + extra_bytes_LSB + list(int.to_bytes(2))
                    bus.write_i2c_block_data(address, 0, data_to_send)
                if "left" in key:
                    print(f"left pressed:{pressed}")
                    extra_bytes_LSB = list(int.to_bytes(0))
                    extra_bytes_MSB = list(int.to_bytes(0))
                    data_to_send = extra_bytes_MSB + extra_bytes_LSB + list(int.to_bytes(1))
                    bus.write_i2c_block_data(address, 0, data_to_send)
