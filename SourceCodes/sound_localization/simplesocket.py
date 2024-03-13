import socket
import struct
import smbus
import time

PORT, HOST_IP = 8080, '127.0.0.1'
key = 5

channel = 1
address = 0x12

bus = smbus.SMBus(channel)

#currentAngle = 0
#lowestDistance = -1
x = 0
y = 0

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind((HOST_IP, PORT))
    s.listen(1)
    print("starting to listen")
    conn, addr = s.accept()
    try:
        print('Connected by', addr)
        
        start_time = time.time()
        
        while True:
            try:
                d = conn.recv(12) #reads up to 12 bytes of data
                if not d:
                    print("Recevied empty string")
                    break
                    
                x, y = struct.unpack('ff', d)
                # Format floats to have only two decimal points
                x_formatted = "{:.2f}".format(x)
                y_formatted = "{:.2f}".format(y)
                print("Received x:", x_formatted)
                print("Received y:", y_formatted)

                current_time = time.time()
                elapsed_time = current_time - start_time
 
                # data_to_send = struct.pack('ff', float(x_formatted), float(y_formatted))
                data = list((int(float(x_formatted)), int(float(y_formatted))))
                # print(list(data))
                # data_list = list(int(data))
                print(data)
                # bus.write_i2c_block_data(address, 0, data)
                
            except struct.error as e:
                print("Error unpacking data:", e)
            except Exception as e:
                print("Error:", e)
    finally:
        conn.close()
finally:
    s.close()                
                
                
