#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

#include "stm32f10x.h"

class CountSensor
{
public:
    CountSensor(uint32_t clock = RCC_APB2Periph_GPIOB, GPIO_TypeDef *port = GPIOB, uint16_t pin = GPIO_Pin_14);
    void handle();
    uint16_t get_count();

private:
    GPIO_TypeDef *port;
    uint16_t pin;
    uint16_t count;
};

#endif
