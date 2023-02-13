#ifndef __DMA_H
#define __DMA_H

#include "stm32f10x.h"

class DMA
{
public:
    DMA(uint32_t addr_a, uint32_t addr_b, uint16_t size);

    void transfer();

private:
    uint16_t size;
};

#endif
