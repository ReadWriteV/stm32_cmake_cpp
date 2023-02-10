#include "motor.hpp"

Motor::Motor()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, FunctionalState::ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, FunctionalState::ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // PA2
    GPIO_InitStructure.GPIO_Speed = GPIOSpeed_TypeDef::GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIOMode_TypeDef::GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;   // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; // CCR
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, FunctionalState::ENABLE);
}

void Motor::set_speed(int8_t speed)
{
    TIM_SetCompare3(TIM2, speed);
}
