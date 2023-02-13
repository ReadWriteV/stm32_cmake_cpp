#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h" // Device header
#include "common.hpp"

/// @brief software i2c
class I2C
{
public:
    I2C(uint32_t clock = RCC_APB2Periph_GPIOB, GPIO_TypeDef *port = GPIOB, uint16_t scl_pin = GPIO_Pin_10, uint16_t sda_pin = GPIO_Pin_11);
    void start() const;
    void stop() const;

    void send_byte(uint8_t byte) const;
    uint8_t receive_byte() const;

    void send_ack(uint8_t ack) const;
    uint8_t receive_ack() const;

private:
    void SCL(uint8_t v) const
    {
        GPIO_WriteBit(port, scl_pin, static_cast<BitAction>(v));
        delay_us(10);
    }

    void SDA(uint8_t v) const
    {
        GPIO_WriteBit(port, sda_pin, static_cast<BitAction>(v));
        delay_us(10);
    }

    uint8_t SDA() const
    {
        uint8_t data = GPIO_ReadInputDataBit(port, sda_pin);
        delay_us(10);
        return data;
    }
    GPIO_TypeDef *port;
    uint16_t scl_pin;
    uint16_t sda_pin;
};

#endif
