#include "movement.h"
#include "stm32f4xx_hal.h"
#include "stepping.h"
#include <rtthread.h>

uint16_t floor1 = 1;
uint16_t floor2 = 11;
uint16_t forward = 4;
uint16_t back = 4;
uint16_t up = 7;
uint16_t down = 4;

// 上升动作
void vertical_up(uint16_t length)
{
    uint32_t steps = length * 600 * 200 / 360;
    uint32_t time = steps * 1000 / 1660;
    Enable_Motor1_Only();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); // ENA1 低使能
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);  // DIR1 向上

    rt_thread_mdelay(time);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);   // 禁用
}

// 下降动作
void vertical_down(uint16_t length)
{
    uint32_t steps = length * 600 * 200 / 360;
    uint32_t time = steps * 1000 / 1660;
    Enable_Motor1_Only();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); // ENA1
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET); // DIR1 向下

    rt_thread_mdelay(time);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // 禁用
}

// 后退动作（水平前进）
void level_back(uint16_t length)
{
    uint32_t steps = length * 1600 / 4;
    uint32_t time = steps * 1000 / 1660;
    Enable_Motor2_Only();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); // ENA2
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);  // DIR2 向前

    rt_thread_mdelay(time);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);   // 禁用
}

// 前进动作（水平后退）
void level_forward(uint16_t length)
{
    uint32_t steps = length * 1600 / 4;
    uint32_t time = steps * 1000 / 1660;
    Enable_Motor2_Only();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); // ENA2
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET); // DIR2 向后

    rt_thread_mdelay(time);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // 禁用
}

// 第一层取货动作
void take1(void)
{
    vertical_up(floor1);
    level_forward(forward);
    vertical_up(up);
    level_back(back);
    vertical_down(floor1 + up);
}

// 第一层放货动作
void Place1(void)
{
    vertical_up(floor1 + up);
    level_forward(forward);
    vertical_down(down);
    level_back(back);
    vertical_down(floor1 + up - down);
}

// 第二层取货动作
void Take2(void)
{
    vertical_up(floor2 + 5);
    level_forward(forward);
    vertical_up(up - 2);
    level_back(back);
    vertical_down(floor2 + up - 2 + 5 - 1);
}

// 第二层放货动作
void Place2(void)
{
    vertical_up(floor2 + up);
    level_forward(forward);
    vertical_down(down);
    level_back(back);
    vertical_down(floor2 + up - down - 1);
}
