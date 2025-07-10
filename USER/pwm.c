#include "stm32f4xx.h"
#include "pwm.h"
#include "delay.h" // void delay_ms(u16 nms);

extern const int PWM_FREQUENCY;

// ************** ���õ��������� GPIO **************
void Motor_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ�� GPIO ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB, ENABLE);

    // ���õ�������������
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // ��� 1��2 ����������� (PE9, PE12, PE11, PE13)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_13;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // ��� 3��4 ����������� (PB6, PB3, PB5, PB11)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_11;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// ************** ���� PWM **************
void PWM_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    TIM_OCInitTypeDef TIM_OCStruct;

    // �ر� USART3 ���� PB10 ��ռ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, DISABLE);

    // ʹ�ܶ�ʱ���� GPIO ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

    // ���� GPIO Ϊ��������
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    // PA8 (TIM1_CH1) �� PA1 (TIM2_CH2)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1); // ���2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2); // ���1

    // PB10 (TIM2_CH3) - ���3
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);

    // PB7 (TIM4_CH2) - ���4
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);

    // ��ʱ�����ã�20kHz��
    TIM_BaseStruct.TIM_Period = 999;
    TIM_BaseStruct.TIM_Prescaler = 84 - 1;
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1, &TIM_BaseStruct);
    TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
    TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);

    // PWM �������
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_Pulse = 500;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCStruct); // ���2
    TIM_OC2Init(TIM2, &TIM_OCStruct); // ���1
    TIM_OC3Init(TIM2, &TIM_OCStruct); // ���3
    TIM_OC2Init(TIM4, &TIM_OCStruct); // ���4

    // Ԥװ��
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // ������ʱ��
    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    // �߼���ʱ�����ʹ��
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

// ************** ���õ���ٶ� **************
void Motor_SetSpeed(int motor, int speed)
{
    uint16_t pwm_val = (speed > 0) ? speed : -speed;
    BitAction direction = (speed > 0) ? Bit_SET : Bit_RESET;

    switch (motor)
    {
    case 1:
        GPIO_WriteBit(GPIOE, GPIO_Pin_9, direction);
        GPIO_WriteBit(GPIOE, GPIO_Pin_13, (BitAction)(!direction));
        TIM_SetCompare2(TIM2, pwm_val); // PA1
        break;
    case 2:
        GPIO_WriteBit(GPIOE, GPIO_Pin_12, direction);
        GPIO_WriteBit(GPIOE, GPIO_Pin_11, (BitAction)(!direction));
        TIM_SetCompare1(TIM1, pwm_val); // PA8
        break;
    case 3:
        GPIO_WriteBit(GPIOB, GPIO_Pin_6, direction);
        GPIO_WriteBit(GPIOB, GPIO_Pin_3, (BitAction)(!direction));
        TIM_SetCompare3(TIM2, pwm_val); // PB10
        break;
    case 4:
        GPIO_WriteBit(GPIOB, GPIO_Pin_5, direction);
        GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)(!direction));
        TIM_SetCompare2(TIM4, pwm_val); // PB7
        break;
    }
}

// ************** ���� STBY��ʹ�����ţ� **************
void STBY_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
    GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_SetBits(GPIOF, GPIO_Pin_5); // STBY = 1
}
