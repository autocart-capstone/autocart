import socket
import struct
import smbus
import time
import matplotlib.pyplot as plt
import math

PORT, HOST_IP = 8080, '127.0.0.1'

angle_distance_pairs = []
x_points = []
y_points = []

plt.ion()
fig = plt.figure()
#figure, ax = plt.subplots(figsize=(10,8))
#line1, = ax.plot(x_points, y_points)



with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST_IP, PORT))
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
                        
                        x_points.append(distance * math.cos(angle))
                        y_points.append(distance * math.sin(angle))
                                                
                        current_time = time.time()
                        measuring_time = current_time - measure_start
                        
                    
                    print(angle_distance_pairs)
                    print("-------------")
                        
                    plt.scatter(x_points, y_points, s=10)
                    plt.show()
                    
                    
                    fig.canvas.draw()
                    fig.canvas.flush_events()
                    
                        
                    angle_distance_pairs = []
                    x_points = []
                    y_points = []
                        
                    start_time = time.time()

                
                else:
                    print(angle_distance_pairs)
                    angle_distance_pairs = []
                    print{"------------"}

                    
                start_time = time.time()
       
                
                
