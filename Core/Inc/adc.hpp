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

private:
    static constexpr inline ADC_TypeDef *adc = ADC1;
    static constexpr inline uint8_t adc_channel = ADC_Channel_0;
    static constexpr inline uint32_t adc_clock = RCC_APB2Periph_ADC1;
    static constexpr inline uint32_t adc_gpio_clock = RCC_APB2Periph_GPIOA;
    static constexpr inline uint16_t adc_gpio_pin = GPIO_Pin_0;
    static constexpr inline GPIO_TypeDef *adc_gpio_port = GPIOA;
};

#endif
