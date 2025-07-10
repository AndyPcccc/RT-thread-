#include "stm32f4xx.h"
#include "ADC.h"

void ADC_Config(void) {
    ADC_InitTypeDef ADC_InitStruct;
    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 1. 使能时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* 2. 配置 PA5 和 PA4 为模拟输入模式 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* 3. 配置 ADC 通用部分 */
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;  // 分频因子，ADC时钟 = PCLK2 / 4
    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStruct);

    /* 4. 配置 ADC1 */
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;  // 12位分辨率
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;  // 使能扫描模式
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;  // 使能连续转换模式
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;  // 触发源（可以改为软件触发）
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  // 无外部触发
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;  // 数据右对齐
    ADC_InitStruct.ADC_NbrOfConversion = 2;  // 规则组转换2个通道
    ADC_Init(ADC1, &ADC_InitStruct);

    /* 5. 配置 ADC 通道 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_144Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_144Cycles);

    /* 6. 使能 ADC1 */
    ADC_Cmd(ADC1, ENABLE);
}

uint16_t ADC_Read(void) {
    /* 启动 ADC 转换 */
    ADC_SoftwareStartConv(ADC1);
    
    /* 等待转换完成 */
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    
    /* 读取转换结果 */
    return ADC_GetConversionValue(ADC1);
}
