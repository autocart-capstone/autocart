import serial
import numpy as np
import matplotlib.pyplot as plt

noise1 = np.load("misc/filtered_noise1.npy") 
noise2 = np.load("misc/filtered_noise2.npy") 
noise3 = np.load("misc/filtered_noise3.npy")

A = np.array([0, 0])
B = np.array([10, 0])
C = np.array([5, 10])

assert A[0] == 0 and A[1] == 0
assert B[0] > 0 and B[1] == 0
assert C[1] > 0

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


b = B[0]  # also = np.linalg.norm(B)
cx = C[0]
cy = C[1]
c = np.linalg.norm(C)

def calculate_TDoA(rec):
    Fs = 48000
    T1 = correlate_and_find_delay2(rec, noise1, False) / Fs
    T2 = correlate_and_find_delay2(rec, noise1, False) / Fs
    T3 = correlate_and_find_delay2(rec, noise1, False) / Fs
    c = 343 # m/s, speed of sound

    ## Fang's algorithm, gotten from the PDF (in the repo or at https://ieeexplore.ieee.org/document/102710)

    Rab = c*(T1 - T2)
    Rac = c*(T1 - T3)

    # variable names correspond to those in the paper
    g = (Rac * b / Rab - cx) / cy
    h = (c**2 - Rac**2 + Rac * Rab * (1 - (b / Rab) ** 2)) / (2 * cy)

    d = -(1 - (b / Rab) ** 2 + g**2)
    e = b * (1 - (b / Rab) ** 2) - 2 * g * h
    f = (Rab**2 / 4) * (1 - (b / Rab) ** 2) ** 2 - h**2

    z = 0
    x = np.roots([d, e, f - z**2])  # eq 9a
    y = g * x + h  # eq 13
    print(x, y)

    guess1 = np.array([x[0], y[0]])
    guess2 = np.array([x[1], y[1]])


    def err(g):
        deltaA = np.linalg.norm(g - A)
        deltaB = np.linalg.norm(g - B)
        deltaC = np.linalg.norm(g - C)
        rab = deltaA - deltaB
        rac = deltaA - deltaC
        mse = ((rab - Rab) ** 2 + (rac - Rac) ** 2) / 2
        return mse


    best_guess = min([guess1, guess2], key=err)
    return best_guess


ser = serial.Serial("/dev/ttyACM0", 115200)
#ser.set_buffer_size(rx_size = 8192)
while True:
    line = ser.readline().strip()
    if(line != b'bytes'):
        continue
    size = ser.readline().strip()
    size = int(size.decode('utf-8'))
    print(f"size {size}")
    b = ser.read(size)
    samples = np.frombuffer(b, dtype='<i2')
    samples = np.asarray(samples, dtype='double') / 2**15 # normalize to [-1, 1]
    if False: # set to true to hear the audio
        import sounddevice as sd
        sd.play(samples, 48000, blocking=False)
    else:
        pos = calculate_TDoA(samples)
        plt.ion()
        plt.figure(1)
        plt.clf()
        plt.scatter(
            [A[0], B[0], C[0]], [A[1], B[1], C[1]], label="base stations", marker="D"
        )
        plt.scatter(pos[0], pos[1], label="position guess")
        plt.legend()
        plt.show()
        plt.pause(0.01)



    
    
