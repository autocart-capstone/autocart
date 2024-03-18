"""
    For debugging purposes. To be integrated with the main py file for sound localization
"""

import numpy as np
import matplotlib.pyplot as plt

guessed_positions = [(0.150, 0.150), (0.150, 0.350), (0.300, 0.150), (0.300, 0.350), \
                     (0.500, 0.350), (0.500, 0.150), (0.700, 0.150), (0.700, 0.350)] #Printing out NU

positions = {}

A = np.array([0, 0])
B = np.array([0.82, 0])
C = np.array([0.82/2, 0.551])

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
axes2 = plt.gca()
axes2.set_aspect("equal")
axes2.set_xlim(axes2.get_xlim())
axes2.set_ylim(axes2.get_ylim())

plt.subplot(211)
plt.scatter(
    [A[0], B[0], C[0]],
    [A[1], B[1], C[1]],
    label="base stations",
    marker="o",
)
axes1 = plt.gca()
axes1.set_aspect("equal")
axes1.set_xlim(axes1.get_xlim())
axes1.set_ylim(axes1.get_ylim())

clearDrawing = False
buttonPressed = False
new_drawing_idx = 0
x_pts = []
y_pts = []
drawing = []
drawing.append((x_pts, y_pts))

# [([x11, x12, x13...], [y11, y12, y13]), ([x21, x22,.. ],)]

# while True:
for guessed_position in guessed_positions:
    if guessed_position is not None:
        positions["self"] = guessed_position

    # Clear subplot 212 before replotting to update the lines
    plt.subplot(212)
    plt.cla()
    plt.scatter(
        [A[0], B[0], C[0]],
        [A[1], B[1], C[1]],
        label="base stations",
        marker="o",
    )
    if not buttonPressed:
        plt.subplot(211)
        plt.cla()
        plt.scatter(
            [A[0], B[0], C[0]],
            [A[1], B[1], C[1]],
            label="base stations",
            marker="o",
        )
    
    for name, position in positions.items():
        plt.subplot(212)
        plt.scatter(position[0], position[1], label=name)
        plt.subplot(211)
        plt.scatter(position[0], position[1], label=name)

    # if guessed_position[0] == 0.5 and guessed_position[1] == 0.150:
    #     clearDrawing = True

    if guessed_position[0] == 0.5 and guessed_position[1] == 0.350:
        # if buttonPressed:
        #     buttonPressed =  False
        # else: 
        #     buttonPressed = True
        buttonPressed = True
        new_drawing_idx += 1
        drawing.append(([],[]))

    drawing[new_drawing_idx][0].append(guessed_position[0])
    drawing[new_drawing_idx][1].append(guessed_position[1])
    if buttonPressed:
        plt.subplot(211)
        # plt.scatter(drawing[new_drawing_idx][0], drawing[new_drawing_idx][1], label=name)
        plt.plot(drawing[new_drawing_idx][0], drawing[new_drawing_idx][1])

    # if clearDrawing:
    #     plt.subplot(211)
    #     plt.cla()
    #     plt.scatter(
    #         [A[0], B[0], C[0]],
    #         [A[1], B[1], C[1]],
    #         label="base stations",
    #         marker="o",
    #     )

    plt.show()
    plt.pause(0.5)
        
