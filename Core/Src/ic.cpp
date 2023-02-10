#include "ic.hpp"

IC::IC()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, FunctionalState::ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, FunctionalState::ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // PA6
    GPIO_InitStructure.GPIO_Speed = GPIOSpeed_TypeDef::GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIOMode_TypeDef::GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM3);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_PWMIConfig(TIM3, &TIM_ICInitStructure); // add

    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3, FunctionalState::ENABLE);
}

uint32_t IC::get_freq()
{
    return 1000000 / (TIM_GetCapture1(TIM3) + 1);
}

uint32_t IC::get_duty()
{
    return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}
