#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

/**
    OLED oled;
    ADC adc1;
    oled.show(1, 1, "voltage:");
    float voltage;
    while (true)
    {
        voltage = static_cast<float>(adc1.get_value()) / 4095 * 3.3;
        oled.show(1, 8 * 8 + 1, static_cast<uint32_t>(voltage), 1);
        oled.show(1, 8 * 9 + 1, '.');
        oled.show(1, 8 * 10 + 1, static_cast<uint32_t>(voltage * 100) % 100, 2);
    }
*/

class ADC
{
public:
    ADC();
    uint16_t get_value();
};

#endif