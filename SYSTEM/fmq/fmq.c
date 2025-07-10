#include "stm32f4xx.h"
#include "fmq.h"

void Buzzer_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // ʹ�� GPIOB ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    // ���� PB4 Ϊ�������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Ĭ�Ϲرշ�����
    GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

void Buzzer_On(void) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_4); // �򿪷�����
}

void Buzzer_Off(void) {
    GPIO_SetBits(GPIOB, GPIO_Pin_4); // �رշ�����
}
