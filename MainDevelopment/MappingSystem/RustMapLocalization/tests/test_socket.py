import socket
import struct

s = socket.socket()

# binding port and host
s.bind(("0.0.0.0", 8001))

# waiting for a client to connect
s.listen(1)

while True:
    c, addr = s.accept()

    arr = [0.0, 1000.0, 128.0, 1000.0]

    c.sendall(struct.pack("I", len(arr)))
    c.sendall(struct.pack(f"{len(arr)}f", *arr))

    val = c.recv(1024)
    print(val)
