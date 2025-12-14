#ifndef AHRS_H
#define AHRS_H

typedef struct
{
    float roll;
    float pitch;
    float yaw;
} AHRS_Output_t;

/* Initialize AHRS */
void AHRS_Init(void);

/* Update AHRS using accel + gyro (simple complementary filter) */
AHRS_Output_t AHRS_Update(
    float ax, float ay, float az,
    float gx, float gy, float gz,
    float dt
);

#endif
