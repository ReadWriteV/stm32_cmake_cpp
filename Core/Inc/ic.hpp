#ifndef __IC_H
#define __IC_H

#include "stm32f10x.h"

/*
    OLED oled;
    PWM generator;
    IC cal;

    oled.show(1, 1, "Freq:00000Hz");
    oled.show(3, 1, "Duty:000%");
    while (true)
    {
        oled.show(1, 8 * 5 + 1, cal.get_freq(), 5);
        oled.show(3, 8 * 5 + 1, cal.get_duty(), 3);
    }
 */

class IC
{
public:
    IC();

    uint32_t get_freq();
    uint32_t get_duty();
};

#endif
