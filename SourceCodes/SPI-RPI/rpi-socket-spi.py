import socket
import struct
import spidev
import time

PORT, HOST_IP = 8080, '127.0.0.1'
key = 5

# Function to initialize SPI
def init_spi():
    spi = spidev.SpiDev()
    spi.open(0, 0)  # Use CE0 (chip enable 0) on the Raspberry Pi
    spi.max_speed_hz = 100000  # Set SPI speed to 100 KHz
    return spi

# Function to send and receive data over SPI
def transfer_spi(spi, data):
    return spi.xfer2(data)

    
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST_IP, PORT))
    s.listen()
    print("starting to listen")
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        spi = init_spi()
        while(True):
            d = conn.recv(12)
            
            if not d:
                print()
            else:
                values = struct.unpack('ffi', d)
                
                if(values[1]<200 and ((values[0] < 60) or values[0] > 300)): #STOP
                    print(values)
                    data_to_send = [0x2]
                    received_data = transfer_spi(spi, data_to_send)
                elif(values[1]>200 and ((values[0] < 60) or values[0] > 300)): #GO
                    data_to_send = [0x4]
                    received_data = transfer_spi(spi, data_to_send)
