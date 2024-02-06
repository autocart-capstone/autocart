import serial
import numpy as np
import matplotlib.pyplot as plt

noise = np.load("filtered_noise.npy") # not in the function so this only executes when script is imported, not every func call

def correlate_and_find_delay2(rec):
    #rec_padded = np.pad(rec, (len(noise), 0), 'constant', constant_values=0)
    print(rec)
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
    plt.plot(cross_corr)
    plt.title("correlation")

    k_max_ind = np.argmax(cross_corr)

    return k_max_ind

ser = serial.Serial("/dev/ttyACM0", 115200)
#ser.set_buffer_size(rx_size = 8192)
while True:
    line = ser.readline().strip()
    if line != b'bytes':
        if len(line) < 100:
            print(line)
        continue
    size = ser.readline().strip()
    size = int(size.decode('utf-8'))
    #print(size)
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
        delay_index = correlate_and_find_delay2(samples)
        delay_s = delay_index / 48000
        delay_m = delay_s * 343
        plt.text(delay_index, 5, f"{round(delay_m, 6)} m")
        plt.show()
        plt.pause(0.01)
    
    
