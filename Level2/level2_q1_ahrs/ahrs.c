#include "ahrs.h"
#include <math.h>

static float roll = 0.0f;
static float pitch = 0.0f;
static float yaw = 0.0f;

void AHRS_Init(void)
{
    roll = pitch = yaw = 0.0f;
}

AHRS_Output_t AHRS_Update(
    float ax, float ay, float az,
    float gx, float gy, float gz,
    float dt)
{
    /* Accelerometer angles */
    float roll_acc  = atan2f(ay, az) * 180.0f / M_PI;
    float pitch_acc = atan2f(-ax, sqrtf(ay*ay + az*az)) * 180.0f / M_PI;

    /* Gyro integration */
    roll  += gx * dt;
    pitch += gy * dt;
    yaw   += gz * dt;

    /* Complementary filter */
    roll  = 0.98f * roll  + 0.02f * roll_acc;
    pitch = 0.98f * pitch + 0.02f * pitch_acc;

    AHRS_Output_t out = { roll, pitch, yaw };
    return out;
}
