#include "stm32f4xx.h"
#include "hcsr04.h"
#include "delay.h"

void HCSR04_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

		// 使能 GPIOF 时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    // 配置 Trig (PF3) 为输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    // 配置 Echo (PF2) 为输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}

uint32_t HCSR04_GetDistance(void) {
    uint32_t time = 0;
    float distance;
    uint32_t timeout;

    // 触发超声波
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    delay_us(10);
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);

    // 等待 Echo 高电平开始
    timeout = 10000;
    while (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) == 0 && timeout--) {
        delay_us(1);
    }
    if (timeout == 0) return 9999; // 超时返回一个较大值

    // 开始计时（高电平持续时间）
    time = 0;
    timeout = 30000;
    while (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) == 1 && timeout--) {
        time++;
        delay_us(1);
    }

    if (timeout == 0) return 9999; // 超时，返回最大距离

    distance = (time * 0.034) / 2.0f; // 单位：cm
    return (uint32_t)distance;
}
