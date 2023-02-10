#include "led.hpp"

LED::LED(uint32_t clock, GPIO_TypeDef *port, uint16_t pin, bool low_triggle) : port(port), pin(pin), low_triggle(low_triggle)
{
    RCC_APB2PeriphClockCmd(clock, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Speed = GPIOSpeed_TypeDef::GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIOMode_TypeDef::GPIO_Mode_Out_PP;
    GPIO_Init(port, &GPIO_InitStructure);
}

void LED::on() const
{
    if (low_triggle)
    {
        GPIO_ResetBits(port, pin);
    }
    else
    {
        GPIO_SetBits(port, pin);
    }
}

void LED::off() const
{
    if (low_triggle)
    {
        GPIO_SetBits(port, pin);
    }
    else
    {
        GPIO_ResetBits(port, pin);
    }
}

void LED::toggle() const
{
    port->ODR ^= pin;
}
