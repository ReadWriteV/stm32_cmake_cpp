#include "stm32f10x.h"
#include "common.hpp"

#include "oled.hpp"

int main()
{
    OLED oled;

    oled.show(1, 1, "hello world!");

    while (true)
    {
    }

    return 0;
}
