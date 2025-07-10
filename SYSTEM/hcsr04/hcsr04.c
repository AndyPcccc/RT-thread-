#include "stm32f4xx.h"
#include "hcsr04.h"
#include "delay.h"

void HCSR04_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

		// ʹ�� GPIOF ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    // ���� Trig (PF3) Ϊ���
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    // ���� Echo (PF2) Ϊ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}

uint32_t HCSR04_GetDistance(void) {
    uint32_t time = 0;
    float distance;
    uint32_t timeout;

    // ����������
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    delay_us(10);
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);

    // �ȴ� Echo �ߵ�ƽ��ʼ
    timeout = 10000;
    while (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) == 0 && timeout--) {
        delay_us(1);
    }
    if (timeout == 0) return 9999; // ��ʱ����һ���ϴ�ֵ

    // ��ʼ��ʱ���ߵ�ƽ����ʱ�䣩
    time = 0;
    timeout = 30000;
    while (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) == 1 && timeout--) {
        time++;
        delay_us(1);
    }

    if (timeout == 0) return 9999; // ��ʱ������������

    distance = (time * 0.034) / 2.0f; // ��λ��cm
    return (uint32_t)distance;
}
