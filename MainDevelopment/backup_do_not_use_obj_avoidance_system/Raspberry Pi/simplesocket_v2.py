"""
Pseudocode:
Setup c++ socket connection to the C++ SDK
Read data coming from the SDK whenever current angle is less than previous angle:
Store it in buffer(dynamic buffer) (1 revolution has 1200 samples)
Make sure matlab is done processing and ready to grab new data values
Send buffer contents (data: angle, distance) to matlab socket connection

"""
import socket
import struct

class SimpleSocketRpi():
    def __init__(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.PORT = 8080
        self.HOST_IP = '127.0.0.1'
        self.buf = []

    def connect_socket(self):
        global conn, addr
        self.s.bind((self.HOST_IP, self.PORT))
        self.s.listen(1)
        print("starting to listen")
        conn, addr = self.s.accept()
        print('Connected by', addr)

    def send_data_to_matlab(self):
        # To be implemented
        return -1

    def receive_data_from_matlab(self):
        # To be implemented
        return -1

    def receive_data_from_lidar(self):
        d = conn.recv(8) #reads up to 8 bytes of data
        if not d:
            print("Recevied empty string")
        # angle, distance = struct.unpack('ff', d)
        return d

    def save_data_to_buffer(self, data: tuple):
        self.buf += [data]

    def get_buffer(self):
        return self.buf

    def reset_buffer(self):
        self.buf = []

def main():
    ss = SimpleSocketRpi()
    ss.connect_socket()
    curr_angle = 0
    prev_angle = curr_angle
    matlab_ready = False    #Dummy var (need to set this)

    while True:
        data = ss.receive_data_from_lidar()

        curr_angle = data[0]    # Assuming first elem is angle

        ss.save_data_to_buffer(data)

        if curr_angle < prev_angle: # If we finish one revolution
            if matlab_ready:
                #Send buffer to matlab socket
                ss.send_data_to_matlab()

            #Reset buffer - always do this after finishing 1 rev
            ss.reset_buffer()
            #Save first data from the new rev
            ss.save_data_to_buffer(data)
        
        #If we are not done with one rev yet, keep saving data (angle,dist) to buffer

        #Update prev_angle
        prev_angle = curr_angle
    
    # Dummy data - solely for testing
    curr_angle = 0
    # prev_angle = curr_angle
    # data_lst = [(356.7, 18), (358.2, 12), (359.5, 11), (0, 10), (1.2, 25), (3.6, 20), (5.0, 15)]
    # for i in range(len(data_lst)):
    #     curr_angle = data_lst[i][0]
    #     ss.save_data_to_buffer(data_lst[i])
    #     if curr_angle < prev_angle: # If we finish one revolution
    #         ss.reset_buffer()
    #         ss.save_data_to_buffer(data_lst[i]) # save first data from rev
    #     print(ss.get_buffer())
    #     prev_angle = curr_angle
    return 0



main()