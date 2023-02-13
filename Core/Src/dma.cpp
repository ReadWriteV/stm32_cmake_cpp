#include "dma.hpp"

DMA::DMA(uint32_t addr_a, uint32_t addr_b, uint16_t size) : size(size)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, FunctionalState::ENABLE);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = addr_a;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryBaseAddr = addr_b;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = size;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, FunctionalState::DISABLE);
}

void DMA::transfer()
{
    DMA_Cmd(DMA1_Channel1, FunctionalState::DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, size);
    DMA_Cmd(DMA1_Channel1, FunctionalState::ENABLE);

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == FlagStatus::RESET)
        ;
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
