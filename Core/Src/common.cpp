#include "common.hpp"

#include "core_cm3.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// int _write(int fd, char *pBuffer, int size)
// {
// 	for (int i = 0; i < size; i++)
// 	{
// 		ITM_SendChar(pBuffer[i]);
// 	}
// 	return size;
// }

int print_to_swo(const char *format, ...)
{
    va_list ap;
    char buff[100];
    va_start(ap, format);
    vsprintf(buff, format, ap);
    va_end(ap);

    for (size_t i = 0; i < strlen(buff); i++)
    {
        ITM_SendChar(buff[i]);
    }
    return strlen(buff);
}

void software_delay(u32 count)
{
    for (; count != 0; count--)
        ;
}

void delay_ms(u32 ms)
{
    SysTick_Config(SystemCoreClock / 1000); // set period of SysTick to 1ms ( (72M / 1000) / 72Mhz = 1ms)
    for (u32 i = 0; i < ms; i++)            // ms * 1ms = ms ms
    {
        while (!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG_Msk))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // disable SysTick
}

void delay_us(u32 us)
{
    SysTick_Config(SystemCoreClock / 1000000); // set period of SysTick to 1ms ( (72M / 1000000) / 72Mhz = 1us)
    for (u32 i = 0; i < us; i++)               // us * 1us = us us
    {
        while (!((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG_Msk))
            ;
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // disable SysTick
}
