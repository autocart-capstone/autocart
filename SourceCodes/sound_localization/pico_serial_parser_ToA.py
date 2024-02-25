import serial
import numpy as np
import matplotlib.pyplot as plt

noiseA = np.load("misc/filtered_noiseA.npy") 
noiseB = np.load("misc/filtered_noiseB.npy") 

def correlate_and_find_delay2(rec, noise, plot):
    #rec_padded = np.pad(rec, (len(noise), 0), 'constant', constant_values=0)
    #print(rec)
    rec_fft = np.fft.rfft(rec)
    diff = len(rec)-len(noise)
    noise_padded = np.pad(noise, (0, diff), 'constant', constant_values=0)
    noise_fft_conj = np.conj(np.fft.rfft(noise_padded))
    #print(rec_fft.shape, noise_fft_conj.shape)
    cross_corr_freq = noise_fft_conj * rec_fft 
    cross_corr = np.abs(np.fft.irfft(cross_corr_freq))
    valid_len = diff + 1
    cross_corr = cross_corr[:valid_len]
    #print(cross_corr)
    if plot:
        plt.plot(cross_corr)
        plt.title("correlation")

    k_max_ind = np.argmax(cross_corr)

    return k_max_ind

ser = serial.Serial("/dev/ttyACM0", 115200)
#ser.set_buffer_size(rx_size = 8192)
delay_m1 = 0
delay_m2 = 0
while True:
    line = ser.readline().strip()
    node = 0
    noise_to_use = None
    if line == b'node1':
        node = 1
        noise_to_use = noiseB
    elif line == b'node2':
        node = 2
        noise_to_use = noiseB
    else:
        if len(line) < 100:
            #print(line)
            pass
        continue
    line = ser.readline().strip()
    assert(line == b'bytes')
    size = ser.readline().strip()
    size = int(size.decode('utf-8'))
    print(f"node {node}, size {size}")
    b = ser.read(size)
    samples = np.frombuffer(b, dtype='<i2')
    samples = np.asarray(samples, dtype='double') / 2**15 # normalize to [-1, 1]
    if False: # set to true to hear the audio
        import sounddevice as sd
        sd.play(samples, 48000, blocking=False)
    else:
        plt.ion()
        plt.figure(1)
        plt.clf()
        delay_index = correlate_and_find_delay2(samples, noise_to_use, False)
        delay_s = delay_index / 48000
        delay_inches = delay_s * 13503.9 -123
        delay_m = delay_s * 343 - 3.15
        print(f"distance node{node}={delay_inches} in")
        #plt.text(delay_index, 0, f"{round(delay_m, 6)} m")
        if node == 1:
            delay_m1 = delay_inches
        else:
            delay_m2 = delay_inches
            # distance between the two speakers is 115 inches/ 3.1242 meters
            circle1 = plt.Circle((0, 0), delay_m2, color='r', fill=False)
            circle2 = plt.Circle((115, 0), delay_m1, color='b', fill=False)
            plt.gca().add_patch(circle1)
            plt.gca().add_patch(circle2)
            plt.gca().set_xlim(0.0, 115.0)
            plt.gca().set_ylim(0.0, 115.0)
            plt.show()
            plt.pause(0.01)



    
    
