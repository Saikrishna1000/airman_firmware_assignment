---

## Level 2 – Advanced Extension (Partial Implementation)

### Overview
Level 2 extends the telemetry pipeline by adding attitude estimation (AHRS) and real-time visualization.  
A **basic complementary filter** is used to compute orientation from simulated sensor data.

---

### Level 2 – Question 1: AHRS Algorithm
- Implemented a **Complementary Filter**
- Inputs:
  - Accelerometer
  - Gyroscope
  - Magnetometer
- Outputs:
  - Roll
  - Pitch
  - Heading (Yaw)

The complementary filter combines:
- Gyroscope integration for short-term motion
- Accelerometer correction for long-term stability

This approach is computationally light and suitable for embedded systems.

Files:
- `level2_half/ahrs.c`
- `level2_half/ahrs.h`

---

### Level 2 – Question 2: Enhanced Telemetry Frame
A new Level-2 telemetry frame is generated:


- Uses the same XOR checksum method as Level-1
- Demonstrates protocol extensibility

File:
- `level2_half/telemetry_tx_l2.c`

---

### Level 2 – Question 3: Real-Time Visualization
- Implemented real-time plotting using **matplotlib**
- Roll, Pitch, and Heading plotted at ~10 Hz
- Confirms AHRS output visually

File:
- `level2_half/plot_live.py`

---

### Performance
- Update rate: ~10 Hz (visualization)
- Stable roll and pitch estimation
- Suitable for simulation and embedded prototyping

---

### Limitations
- Complementary filter is not as accurate as Madgwick or Mahony filters
- Magnetometer is not tilt-compensated
- No 3D visualization implemented

---

### AI Usage
AI tools were used for:
- Understanding AHRS concepts
- Verifying complementary filter equations
- Reviewing code structure and documentation

---
