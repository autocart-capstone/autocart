from pynput.keyboard import Key, Listener
import socket
import sys

# use with python3 keyboard_sender.py <ip> <port>

if len(sys.argv) < 3:
    print("use with `python3 keyboard_sender.py <ip> <port>`")

ip = sys.argv[1]
port = sys.argv[2]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((ip, port))


def on_press(key):
    s.send(f"pressed {key}".encode())


def on_release(key):
    s.send(f"released {key}".encode())


# Collect events until released
with Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
