#include "adc.hpp"

ADC::ADC()
{
    RCC_APB2PeriphClockCmd(adc_clock, FunctionalState::ENABLE);
    RCC_APB2PeriphClockCmd(adc_gpio_clock, FunctionalState::ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = adc_gpio_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(adc_gpio_port, &GPIO_InitStructure);

    ADC_RegularChannelConfig(adc, adc_channel, 1, ADC_SampleTime_55Cycles5);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_ContinuousConvMode = FunctionalState::DISABLE;
    ADC_InitStructure.ADC_ScanConvMode = FunctionalState::DISABLE;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(adc, &ADC_InitStructure);

    ADC_Cmd(adc, FunctionalState::ENABLE);

    ADC_ResetCalibration(adc);
    while (ADC_GetResetCalibrationStatus(adc) == SET)
        ;
    ADC_StartCalibration(adc);
    while (ADC_GetCalibrationStatus(adc) == SET)
        ;
}

uint16_t ADC::get_value()
{
    ADC_SoftwareStartConvCmd(adc, FunctionalState::ENABLE);
    while (ADC_GetFlagStatus(adc, ADC_FLAG_EOC) == RESET)
        ;
    return ADC_GetConversionValue(adc);
}
