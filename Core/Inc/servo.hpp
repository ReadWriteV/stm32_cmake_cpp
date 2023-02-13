#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"

class Servo
{
public:
    Servo();

    /// @brief set angle of servo
    /// @param angle expected angle
    void set_angle(float angle);
};

#endif
