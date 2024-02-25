import numpy as np
import matplotlib.pyplot as plt
import threading
import asyncio
from pyodide.http import pyfetch
import io
from pyscript import display

noiseA = await pyfetch("assets/filtered_noiseA.npy")
noiseB = await pyfetch("assets/filtered_noiseB.npy")
noiseC = await pyfetch("assets/filtered_noiseC.npy")

noiseA = await noiseA.bytes()
noiseB = await noiseB.bytes()
noiseC = await noiseC.bytes()

noiseA = np.load(io.BytesIO(noiseA))
noiseB = np.load(io.BytesIO(noiseB))
noiseC = np.load(io.BytesIO(noiseC))

A = np.array([0, 0])
B = np.array([10, 0])
C = np.array([5, 10])

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
    
    #valid_len = diff + 1
    #cross_corr = cross_corr[:valid_len]
    
    # print(cross_corr)
    plt.plot(cross_corr)
    plt.title("correlation " + name)

    k_max_ind = np.argmax(cross_corr)
    k_max = cross_corr[k_max_ind]
    avg = np.sum(cross_corr) / len(cross_corr)

    return k_max_ind, k_max, avg


def fangs_algorithm_TDoA(ta, tb, tc):

    Nw = len(noiseA)
    # The correlation wraps around, this can cause issues when 1 val is close to index 0, and the other close to Nw
    # assume the tdoa is always less than Nw/2, if not then substract 1 val Nw, this should bring substraction back in the range
    # substracting the largest value by Nw makes it negative
    #tab = min([ta-tb, ta-tb-Nw, ta-tb+Nw], key=lambda x: abs(x))
    #tac = min([ta-tc, ta-tc-Nw, ta-tc+Nw], key=lambda x: abs(x))

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
    #Rab = c*tab
    #Rac = c*tac

    #avoid division by zero, just make em real small
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

    z = 0
    x = np.roots([d, e, f - z**2])  # eq 9a
    y = g * x + h  # eq 13
    #print(x, y)

    guess1 = np.array([x[0], y[0]])
    guess2 = np.array([x[1], y[1]])

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

    best_guess = min([guess1, guess2], key=err)
    return best_guess

async def update_plot(audio_buffer):
    fig = plt.figure(1)
    plt.clf()
    ax1 = plt.subplot(231)
    found_delay1, max1, avg1 = correlate_and_find_delay(audio_buffer, noiseA, "A")
    plt.subplot(232, sharey=ax1)
    found_delay2, max2, avg2 = correlate_and_find_delay(audio_buffer, noiseB, "B")
    plt.tick_params('y', labelleft=False)
    plt.subplot(233, sharey=ax1)
    found_delay3, max3, avg3 = correlate_and_find_delay(audio_buffer, noiseC, "C")
    plt.tick_params('y', labelleft=False)

    ta = found_delay1 / 48000
    tb = found_delay2 / 48000
    tc = found_delay3 / 48000

    guessed_position = fangs_algorithm_TDoA(ta, tb, tc)
    print(f"pos: {guessed_position}")
    plt.subplot(212)
    plt.scatter([A[0], B[0], C[0]], [A[1], B[1], C[1]], label="base stations", marker="o")
    if guessed_position[0] > -1.0 and guessed_position[0] < 11.0 and guessed_position[1] > -1.0 and guessed_position[1] < 11.0:
        plt.scatter(guessed_position[0], guessed_position[1], label="position guess")
    else :
        plt.text(0.5, 0.5, "guessed position not within bounds", color="red", ha="center", va="center", transform=plt.gca().transAxes)
    plt.gca().set_aspect("equal")
    plt.legend(loc="center left", bbox_to_anchor=(1.0, 0.5))
    
    display(fig, append=False, target='matplot')

    await asyncio.sleep(0.1)


from pyodide.ffi import to_js
import pyodide
from pyscript import window

options = window.Object.new()
options.audio = True

stream = await window.navigator.mediaDevices.getUserMedia(options)

constraints = stream.getAudioTracks()[0].getConstraints()
constraints.sampleRate = 48000
constraints.noiseSuppresion = False
constraints.channelCount = 1
# These constraints could just do nothing...

await stream.getAudioTracks()[0].applyConstraints(constraints)
recorder = window.MediaRecorder.new(stream)

Fs = 48000
Ts = 1/Fs
Nw = len(noiseA)

options = window.Object.new()
options.sampleRate = Fs
context = window.AudioContext.new(options)

record_time = Nw * Ts

data_parsed = asyncio.Event()

async def onDataAvail(event):
    print("onDataAvail callback")
    blob = event.data
    print(blob.type)
    buf = await blob.arrayBuffer()
    decoded = await context.decodeAudioData(buf)
    print(decoded.duration)
    s = np.array(decoded.getChannelData(0))
    print(s.size)
    print(Nw)
    out = np.zeros(Nw)
    out[:min(len(s), Nw)] += s[:Nw]
    await update_plot(out)
    data_parsed.set()

pyodide.ffi.wrappers.add_event_listener(recorder, 'dataavailable', onDataAvail)

while True:
    recorder.start()
    print("recording started!")
    await asyncio.sleep(record_time)
    print("recording stopped!")
    recorder.stop()
    await data_parsed.wait()
    data_parsed.clear()
