#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>   // for usleep()
#include <time.h>

/* ---------------- Sensor Data Structure ---------------- */
typedef struct
{
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float altitude;
    float temperature;
} SensorData;

/* ---------------- Noise Generator ---------------- */
float noise(float amplitude)
{
    return ((float)rand() / RAND_MAX * 2.0f - 1.0f) * amplitude;
}

/* ---------------- Sensor Simulation Function ---------------- */
void simulate_sensors(SensorData *data, float *time_sec)
{
    /* advance time by 50 ms */
    *time_sec += 0.05f;

    /* Accelerometer (m/s^2) */
    data->ax = sinf(*time_sec) + noise(0.02f);
    data->ay = cosf(*time_sec) + noise(0.02f);
    data->az = 9.81f;

    /* Gyroscope (deg/s) */
    data->gx = sinf(*time_sec) * 30.0f + noise(0.5f);
    data->gy = cosf(*time_sec) * 30.0f + noise(0.5f);
    data->gz = 5.0f;

    /* Magnetometer (relative units) */
    data->mx = cosf(*time_sec);
    data->my = sinf(*time_sec);
    data->mz = 0.2f;

    /* Altitude (meters) – linear increase */
    data->altitude += 0.02f;

    /* Temperature (°C) – slow variation */
    data->temperature = 25.0f + sinf(*time_sec * 0.1f);
}

/* ---------------- Main ---------------- */
int main(void)
{
    SensorData sensor = {0};
    float time_sec = 0.0f;

    /* Initial values */
    sensor.altitude = 10.0f;

    /* Seed random number generator */
    srand(time(NULL));

    while (1)
    {
        simulate_sensors(&sensor, &time_sec);

        /* For now, print values (UART comes in Question 2) */
        printf(
            "ACC[%.2f %.2f %.2f]  "
            "GYR[%.2f %.2f %.2f]  "
            "MAG[%.2f %.2f %.2f]  "
            "ALT=%.2f m  TEMP=%.2f C\n",
            sensor.ax, sensor.ay, sensor.az,
            sensor.gx, sensor.gy, sensor.gz,
            sensor.mx, sensor.my, sensor.mz,
            sensor.altitude,
            sensor.temperature
        );

        usleep(50000);   // 50 ms → 20 Hz
    }

    return 0;
}
