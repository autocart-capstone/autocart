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
from smbus2 import SMBus

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


destinations = [
    (25, 18.5), (20, 18.5), (15, 18.5), (10, 18.5),# TR -> TL
    ( 5, 18.5), ( 5, 14.1), ( 5,  9.7), ( 5,  5.3),# TL -> BL
    ( 5,  1  ), (10,  1  ), (15,  1  ), (20,  1  ),# BL -> BR
    (25,  1  ), (25,  5.3), (25,  9.7), (25, 14.1),# BR -> TR
]


channel = 1
address = 0x12

bus = SMBus(channel)

# data_to_send = (0,0,3) #FORWARD
# data = bytes(data_to_send) #SEND
# bus.write_i2c_block_data(address, 0, list(data))

PICO_CMD_STOP = 0
PICO_CMD_TURN_LEFT = 1
PICO_CMD_TURN_RIGHT = 2
PICO_CMD_FWD = 3
PICO_CMD_BWD = 4

PICO_ANGLE_PADDING = list(int.to_bytes(0, length=2))

def got_position_from_matlab(cart_x, cart_y, cart_angle):   
    dest_x, dest_y = destinations[0]
    if math.sqrt((cart_x - dest_x) ** 2 + (cart_y - dest_y) ** 2) < 1:
        print("-- Reached point of interest")
        destinations.append(
            destinations.pop(0)
        )  # put reached destination at the end of the list

    dest_x, dest_y = destinations[0]

    line_to_dest = dest_x - cart_x, dest_y - cart_y

    angle_to_dest_deg = (
        math.atan2(line_to_dest[1], line_to_dest[0]) / math.pi * 180.0
    )  # [-180, 180]
    angle_to_dest_deg %= 360.0  # [0, 360]

    angle_to_turn = int(cart_angle - angle_to_dest_deg) % 360  # [0, 360]

    print(
        "angle_to_dest:",
        angle_to_dest_deg,
        "cart_angle:",
        cart_angle,
        "angle_to_turn:",
        angle_to_turn,
    )

    cmd, angle_bytes = None, None

    if angle_to_turn > 60.0 and angle_to_turn < 180.0:
        cmd = PICO_CMD_TURN_RIGHT
        angle_bytes = PICO_ANGLE_PADDING
        print("PIVOT right")
    elif angle_to_turn < 300.0 and angle_to_turn > 180.0:
        cmd = PICO_CMD_TURN_LEFT
        print("PIVOT left")
        angle_bytes = PICO_ANGLE_PADDING
    else:
        print(f"FWD, angle = {angle_to_turn}")
        cmd = PICO_CMD_FWD
        angle_bytes = list(int.to_bytes(angle_to_turn, length=2))

    data = angle_bytes + [cmd]
    bus.write_i2c_block_data(address, 0, data)



def main():
    ss = SimpleSocketRpi()
    ss.connect_socket()
    curr_angle = 0
    prev_angle = curr_angle
    matlab_ready = True
    collision = False
    matlab_sent_timestamp = time.time()

    while True:
        #Receive from SDK
        data = ss.receive_data_from_lidar()
        data = struct.unpack("ff", data)
        curr_angle = data[0]  # Assuming first elem is angle
        ss.save_data_to_buffer(data)

        #Receive X,Y from MATLAB
        if (collision == False):
            matlab_pos = ss.receive_data_from_matlab()
        
        #Process X,Y
        if (matlab_pos and collision==False):
            matlab_ready = True
            a = matlab_pos.decode().strip().split()
            x = float(a[0])
            y = float(a[1])
            angle = float(a[2])
            print(f"received (x,y,angle): ({x},{y},{angle})")
            print(
                f"took {time.time() - matlab_sent_timestamp} seconds to get position from Matlab"
            )
            got_position_from_matlab(x, y, angle)

        #Finish one revolution
        if curr_angle < prev_angle: 
            if (matlab_ready and collision == False):
                # Send buffer to matlab socket
                # print(ss.get_buffer())
                ss.send_data_to_matlab()
                print("sent data to Matlab")
                matlab_sent_timestamp = time.time()
                matlab_ready = False
               
            #Check for Collision 
            lowestDistance = -1
            closestAngle = 0
            collision = False
            for i in range (1, len(ss.buf),2):
                if((ss.buf[i] < 800) and (ss.buf[i] < lowestDistance or lowestDistance == -1) and ((ss.buf[i-1] < 90) or (ss.buf[i-1] > 270))):
                    lowestDistance = ss.buf[i]
                    closestAngle = ss.buf[i-1]
                    
                #print(f"Hit: {ss.buf[i]}")

            if(closestAngle > 0 and closestAngle < 90):
                if(math.cos(((90 - closestAngle) * math.pi) / 180) * lowestDistance < 190):
                    collision = True
                    print(f"Collision avoided at Distance = {lowestDistance}, Angle = {closestAngle}")
                    bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_STOP]) # Send Stop
            elif(closestAngle > 270 and closestAngle < 360):
                if(math.cos(((closestAngle - 270)) * math.pi / 180) * lowestDistance < 190):
                    collision = True
                    print(f"Collision avoided at Distance = {lowestDistance}, Angle = {closestAngle}")
                    bus.write_i2c_block_data(address, 0, PICO_ANGLE_PADDING + [PICO_CMD_STOP]) # Send Stop

            
            # Reset buffer - always do this after finishing 1 rev
            ss.reset_buffer()
            # Save first data from the new rev
            ss.save_data_to_buffer(data)

        # If we are not done with one rev yet, keep saving data (angle,dist) to buffer
        # Update prev_angle
        prev_angle = curr_angle


main()
