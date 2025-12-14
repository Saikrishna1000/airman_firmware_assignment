/******************************************************************************
 * File Name   : telemetry_tx.c
 *
 * Purpose     :
 *  This file implements LEVEL-1 QUESTION-2 of the AIRMAN firmware assignment.
 *
 *  TASK OVERVIEW:
 *  1. Generate simulated sensor data (accelerometer, gyroscope, etc.)
 *  2. Build a UART telemetry frame in the EXACT required format:
 *
 *     $L1,<timestamp_ms>,<ax>,<ay>,<az>,<gx>,<gy>,<gz>,<alt>,<temp>*<CHK>
 *
 *  3. Timestamp increments every 50 ms (20 Hz).
 *  4. CHK is calculated as XOR of all characters between '$' and '*'.
 *  5. One frame is transmitted (printed) every 50 ms.
 *
 *  NOTE:
 *  - UART transmission is simulated using printf().
 *  - The same string can later be sent via real UART without changes.
 *
 * Author      : Sai Krishna
 * Platform    : PC Simulation (GCC + MSYS2)
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

/* ---------------- Sensor Data Structure ---------------- */
typedef struct
{
    float ax, ay, az;      // Accelerometer (m/s^2)
    float gx, gy, gz;      // Gyroscope (deg/s)
    float altitude;        // Altitude (meters)
    float temperature;     // Temperature (deg C)
} SensorData;

/* ---------------- Small Random Noise ---------------- */
float noise(float amplitude)
{
    return ((float)rand() / RAND_MAX * 2.0f - 1.0f) * amplitude;
}

/* ---------------- Sensor Simulation ----------------
 * Generates smooth, predictable sensor values using
 * sine/cosine functions and small noise.
 */
void simulate_sensors(SensorData *s, float *time_sec)
{
    *time_sec += 0.05f;   // 50 ms step

    /* Accelerometer */
    s->ax = sin(*time_sec) + noise(0.02f);
    s->ay = cos(*time_sec) + noise(0.02f);
    s->az = 9.81f;

    /* Gyroscope */
    s->gx = sin(*time_sec) * 30.0f + noise(0.5f);
    s->gy = cos(*time_sec) * 30.0f + noise(0.5f);
    s->gz = 5.0f;

    /* Linear altitude & slow temperature change */
    s->altitude += 0.02f;
    s->temperature = 25.0f + sin(*time_sec * 0.1f);
}

/* ---------------- Checksum Calculation ----------------
 * XOR of all characters between '$' and '*'
 */
unsigned char calculate_checksum(const char *frame)
{
    unsigned char chk = 0;

    /* Start from index 1 to skip '$' */
    for (int i = 1; frame[i] != '*'; i++)
    {
        chk ^= frame[i];
    }
    return chk;
}

/* ---------------- MAIN FUNCTION ---------------- */
int main(void)
{
    SensorData sensor = {0};
    float time_sec = 0.0f;
    uint32_t timestamp_ms = 0;

    char frame[256];
    char final_frame[300];

    sensor.altitude = 10.0f;
    srand(time(NULL));   // Seed random noise

    while (1)
    {
        /* 1. Generate simulated sensor data */
        simulate_sensors(&sensor, &time_sec);

        /* 2. Update timestamp (20 Hz → 50 ms) */
        timestamp_ms += 50;

        /* 3. Build telemetry frame WITHOUT checksum */
        snprintf(frame, sizeof(frame),
                 "$L1,%lu,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f*",
                 timestamp_ms,
                 sensor.ax, sensor.ay, sensor.az,
                 sensor.gx, sensor.gy, sensor.gz,
                 sensor.altitude,
                 sensor.temperature);

        /* 4. Calculate XOR checksum */
        unsigned char chk = calculate_checksum(frame);

        /* 5. Append checksum to frame */
        snprintf(final_frame, sizeof(final_frame),
                 "%s%02X\n", frame, chk);

        /* 6. Transmit frame (UART simulated using printf) */
        printf("%s", final_frame);

        /* 7. Maintain 20 Hz rate */
        usleep(50000);
    }

    return 0;
}
