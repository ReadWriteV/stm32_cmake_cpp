#ifndef __COMMON_H
#define __COMMON_H

#include "stm32f10x.h"

/// @brief Print formated string to SWO, display in ST-LINK Utility SWO Viewer.
/// @param format specifies the format for string.
/// @param ... list of args.
/// @return None
int print_to_swo(const char *format, ...);

/// @brief Use software-style to delay.
/// @param count time to delay.
void software_delay(u32 count);

/// @brief Use hardware-style to delay.
/// @param ms ms ms to delay.
void delay_ms(u32 ms);

/// @brief Use hardware-style to delay.
/// @param us us us to delay.
void delay_us(u32 us);

#endif