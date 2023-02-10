#include "stm32f10x.h"
#include "common.hpp"
#include "oled.hpp"

#include "mpu6050.hpp"

int main()
{
    OLED oled;

    MPU6050 m;
    uint8_t id = m.get_id();

    oled.show(1, 1, "id:");
    oled.show(1, 8 * 3 + 1, id, 4);

    int16_t AX = 0, AY = 0, AZ = 0, GX = 0, GY = 0, GZ = 0;

    while (true)
    {
        m.get_data(&AX, &AY, &AZ, &GX, &GY, &GZ);
        oled.show(3, 1, AX, 4);
        oled.show(3, 8 * 5 + 1, AY, 4);
        oled.show(3, 8 * 10 + 1, AZ, 4);
        oled.show(5, 1, GX, 4);
        oled.show(5, 8 * 5 + 1, GY, 4);
        oled.show(5, 8 * 10 + 1, GZ, 4);
    }

    return 0;
}