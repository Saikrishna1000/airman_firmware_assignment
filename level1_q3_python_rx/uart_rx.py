"""
File Name : uart_rx.py

Purpose:
LEVEL-1 QUESTION-3 of AIRMAN Firmware Assignment

- Reads telemetry frames
- Validates XOR checksum
- Parses values
- Logs valid data to output.csv
- Prints parsed output

UART is simulated using stdin.
"""

import sys
import csv

OUTPUT_FILE = "output.csv"

# ---------- Checksum function ----------
def calculate_checksum(payload: str) -> int:
    chk = 0
    for ch in payload:
        chk ^= ord(ch)
    return chk

# ---------- CSV setup ----------
csv_file = open(OUTPUT_FILE, "w", newline="")
csv_writer = csv.writer(csv_file)

csv_writer.writerow([
    "timestamp_ms",
    "ax", "ay", "az",
    "gx", "gy", "gz",
    "altitude",
    "temperature"
])

print("Waiting for telemetry frames...\n")

# ---------- Main loop ----------
for line in sys.stdin:
    line = line.strip()

    if not line.startswith("$") or "*" not in line:
        continue

    try:
        payload, recv_chk = line[1:].split("*")
        recv_chk = int(recv_chk, 16)

        calc_chk = calculate_checksum(payload)

        if calc_chk != recv_chk:
            print("Checksum FAILED:", line)
            continue

        fields = payload.split(",")

        timestamp = int(fields[1])
        ax, ay, az = map(float, fields[2:5])
        gx, gy, gz = map(float, fields[5:8])
        altitude = float(fields[8])
        temperature = float(fields[9])

        csv_writer.writerow([
            timestamp,
            ax, ay, az,
            gx, gy, gz,
            altitude,
            temperature
        ])
        csv_file.flush()

        print(
            f"OK | t={timestamp} ms | "
            f"ACC=({ax:.2f},{ay:.2f},{az:.2f}) "
            f"GYR=({gx:.2f},{gy:.2f},{gz:.2f}) "
            f"ALT={altitude:.2f} TEMP={temperature:.2f}"
        )

    except Exception as e:
        print("Parse error:", e)
