# Echo server program
import socket
import sys
import errno
import time

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50008           # Arbitrary non-privileged port
txtfile = "19thjan.txt"



with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    print("starting to listen")
    
    conn, addr = s.accept()
    
    try:
        with conn:
            print('Connected by', addr)
            
            time.sleep(0.8)
            
            for i in range(10):
                print("sending")
                data = "   theta: 0.26 Dist: 09528.00 Q: 47 \n"
                print(data)         
                conn.sendall(data.encode('utf-8'))  
                time.sleep(0.8)
                
    except IOError as e:
        if e.errno == errno.EPIPE:
            pass
                
    
                
conn.close()
