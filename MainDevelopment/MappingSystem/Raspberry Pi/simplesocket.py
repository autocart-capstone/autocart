import socket
import struct
import smbus
import time
import matplotlib.pyplot as plt
import math

PORT_SDK, HOST_IP_SDK = 8080, '127.0.0.1'
PORT_matlab, HOST_IP_matlab = 50007, ''

angle_distance_pairs = []


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST_IP_SDK, PORT_SDK))
    s.listen()
    print("starting to listen")
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        
        start_time = time.time()
        
        while True:
                
            d = conn.recv(12)
            values = struct.unpack('ffi', d)
            
            # If data is not received

            if not d:
                print()
            else:
                
                current_time = time.time()
                elapsed_time = current_time - start_time
                
                    
                if(elapsed_time >= 1.0):
                    measure_start = time.time()
                    measuring_time = 0
                    
                    
                    while (measuring_time <= 0.2):
                        d = conn.recv(12)
                        values = struct.unpack('ffi', d)
                        
                        distance = values[1]
                        angle = round(values[0])
                        angle_distance_pairs.append((angle, distance))
    
                        current_time = time.time()
                        measuring_time = current_time - measure_start
                        
                    
                    print(angle_distance_pairs)
                    print("-------------")
                        
                    angle_distance_pairs = []
                    start_time = time.time()
       
                
                
