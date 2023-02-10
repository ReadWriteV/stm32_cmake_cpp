#include "i2c.hpp"

I2C::I2C(uint32_t clock, GPIO_TypeDef *port, uint16_t scl_pin, uint16_t sda_pin)
    : port(port), scl_pin(scl_pin), sda_pin(sda_pin)
{
    RCC_APB2PeriphClockCmd(clock, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Pin = scl_pin | sda_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStructure);

    GPIO_SetBits(port, scl_pin | sda_pin);
}

void I2C::start() const
{
    SDA(1);
    SCL(1);
    SDA(0);
    SCL(0);
}

void I2C::stop() const
{
    SDA(0);
    SCL(1);
    SDA(1);
}

void I2C::send_byte(uint8_t byte) const
{
    for (uint8_t i = 0; i < 8; i++)
    {
        SDA(byte & (0x80 >> i));
        SCL(1);
        SCL(0);
    }
}

uint8_t I2C::receive_byte() const
{
    uint8_t byte = 0x00;
    SDA(1);
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL(1);
        if (SDA() == 1)
        {
            byte |= (0x80 >> i);
        }
        SCL(0);
    }
    return byte;
}

void I2C::send_ack(uint8_t ack) const
{
    SDA(ack);
    SCL(1);
    SCL(0);
}

uint8_t I2C::receive_ack() const
{
    SDA(1);
    SCL(1);
    uint8_t ack = SDA();
    SCL(0);
    return ack;
}
