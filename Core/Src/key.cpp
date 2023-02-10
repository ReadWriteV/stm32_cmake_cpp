#include "key.hpp"
#include "common.hpp"

Key::Key(uint32_t clock, GPIO_TypeDef *port, uint16_t pin, bool low_triggle) : port(port), pin(pin), low_triggle(low_triggle)
{
    RCC_APB2PeriphClockCmd(clock, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Speed = GPIOSpeed_TypeDef::GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIOMode_TypeDef::GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);
}

bool Key::is_pressed() const
{
    uint8_t pressed_flag = low_triggle ? 0 : 1;
    if (GPIO_ReadInputDataBit(port, pin) == pressed_flag)
    {
        delay_ms(20);
        if (GPIO_ReadInputDataBit(port, pin) == pressed_flag)
        {
            while (GPIO_ReadInputDataBit(port, pin) == pressed_flag)
                ;
            return true;
        }
    }
    return false;
}