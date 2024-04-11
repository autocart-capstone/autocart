import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import matplotlib.animation as pltAnim
import serial
import threading
import queue
import copy

noiseA = np.load("misc/filtered_noiseA.npy")
noiseB = np.load("misc/filtered_noiseB.npy")
noiseC = np.load("misc/filtered_noiseC.npy")

A = np.array([0, 0])
B = np.array([0.82, 0])
C = np.array([0.82 / 2, 0.551])
Z_MIC_RELATIVE_TO_SPEAKERS = 0.195

assert A[0] == 0 and A[1] == 0
assert B[0] > 0 and B[1] == 0
assert C[1] > 0


def correlate_and_find_delay(rec, noise, name):
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
    k_max_ind = np.argmax(cross_corr)
    k_max = cross_corr[k_max_ind]
    avg = np.sum(cross_corr) / len(cross_corr)

    return k_max_ind, k_max, avg, cross_corr


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
    h = (c**2 - Rac**2 + Rac * Rab * (1 - (b / Rab) ** 2)) / (2 * cy)

    d = -(1 - (b / Rab) ** 2 + g**2)
    e = b * (1 - (b / Rab) ** 2) - 2 * g * h
    f = (Rab**2 / 4) * (1 - (b / Rab) ** 2) ** 2 - h**2

    z = Z_MIC_RELATIVE_TO_SPEAKERS
    x = np.roots([d, e, f - z**2])  # eq 9a
    x = x[
        (abs(x.imag) < 1e-5) & (x.real >= A[0]) & (x.real <= B[0])
    ]  # ignore imaginary roots and points beyond axis limits
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
    plt.pcolormesh(t, f, Sxx, shading="gouraud")
    plt.ylabel("Frequency [Hz]")
    plt.xlabel("Time [sec]")
    plt.ylim((1000, 5000))


INVALID_CURSOR_POS = (-100.0, -100.0)  # off the shown map hopefully

thread_queue = queue.Queue()


class QueueMsg:
    def __init__(
        self, cross_corrA, cross_corrB, cross_corrC, positions, cursor_position
    ) -> None:
        self.cross_corrA = cross_corrA
        self.cross_corrB = cross_corrB
        self.cross_corrC = cross_corrC
        self.positions = positions
        self.cursor_position = cursor_position


def do_plot():
    fig = plt.figure(1)
    axA = plt.subplot(231)
    axB = plt.subplot(232, sharey=axA)
    axC = plt.subplot(233, sharey=axA)

    axMap = plt.subplot(212)

    def update_plot(frame):
        if thread_queue.empty():
            return
        msg = thread_queue.get()

        axA.clear()
        axA.plot(msg.cross_corrA)
        axA.set_title("Correlation A")

        axB.clear()
        axB.plot(msg.cross_corrB)
        axB.set_title("Correlation B")
        axB.tick_params("y", labelleft=False)

        axC.clear()
        axC.plot(msg.cross_corrC)
        axC.set_title("Correlation C")
        axC.tick_params("y", labelleft=False)

        axMap.clear()
        axMap.scatter(
            [A[0], B[0], C[0]],
            [A[1], B[1], C[1]],
            label="base stations",
            marker="o",
            color="purple",
        )
        axMap.set_aspect("equal")
        axMap.set_xlim(axMap.get_xlim())
        axMap.set_ylim(axMap.get_ylim())

        for line in msg.positions:
            axMap.plot(line[0], line[1], color="blue", linewidth="2")

        axMap.scatter(
            msg.cursor_position[0],
            msg.cursor_position[1],
            color="lightblue",
        )
        fig.canvas.draw()

    anim = pltAnim.FuncAnimation(fig, update_plot, cache_frame_data=False, interval=10)
    plt.show(block=True)


def main_task_pico():
    Nw = len(noiseA)
    positions = []
    positions.append([[], []])
    pos_idx = 0
    with serial.Serial("COM14", 115200) as ser:
        # ser.set_buffer_size(rx_size = 8192)
        ser.write(b"freq\n")
        # print(ser.readline())
        ser.write(f"{50000}\n".encode())
        # print(ser.readline())
        # num_samples = int(Fs)
        while True:
            draw_button_on = 0
            clear_button_on = 0

            ser.write(f"{Nw}\n".encode())
            # print(size)

            rcv_draw = ser.readline()  # For draw button
            rcv_draw = rcv_draw.decode("utf-8").strip()

            rcv_clear = ser.readline()  # For clear button
            rcv_clear = rcv_clear.decode("utf-8").strip()

            num_bytes = Nw * 2  # 2 bytes per sample
            b = ser.read(num_bytes)

            sound = np.frombuffer(b, dtype="<i2")

            found_delay1, max1, avg1, cross_corrA = correlate_and_find_delay(
                sound, noiseA, "A"
            )
            found_delay2, max2, avg2, cross_corrB = correlate_and_find_delay(
                sound, noiseB, "B"
            )
            found_delay3, max3, avg3, cross_corrC = correlate_and_find_delay(
                sound, noiseC, "C"
            )

            ta = found_delay1 / 50000
            tb = found_delay2 / 50000
            tc = found_delay3 / 50000

            guessed_position = fangs_algorithm_TDoA(ta, tb, tc)

            # Button stuff
            if rcv_draw == "press":
                draw_button_on = True

            if rcv_clear == "cleared":
                clear_button_on = True

            if guessed_position is None:
                cursor_position = INVALID_CURSOR_POS

            else:
                cursor_position = guessed_position
                if draw_button_on:
                    # If button is pressed
                    positions[pos_idx][0].append(
                        guessed_position[0]
                    )  # Add x coord in the curr drawing list
                    positions[pos_idx][1].append(
                        guessed_position[1]
                    )  # Add y coord in the curr drawing list
                else:
                    # If button is released, add new list to positions
                    positions.append([[], []])
                    pos_idx += 1

            if clear_button_on == 1:
                positions.clear()
                positions.append([[], []])
                pos_idx = 0

            if thread_queue.empty():
                thread_queue.put(
                    QueueMsg(
                        cross_corrA,
                        cross_corrB,
                        cross_corrC,
                        copy.deepcopy(positions),
                        cursor_position,
                    )
                )
            else:
                print("dropping frame")


def main_task_mic():
    Nw = len(noiseA)

    audio_buffer_queue = queue.Queue()

    def audio_callback(indata, frames, time, status):
        """This is called (from a separate thread) for each audio block."""

        if status:
            print(status)

        length = min(Nw - audio_callback.index, frames)
        audio_callback.buffer[audio_callback.index : audio_callback.index + length] = (
            indata[:length].flatten()
        )

        audio_callback.index += length

        if audio_callback.index >= Nw:
            audio_callback.index = 0
            if audio_buffer_queue.empty():
                audio_buffer_queue.put(audio_callback.buffer.copy())
            else:
                print("dropping sound")

    audio_callback.index = 0
    audio_callback.buffer = np.zeros(Nw)

    import sounddevice as sd

    stream = sd.InputStream(channels=1, samplerate=48000, callback=audio_callback)
    with stream:
        positions = []
        while True:
            sound = audio_buffer_queue.get()

            found_delay1, max1, avg1, cross_corrA = correlate_and_find_delay(
                sound, noiseA, "A"
            )
            found_delay2, max2, avg2, cross_corrB = correlate_and_find_delay(
                sound, noiseB, "B"
            )
            found_delay3, max3, avg3, cross_corrC = correlate_and_find_delay(
                sound, noiseC, "C"
            )

            ta = found_delay1 / 50000
            tb = found_delay2 / 50000
            tc = found_delay3 / 50000

            guessed_position = fangs_algorithm_TDoA(ta, tb, tc)

            if guessed_position is None:
                cursor_position = INVALID_CURSOR_POS

            else:
                cursor_position = guessed_position

            if thread_queue.empty():
                thread_queue.put(
                    QueueMsg(
                        cross_corrA,
                        cross_corrB,
                        cross_corrC,
                        positions.copy(),
                        cursor_position,
                    )
                )
            else:
                print("dropping frame")


t1 = threading.Thread(target=main_task_pico, daemon=True)
# t1 = threading.Thread(target=main_task_mic, daemon=True)
t1.start()

do_plot()
