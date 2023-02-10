#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

/*
    PWM pwm;
    while (true)
    {
        for (uint16_t i = 0; i <= 100; i++)
        {
            pwm.set_compare(i);
            delay_ms(10);
        }
        for (uint16_t i = 0; i <= 100; i++)
        {
            pwm.set_compare(100 - i);
            delay_ms(10);
        }
    }
*/

class PWM
{
public:
    PWM();

    void set_compare(uint16_t compare);
    void set_prescaler(uint16_t prescaler);
};

#endif