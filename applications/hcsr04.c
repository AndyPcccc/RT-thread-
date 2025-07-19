#include "stm32f4xx_hal.h"
#include "hcsr04.h"
#include <rtthread.h>
#include <rthw.h>

// 初始化 Trig（PF3）和 Echo（PF2）
void HCSR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOF_CLK_ENABLE();

    // 配置 Trig（PF3）为输出
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // 配置 Echo（PF2）为输入
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

// 获取距离（单位：cm）
uint32_t HCSR04_GetDistance(void)
{
    uint32_t time = 0;
    uint32_t timeout = 0;
    float distance;

    // 发送 10us 脉冲
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
    rt_hw_us_delay(10);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);

    // 等待 Echo 拉高
    timeout = 10000;
    while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2) == GPIO_PIN_RESET && timeout--)
    {
        rt_hw_us_delay(1);
    }
    if (timeout == 0)
        return 9999;

    // 计时高电平持续时间
    timeout = 30000;
    while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2) == GPIO_PIN_SET && timeout--)
    {
        time++;
        rt_hw_us_delay(1);
    }
    if (timeout == 0)
        return 9999;

    // 计算距离（音速约 0.034cm/us）
    distance = (time * 0.034f) / 2.0f;
    return (uint32_t)distance;
}
