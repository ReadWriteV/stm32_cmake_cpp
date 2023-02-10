#include "count_sensor.hpp"

CountSensor::CountSensor(uint32_t clock, GPIO_TypeDef *port, uint16_t pin) : port(port), pin(pin), count(0)
{
    RCC_APB2PeriphClockCmd(clock, FunctionalState::ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, FunctionalState::ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Speed = GPIOSpeed_TypeDef::GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIOMode_TypeDef::GPIO_Mode_IPU;
    GPIO_Init(port, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_LineCmd = FunctionalState::ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTIMode_TypeDef::EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTITrigger_TypeDef::EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = IRQn_Type::EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = FunctionalState::ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStructure);
}

void CountSensor::handle()
{
    count++;
}

uint16_t CountSensor::get_count()
{
    return count;
}
