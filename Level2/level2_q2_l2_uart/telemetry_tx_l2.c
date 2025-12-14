/*
 * Level 2 Telemetry Transmitter
 * Sends AHRS roll, pitch, heading
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ahrs.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

unsigned char checksum(const char *s)
{
    unsigned char chk = 0;
    while (*s) chk ^= *s++;
    return chk;
}

int main(void)
{
    AHRS_Init();
    int timestamp = 0;

    while (1)
    {
        /* Simulated sensor data */
        float ax = sin(timestamp * 0.01f);
        float ay = cos(timestamp * 0.01f);
        float az = 9.81f;

        float gx = 1.0f;
        float gy = 0.5f;
        float gz = 0.2f;

        float alt  = 100.0f + sin(timestamp * 0.005f);
        float temp = 25.0f;

        AHRS_Output_t ahrs =
            AHRS_Update(ax, ay, az, gx, gy, gz, 0.1f);

        char payload[256];
        sprintf(payload,
                "L2,%d,%.2f,%.2f,%.2f,%.2f,%.2f",
                timestamp,
                ahrs.roll,
                ahrs.pitch,
                ahrs.yaw,
                alt,
                temp);

        unsigned char chk = checksum(payload);

        printf("$%s*%02X\n", payload, chk);

#ifdef _WIN32
        Sleep(100);
#else
        usleep(100000);
#endif

        timestamp += 100;
    }
}
