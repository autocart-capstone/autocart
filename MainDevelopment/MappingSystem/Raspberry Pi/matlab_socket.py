# Echo server program
import socket
import sys
import errno
import struct

HOST = '0.0.0.0'                 # Symbolic name meaning all available interfaces
PORT = 8003          # Arbitrary non-privileged port

array = [1.3,2.0, 1.3,3.9]
size = len(array)


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    print("starting to listen")
    
    conn, addr = s.accept()
    
    
    with conn:
        print('Connected by', addr)
            
        z = struct.pack('I', size)
        conn.sendall(z)
        conn.sendall(struct.pack(f'{len(array)}f', *array))

        print(z)
                
                
    
                

