#include "stm32f4xx.h"
#include "ADC.h"

void ADC_Config(void) {
    ADC_InitTypeDef ADC_InitStruct;
    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 1. ʹ��ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* 2. ���� PA5 �� PA4 Ϊģ������ģʽ */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* 3. ���� ADC ͨ�ò��� */
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;  // ��Ƶ���ӣ�ADCʱ�� = PCLK2 / 4
    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStruct);

    /* 4. ���� ADC1 */
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;  // 12λ�ֱ���
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;  // ʹ��ɨ��ģʽ
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;  // ʹ������ת��ģʽ
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;  // ����Դ�����Ը�Ϊ���������
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  // ���ⲿ����
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;  // �����Ҷ���
    ADC_InitStruct.ADC_NbrOfConversion = 2;  // ������ת��2��ͨ��
    ADC_Init(ADC1, &ADC_InitStruct);

    /* 5. ���� ADC ͨ�� */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_144Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_144Cycles);

    /* 6. ʹ�� ADC1 */
    ADC_Cmd(ADC1, ENABLE);
}

uint16_t ADC_Read(void) {
    /* ���� ADC ת�� */
    ADC_SoftwareStartConv(ADC1);
    
    /* �ȴ�ת����� */
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    
    /* ��ȡת����� */
    return ADC_GetConversionValue(ADC1);
}
