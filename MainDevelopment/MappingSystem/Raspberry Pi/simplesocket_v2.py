"""
Pseudocode:
Setup c++ socket connection to the C++ SDK
Read data coming from t)e SDK whenever current angle is less than previous angle:
Store it in buffer(dynamic buffer) (1 revolution has 1200 samples)
Make sure matlab is done processing and ready to grab new data values
Send buffer contents (data: angle, distance) to matlab socket connection

"""

import socket
import struct
import os
import subprocess
import time
import math
import smbus

MATLAB_PORT = 8008
if "MATLAB_PORT" in os.environ:
    MATLAB_PORT = int(os.environ["MATLAB_PORT"])
print(f"will listen for matlab on port: {MATLAB_PORT}")

SDK_PORT = 8080
if "SDK_PORT" in os.environ:
    SDK_PORT = int(os.environ["SDK_PORT"])

class SimpleSocketRpi:
    def __init__(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.m = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.buf = []

    def connect_socket(self):
        self.m.bind(("0.0.0.0", MATLAB_PORT))
        self.m.listen(1)

        print("starting to listen to matlab")
        conn, addr = self.m.accept()
        print("Connected by", addr)
        self.matlab_conn = conn
        self.matlab_conn.setblocking(False)

        self.s.bind(("127.0.0.1", SDK_PORT))
        self.s.listen(1)
        print("starting to listen to sdk")

        print("executing sdk")
        self.sdk_subp = subprocess.Popen(
            [
                "../rplidar_sdk-master/output/Linux/Release/ultra_simple",
                "--channel",
                "--serial",
                "/dev/ttyUSB0",
                "115200",
            ],
            stdout=subprocess.DEVNULL,
        )
        # os.system("../rplidar_sdk-master/output/Linux/Release/ultra_simple  --channel --serial /dev/ttyUSB0 115200")
        conn, addr = self.s.accept()
        print("Connected by", addr)
        self.sdk_conn = conn

    def send_data_to_matlab(self):
        self.matlab_conn.sendall(struct.pack("I", len(self.buf)))
        self.matlab_conn.sendall(struct.pack(f"{len(self.buf)}f", *self.buf))

    def receive_data_from_matlab(self):
        try:
            return self.matlab_conn.recv(1024)
        except Exception:
            return b""

    def receive_data_from_lidar(self):
        d = self.sdk_conn.recv(8)  # reads up to 8 bytes of data
        if not d:
            print("Recevied empty string")
        # angle, distance = struct.unpack('ff', d)
        return d

    def save_data_to_buffer(self, data: tuple):
        self.buf += data

    def get_buffer(self):
        return self.buf

    def reset_buffer(self):
        self.buf = []

#global x,y,matlab_ready
#x = -1
#y = -1
destinations = [ (25, 1),(25, 17),(5, 17),(5, 1)]

channel = 1
address = 0x12

bus = smbus.SMBus(channel)

#data_to_send = (0,0,3) #FORWARD
#data = bytes(data_to_send) #SEND
#bus.write_i2c_block_data(address, 0, list(data))

PICO_CMD_STOP = int.to_bytes(0)
PICO_CMD_FWD = int.to_bytes(3)
PICO_CMD_BWD = int.to_bytes(4)
PICO_ANGLE_PADDING = int.to_bytes(0, length=2)
PICO_CMD_TURN_LEFT = int.to_bytes(1)
PICO_CMD_TURN_RIGHT = int.to_bytes(2)

def got_position_from_matlab(cart_x, cart_y, cart_angle):
    
    dest_x, dest_y = destinations[0]
    if math.sqrt((cart_x - dest_x)**2 + (cart_y - dest_y)**2) < 1:
        destinations.append(destinations.pop(0)) # put reached destination at the end of the list
    
    dest_x, dest_y = destinations[0]

    line_to_dest = dest_x - cart_x, dest_y - cart_y

    angle_to_dest = math.atan2(line_to_dest[1], line_to_dest[0]) # [-pi, pi]
    angle_to_dest_deg = (angle_to_dest + math.pi) / math.pi * 360.0

    angle_to_turn = int(cart_angle - angle_to_dest_deg)
    print(angle_to_dest_deg, cart_angle, angle_to_turn)
    turn_cmd = None
    if angle_to_turn > 0.0:
        turn_cmd = PICO_CMD_TURN_LEFT
    else:
        turn_cmd = PICO_CMD_TURN_RIGHT

    angle_bytes = int.to_bytes(abs(angle_to_turn), length=2)

    if True: # Should we always send the turn command?
        data= angle_bytes + turn_cmd
        bus.write_i2c_block_data(address, 0, data)

def main():
    ss = SimpleSocketRpi()
    ss.connect_socket()
    data_to_send = (0,0,3)
    data=bytes(data_to_send)
    bus.write_i2c_block_data(address,0,list(data))
    curr_angle = 0
    prev_angle = curr_angle
    matlab_ready = True
    matlab_sent_timestamp = time.time()

    while True:
        data = ss.receive_data_from_lidar()
        data = struct.unpack("ff", data)

        curr_angle = data[0]  # Assuming first elem is angle

        ss.save_data_to_buffer(data)

        matlab_pos = ss.receive_data_from_matlab()
        if matlab_pos:
            matlab_ready = True
            a = matlab_pos.decode().strip().split()
            x = float(a[0])
            y = float(a[1])
            angle = float(a[2])
            print(f"received (x,y,angle): ({x},{y},{angle})")
            print(f"took {time.time() - matlab_sent_timestamp} seconds to get position from Matlab")
            got_position_from_matlab(x,y,angle)
            
        if curr_angle < prev_angle:  # If we finish one revolution
            if matlab_ready:
                # Send buffer to matlab socket
                # print(ss.get_buffer())
                ss.send_data_to_matlab()
                print("sent data to Matlab")
                matlab_sent_timestamp = time.time()
                matlab_ready = False
            # Reset buffer - always do this after finishing 1 rev
            ss.reset_buffer()
            # Save first data from the new rev
            ss.save_data_to_buffer(data)

        # If we are not done with one rev yet, keep saving data (angle,dist) to buffer
        # Update prev_angle
        prev_angle = curr_angle

main()
