import socket
import struct
import smbus
import time

PORT, HOST_IP = 8080, '127.0.0.1'
key = 5

channel = 1
address = 0x12

bus = smbus.SMBus(channel)

currentAngle = 0
lowestDistance = -1


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
            
            if not d:
                print()
            else:
                
                current_time = time.time()
                elapsed_time = current_time - start_time
                if(elapsed_time >= 0.2):
                    #send Data
                    print("distance ", lowestDistance)
                    print("angle ", round(currentAngle))
                    msb = (round(currentAngle) >> 8) & 0xFF
                    lsb = (round(currentAngle)) & 0xFF
                    
                    data_to_send = (msb,lsb, round(lowestDistance/10))
                    data = bytes(data_to_send)
                    print(list(data))
                    bus.write_i2c_block_data(address, 0, list(data))
                    
                    start_time = time.time()
                    lowestDistance = -1
                    
                if((values[1] < 1000) and (values[1] < lowestDistance or lowestDistance == -1)):
                    lowestDistance = values[1]
                    currentAngle = values[0]
                
                
                
