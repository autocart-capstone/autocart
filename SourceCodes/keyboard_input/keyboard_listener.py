import socket
import struct
import smbus

channel = 1
address = 0x12
bus = smbus.SMBus(channel)

port = 31337

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', port))
s.listen()

while True:
    conn, addr = s.accept()
    with conn:
        while True:
            data = conn.recv(1024)
            msg = data.decode()
            split = msg.split()
            pressed = split[0] == "pressed"
            if not pressed:
                bus.write_i2c_block_data(address, 0, list(int.to_bytes(0)))
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
                bus.write_i2c_block_data(address, 0, list(int.to_bytes(3)))
            if "down" in key:
                print(f"down pressed:{pressed}")
                bus.write_i2c_block_data(address, 0, list(int.to_bytes(4)))
            if "right" in key:
                print(f"right pressed:{pressed}")
                bus.write_i2c_block_data(address, 0, list(int.to_bytes(2)))
            if "left" in key:
                print(f"left pressed:{pressed}")
                bus.write_i2c_block_data(address, 0, list(int.to_bytes(1)))
