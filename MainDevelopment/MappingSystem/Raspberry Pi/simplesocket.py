import socket
import struct
import smbus
import time


PORTObj, PORTMAT, HOST_IP, MATLAB_IP = 8080, 8005, '127.0.0.1', '0.0.0.0'
key = 5

channel = 1
address = 0x12

bus = smbus.SMBus(channel)

currentAngle = 0
lowestDistance = -1

x, y = -1, -1

dataList = []


s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
m = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
with s1, m:
    m.bind((MATLAB_IP, PORTMAT))
    m.listen()
    print('starting to listen to matlab')
    conn2, addr2 = m.accept()
    
    s1.bind((HOST_IP, PORTObj))
    s1.listen()
    print("starting to listen to SDK")
    conn1, addr1 = s1.accept()
    
    
    
    
    
    with conn1, conn2:
        print('Connected by', addr1, PORTObj)
        print('Connected by', addr2, PORTMAT)
        
        start_time = time.time()
        
        while True:            
            d = conn1.recv(12)
            values = struct.unpack('ffi', d)
            deg = values[0]
            dist = values[1]
            quality = values[2]
            dataList.append(deg)
            dataList.append(dist)
            assert(quality > 0)
            
            if((values[1] < 1000) and (values[1] < lowestDistance or lowestDistance == -1)):
                lowestDistance = values[1]
                currentAngle = values[0]
            
            current_time = time.time()
            elapsed_time = current_time - start_time
            
            if(elapsed_time >= 0.1):
                print(dataList[:10])
                conn2.sendall(struct.pack('I', len(dataList)))
                conn2.sendall(struct.pack(f'{len(dataList)}f', *dataList))
                dataList.clear()
            
                #send Data
                #print("smallest distance ", lowestDistance)
                #print("angle of ^", round(currentAngle))
                msb = (round(currentAngle) >> 8) & 0xFF
                lsb = (round(currentAngle)) & 0xFF
                    
                data_to_send = (msb,lsb, round(lowestDistance/10))
                data = bytes(data_to_send)
                #print(list(data))
                # bus.write_i2c_block_data(address, 0, list(data))
                
                start_time = time.time()
                lowestDistance = -1
                    
            
                
                
                
