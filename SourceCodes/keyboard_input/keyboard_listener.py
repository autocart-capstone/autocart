import socket

port = 31337

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', port))
s.listen()

while True:
    conn, addr = s.accept()
    with conn:
        while True:
            data = conn.recv(1024)
            msg = data.decode()
            split = msg.split()
            pressed = split[0] == "pressed"
            key = split[1] # Key.up/down/left/right
            #print(f"{key} pressed:{pressed}")
            if "up" in key:
                print(f"up pressed:{pressed}")
            if "down" in key:
                print(f"down pressed:{pressed}")
            if "right" in key:
                print(f"right pressed:{pressed}")
            if "left" in key:
                print(f"left pressed:{pressed}")

