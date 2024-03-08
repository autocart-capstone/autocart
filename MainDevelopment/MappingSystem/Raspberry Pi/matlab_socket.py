# Echo server program
import socket

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
conn, addr = s.accept()
print('Connected by', addr)

while 1:
    print("Waiting for client")
    data = conn.recv(1024)
    print(data)
    if not data: break
    #conn.sendall(data)
    data = "HELLO AHMED"
    conn.sendall(data.encode('utf-8'))
conn.close()
