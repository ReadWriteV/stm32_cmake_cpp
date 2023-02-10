#include "mpu6050.hpp"

#define MPU6050_ADDRESS 0xD0

#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_CONFIG 0x1A
#define MPU6050_GYRO_CONFIG 0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x47
#define MPU6050_GYRO_ZOUT_L 0x48

#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_PWR_MGMT_2 0x6C
#define MPU6050_WHO_AM_I 0x75

MPU6050::MPU6050()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 10000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStructure);

    I2C_Cmd(I2C2, ENABLE);

    write_reg(MPU6050_PWR_MGMT_1, 0x01);
    write_reg(MPU6050_PWR_MGMT_2, 0x00);
    write_reg(MPU6050_SMPLRT_DIV, 0x09);
    write_reg(MPU6050_CONFIG, 0x06);
    write_reg(MPU6050_GYRO_CONFIG, 0x18);
    write_reg(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050::get_id()
{
    return read_reg(MPU6050_WHO_AM_I);
}

void MPU6050::get_data(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    uint8_t DataH, DataL;

    DataH = read_reg(MPU6050_ACCEL_XOUT_H);
    DataL = read_reg(MPU6050_ACCEL_XOUT_L);
    *AccX = (DataH << 8) | DataL;

    DataH = read_reg(MPU6050_ACCEL_YOUT_H);
    DataL = read_reg(MPU6050_ACCEL_YOUT_L);
    *AccY = (DataH << 8) | DataL;

    DataH = read_reg(MPU6050_ACCEL_ZOUT_H);
    DataL = read_reg(MPU6050_ACCEL_ZOUT_L);
    *AccZ = (DataH << 8) | DataL;

    DataH = read_reg(MPU6050_GYRO_XOUT_H);
    DataL = read_reg(MPU6050_GYRO_XOUT_L);
    *GyroX = (DataH << 8) | DataL;

    DataH = read_reg(MPU6050_GYRO_YOUT_H);
    DataL = read_reg(MPU6050_GYRO_YOUT_L);
    *GyroY = (DataH << 8) | DataL;

    DataH = read_reg(MPU6050_GYRO_ZOUT_H);
    DataL = read_reg(MPU6050_GYRO_ZOUT_L);
    *GyroZ = (DataH << 8) | DataL;
}

void MPU6050::wait_event(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    uint32_t Timeout = 0x5000;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        Timeout--;
        if (Timeout == 0)
        {
            break;
        }
    }
}

void MPU6050::write_reg(uint8_t RegAddress, uint8_t Data)
{
    // start();
    // send_byte(MPU6050_ADDRESS);
    // receive_ack();
    // send_byte(RegAddress);
    // receive_ack();
    // send_byte(Data);
    // receive_ack();
    // stop();

    I2C_GenerateSTART(I2C2, ENABLE);
    wait_event(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    wait_event(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, RegAddress);
    wait_event(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_SendData(I2C2, Data);
    wait_event(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050::read_reg(uint8_t RegAddress)
{
    uint8_t Data;

    // i2c.start();
    // i2c.send_byte(MPU6050_ADDRESS);
    // i2c.receive_ack();
    // i2c.send_byte(RegAddress);
    // i2c.receive_ack();

    // i2c.start();
    // i2c.send_byte(MPU6050_ADDRESS | 0x01);
    // i2c.receive_ack();
    // Data = i2c.receive_byte();
    // i2c.send_ack(1);
    // i2c.stop();

    I2C_GenerateSTART(I2C2, ENABLE);
    wait_event(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    wait_event(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, RegAddress);
    wait_event(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_GenerateSTART(I2C2, ENABLE);
    wait_event(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    wait_event(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);

    wait_event(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
    Data = I2C_ReceiveData(I2C2);

    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return Data;
}
