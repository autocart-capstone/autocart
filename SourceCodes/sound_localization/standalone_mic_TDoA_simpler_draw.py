import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import serial

guessed_positions = []

noiseA = np.load("misc/filtered_noiseA.npy")
noiseB = np.load("misc/filtered_noiseB.npy")
noiseC = np.load("misc/filtered_noiseC.npy")
# 172.17.185.143
# A = 29.25 inch
# B = 122 = 3.0988 meters
# Cx = 108 - 29.25 = 78.75 = 2.00025 meters
# Cy = 188 = 4.7752 meters
A = np.array([0, 0])

B = np.array([0.82, 0])
C = np.array([0.82/2, 0.551])
Z_MIC_RELATIVE_TO_SPEAKERS = 0.195

assert A[0] == 0 and A[1] == 0
assert B[0] > 0 and B[1] == 0
assert C[1] > 0


def correlate_and_find_delay(rec, noise, name):
    # rec_padded = np.pad(rec, (len(noise), 0), 'constant', constant_values=0)
    # print(rec)
    Nw = len(noise)
    assert Nw == len(rec)
    rec_fft = np.fft.rfft(rec)
    noise_fft_conj = np.conj(np.fft.rfft(noise))
    # print(rec_fft.shape, noise_fft_conj.shape)
    cross_corr_freq = noise_fft_conj * rec_fft
    cross_corr = np.abs(np.fft.irfft(cross_corr_freq))

    # valid_len = diff + 1
    # cross_corr = cross_corr[:valid_len]

    # print(cross_corr)
    # plt.plot(cross_corr)
    # plt.title("correlation " + name)

    k_max_ind = np.argmax(cross_corr)
    k_max = cross_corr[k_max_ind]
    avg = np.sum(cross_corr) / len(cross_corr)

    return k_max_ind, k_max, avg


def fangs_algorithm_TDoA(ta, tb, tc):
    Nw = len(noiseA)
    # The correlation wraps around, this can cause issues when 1 val is close to index 0, and the other close to Nw
    # assume the tdoa is always less than Nw/2, if not then substract 1 val Nw, this should bring substraction back in the range
    # substracting the largest value by Nw makes it negative
    # tab = min([ta-tb, ta-tb-Nw, ta-tb+Nw], key=lambda x: abs(x))
    # tac = min([ta-tc, ta-tc-Nw, ta-tc+Nw], key=lambda x: abs(x))

    ## Fang's algorithm, gotten from the PDF (in the repo or at https://ieeexplore.ieee.org/document/102710)
    c = 343  # speed of wave in medium, speed of sound=343 m/s

    cTa = ta * c
    cTb = tb * c
    cTc = tc * c

    b = B[0]  # also = np.linalg.norm(B)
    cx = C[0]
    cy = C[1]
    c = np.linalg.norm(C)

    Rab = cTa - cTb
    Rac = cTa - cTc
    # Rab = c*tab
    # Rac = c*tac

    # avoid division by zero, just make em real small
    if Rab == 0.0:
        Rab = 1e-5
    if Rac == 0.0:
        Rac = 1e-5

    # variable names correspond to those in the paper

    g = (Rac * b / Rab - cx) / cy
    h = (c ** 2 - Rac ** 2 + Rac * Rab * (1 - (b / Rab) ** 2)) / (2 * cy)

    d = -(1 - (b / Rab) ** 2 + g ** 2)
    e = b * (1 - (b / Rab) ** 2) - 2 * g * h
    f = (Rab ** 2 / 4) * (1 - (b / Rab) ** 2) ** 2 - h ** 2

    z = Z_MIC_RELATIVE_TO_SPEAKERS
    x = np.roots([d, e, f - z ** 2])  # eq 9a
    x = x[abs(x.imag) < 1e-5]  # ignore imaginary roots
    y = g * x + h  # eq 13
    # print(x, y)

    guesses = np.transpose([x, y])

    # print(guesses)

    def err(g):
        # calculate what sort of time deltas would be seen with this guess
        # compare them to the original, return the MSE
        deltaA = np.linalg.norm(g - A)
        deltaB = np.linalg.norm(g - B)
        deltaC = np.linalg.norm(g - C)
        rab = deltaA - deltaB
        rac = deltaA - deltaC
        mse = ((rab - Rab) ** 2 + (rac - Rac) ** 2) / 2
        return mse

    if len(guesses) == 0:
        return None

    best_guess = min(guesses, key=err)
    return best_guess

def plot_spect(sound):
  f, t, Sxx = sp.signal.spectrogram(sound, 50000)
  plt.pcolormesh(t, f, Sxx, shading='gouraud')
  plt.ylabel('Frequency [Hz]')
  plt.xlabel('Time [sec]')
  plt.ylim((1000, 5000))

positions = {}


def main_task():
    Nw = len(noiseA)
    sound = np.zeros(Nw)

    with serial.Serial("COM11", 115200) as ser:
        # ser.set_buffer_size(rx_size = 8192)
        ser.write(b"freq\n")
        # print(ser.readline())
        ser.write(f"{50000}\n".encode())
        # print(ser.readline())
        # num_samples = int(Fs)

        plt.ion()
        plt.figure(1)
        plt.clf()

        plt.subplot(212)
        plt.scatter(
            [A[0], B[0], C[0]],
            [A[1], B[1], C[1]],
            label="base stations",
            marker="o",
        )
        a = plt.gca()
        a.set_aspect("equal")
        a.set_xlim(a.get_xlim())
        a.set_ylim(a.get_ylim())
        
        while True:
            draw_button_on = 0
            clear_button_on = 0
            separate_draw = 0

            ser.write(f"{Nw}\n".encode())
            # print(size)

            a = ser.readline()  # For draw button
            a_dec = a.decode('utf-8').strip()

            a1 = ser.readline()  # For clear button
            a1_dec = a1.decode('utf-8').strip()

            num_bytes = Nw * 2  # 2 bytes per sample
            b = ser.read(num_bytes)

            # Button stuff
            if a_dec == "press":
                draw_button_on = 1

            # Separate characters
            if a_dec == "yyyyy":
                separate_draw = 1

            if a1_dec == "cleared":
                clear_button_on = 1

            sound = np.frombuffer(b, dtype="<i2")
            # Keep this
            # plt.ion()
            # plt.figure(1)
            # plt.clf()

            found_delay1, max1, avg1 = correlate_and_find_delay(
                sound, noiseA, "A"
            )

            found_delay2, max2, avg2 = correlate_and_find_delay(
                sound, noiseB, "B"
            )

            found_delay3, max3, avg3 = correlate_and_find_delay(
                sound, noiseC, "C"
            )

            # Keep this
            # plt.subplot(212)
            # plt.scatter(
            #     [A[0], B[0], C[0]],
            #     [A[1], B[1], C[1]],
            #     label="base stations",
            #     marker="o",
            # )
            # a = plt.gca()
            # a.set_aspect("equal")
            # a.set_xlim(a.get_xlim())
            # a.set_ylim(a.get_ylim())

            ta = found_delay1 / 48000
            tb = found_delay2 / 48000
            tc = found_delay3 / 48000

            guessed_position = fangs_algorithm_TDoA(ta, tb, tc)

            if guessed_position is not None:
                positions["self"] = guessed_position
            print(positions)
            for name, position in positions.items():
                plt.scatter(position[0], position[1], label=name)

            plt.gca().set_aspect("equal")
            plt.legend(loc="center left", bbox_to_anchor=(1.0, 0.5))

            # Plot base stations
            plt.subplot(211)
            plt.scatter(
                [A[0], B[0], C[0]],
                [A[1], B[1], C[1]],
                marker="o",
            )
            a = plt.gca()
            a.set_aspect("equal")
            a.set_xlim(a.get_xlim())
            a.set_ylim(a.get_ylim())

            # Draw button
            if draw_button_on == 1:

                # For debugging
                print("THE DRAWING BUTTON IS WORKING!")

                # Only append to the list of guessed positions if is it not None
                if guessed_position is not None:
                    guessed_positions.append(guessed_position)
                print(guessed_positions)

                # Extract x, y coordinate from list
                x_elem = [x[0] for x in guessed_positions]
                y_elem = [x[1] for x in guessed_positions]

                # Appending drawing to Figure 1
                plt.subplot(211)

                # Plot the point
                plt.plot(x_elem, y_elem, color='blue')

            if clear_button_on == 1:
                print("THE CLEAR BUTTON IS WORKING!!")
                guessed_positions.clear()
                plt.subplot(211)
                plt.clf()

            if separate_draw == 1:
                # Only append to the list of guessed positions if is it not None
                if guessed_position is not None:
                    guessed_positions.append(guessed_position)
                print(guessed_positions)

                # Extract x, y coordinate from list
                x_elem = [x[0] for x in guessed_positions]
                y_elem = [x[1] for x in guessed_positions]

                # Appending drawing to Figure 1
                plt.subplot(211)

                # Plot the point
                plt.plot(x_elem, y_elem, color='white')

            plt.show()
            plt.pause(0.01)

main_task()
