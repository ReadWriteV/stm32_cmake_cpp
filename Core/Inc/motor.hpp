#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

/*
 */

class Motor
{
public:
    Motor();

    void set_speed(int8_t speed);
};

#endif