#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/*
    Key KEY_0(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_1);
    Key KEY_1(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_13);

    while (true)
    {
        if (KEY_0.is_pressed() == true)
        {
        }
        else if (KEY_1.is_pressed() == true)
        {
        }
    }
*/

class Key
{
public:
    Key(uint32_t clock, GPIO_TypeDef *port, uint16_t pin, bool low_triggle = true);
    bool is_pressed() const;

private:
    GPIO_TypeDef *port;
    uint16_t pin;
    bool low_triggle;
};

#endif