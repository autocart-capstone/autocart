import socket
import struct
import smbus
import time

PORT, HOST_IP = 8080, '127.0.0.1'

angle_distance_pairs = []  # Initialize an empty list to store angle-distance pairs


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
            
            # If data not received
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
                
                else:
                    print(angle_distance_pairs)
                    angle_distance_pairs = []
                    print{"------------"}

                    
                start_time = time.time()
       
                
                
