"""
plot_live.py

Level 2 - Question 3
Real-time visualization of Roll, Pitch, Heading
Reads L2 telemetry frames from stdin
"""

import sys
import time
import matplotlib.pyplot as plt
from collections import deque

# Buffer size for plots
MAX_POINTS = 100

roll_data = deque(maxlen=MAX_POINTS)
pitch_data = deque(maxlen=MAX_POINTS)
heading_data = deque(maxlen=MAX_POINTS)

time_data = deque(maxlen=MAX_POINTS)

plt.ion()
fig, axs = plt.subplots(3, 1, figsize=(8, 6))

axs[0].set_title("Roll (deg)")
axs[1].set_title("Pitch (deg)")
axs[2].set_title("Heading (deg)")

for ax in axs:
    ax.set_ylim(-180, 180)
    ax.grid(True)

start_time = time.time()

print("Waiting for L2 telemetry frames...")

while True:
    line = sys.stdin.readline().strip()
    if not line:
        continue

    if not line.startswith("$L2"):
        continue

    try:
        payload, chk = line[1:].split("*")
        fields = payload.split(",")

        # $L2,timestamp,roll,pitch,heading,alt,temp
        timestamp = int(fields[1])
        roll = float(fields[2])
        pitch = float(fields[3])
        heading = float(fields[4])

        t = time.time() - start_time

        time_data.append(t)
        roll_data.append(roll)
        pitch_data.append(pitch)
        heading_data.append(heading)

        axs[0].cla()
        axs[1].cla()
        axs[2].cla()

        axs[0].plot(time_data, roll_data)
        axs[1].plot(time_data, pitch_data)
        axs[2].plot(time_data, heading_data)

        axs[0].set_title("Roll (deg)")
        axs[1].set_title("Pitch (deg)")
        axs[2].set_title("Heading (deg)")

        for ax in axs:
            ax.grid(True)

        plt.pause(0.01)  # ~10 Hz refresh

    except Exception as e:
        print("Parse error:", e)
