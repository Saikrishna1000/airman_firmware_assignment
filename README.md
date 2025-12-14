# AIRMAN Firmware Developer – Technical Assignment

## Goal
Build a basic telemetry pipeline using simulated sensor data, transmit it over a UART-like interface, and receive, validate, and log the data using a Python script.

---

## Level 1 – Implementation Overview

### Question 1: Sensor Data Generation
- Sensor data is simulated using mathematical functions.
- Accelerometer and gyroscope data are generated using sine and cosine waves.
- Altitude follows a linear and predictable pattern.
- Temperature varies slowly to emulate real sensor behavior.
- Data generation rate: 20 Hz (one frame every 50 ms).

---

### Question 2: UART Telemetry Frame Format
- Telemetry frames are transmitted in the following format:


- Frames are sent every 50 ms.
- Checksum (CHK) is calculated as the XOR of all characters between `$` and `*`.

---

### Question 3: Python Receiver Script
- A Python script (`uart_rx.py`) acts as a telemetry receiver.
- It reads incoming telemetry frames via standard input (UART simulation).
- The script validates the XOR checksum.
- Valid frames are parsed and logged into a CSV file.
- Parsed sensor values are printed in real time on the terminal.
- No visualization is used as per Level 1 requirements.

---

### Question 4: Level 1 Deliverables
The following deliverables are provided:
- `telemetry_tx.c` – Telemetry transmitter (C)
- `uart_rx.py` – Telemetry receiver (Python)
- `sample_outputs/output.csv` – Sample logged telemetry data
- This README file

```md
## How to Compile and Run

### Compile the Transmitter
```bash
gcc telemetry_tx.c -o telemetry_tx -lm


Run the End-to-End Telemetry Pipeline

telemetry_tx | python uart_rx.py
UART communication is simulated using stdin/stdout piping.

airman_firmware_assignment/
├── level1_q1_simulation/
├── level1_q2_uart_frame/
├── level1_q3_python_rx/
│   ├── uart_rx.py
│   └── output.csv
├── sample_outputs/
│   └── output.csv
└── README.md

AI Tools Used

ChatGPT was used for:

Understanding and clarifying assignment requirements

Verifying checksum logic

Reviewing code structure and documentation

Assumptions and Simplifications

UART communication is simulated instead of using real serial hardware.

Sensor data is generated using mathematical functions rather than real sensors.

Magnetometer data was omitted to keep the implementation simple.

The focus was on correctness, clarity, and reproducibility.