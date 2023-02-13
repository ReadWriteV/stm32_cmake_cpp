#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/**
    LED D0(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_8);
    LED D1(RCC_APB2Periph_GPIOD, GPIOD, GPIO_Pin_2, false);

    D0.on();
    D1.off();

    while (true)
    {
        D0.toggle();
        D1.toggle();
        delay_ms(100);
    }
*/

class LED
{
public:
    LED(uint32_t clock, GPIO_TypeDef *port, uint16_t pin, bool low_triggle = true);
    void on() const;
    void off() const;
    void toggle() const;

private:
    GPIO_TypeDef *port;
    uint16_t pin;
    bool low_triggle;
};

#endif
