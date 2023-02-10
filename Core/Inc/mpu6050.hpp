#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f10x.h"

class MPU6050
{
public:
    MPU6050();
    uint8_t get_id();
    void get_data(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                  int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

private:
    void wait_event(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT);
    void write_reg(uint8_t RegAddress, uint8_t Data);
    uint8_t read_reg(uint8_t RegAddress);
};

#endif
