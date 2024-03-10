# Echo server program
import socket
import sys
import errno

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50008           # Arbitrary non-privileged port


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    print("starting to listen")
    
    conn, addr = s.accept()
    
    try:
        with conn:
            print('Connected by', addr)
            
            data = "HELLO AHMED"
            conn.sendall(data.encode('utf-8'))        
            
            while True:
                    
                d = conn.recv(1024)            
                
                # If data is not received
                if d:
                    print(d.decode())
                    print(sys.getsizeof(d))
                
    except IOError as e:
        if e.errno == errno.EPIPE:
            pass
                
    
                
conn.close()