#include "movement.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "stepping.h"

uint16_t floor1 = 1;
uint16_t floor2 = 16-5;
uint16_t forward = 12-5-1;
uint16_t back = 12-5-1;
uint16_t up = 3 + 4 ;
uint16_t down = 3+2;

void vertical_up(uint16_t length) {
    uint32_t steps = length * 600 * 200 / 360;
    uint32_t time = steps * 1000 / 1660;
		Enable_Motor1_Only();
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);   // ENA1
    GPIO_SetBits(GPIOC, GPIO_Pin_10);    // DIR1 向上
    delay_ms(time);
    GPIO_SetBits(GPIOC, GPIO_Pin_9);
}

void vertical_down(uint16_t length) {
    uint32_t steps = length * 600 * 200 / 360;
    uint32_t time = steps * 1000 / 1660;
		Enable_Motor1_Only();
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);   // ENA1
    GPIO_ResetBits(GPIOC, GPIO_Pin_10);  // DIR1 向下
    delay_ms(time);
    GPIO_SetBits(GPIOC, GPIO_Pin_9);
}

void level_back(uint16_t length) {
    uint32_t steps = length * 1600 / 4;
    uint32_t time = steps * 1000 / 1660;
		Enable_Motor2_Only();
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);   // ENA2
    GPIO_SetBits(GPIOC, GPIO_Pin_11);    // DIR2 向前
    delay_ms(time);
    GPIO_SetBits(GPIOC, GPIO_Pin_6);
}

void level_forward(uint16_t length) {
    uint32_t steps = length * 1600 / 4;
    uint32_t time = steps * 1000 / 1660;
		Enable_Motor2_Only();
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);   // ENA2
    GPIO_ResetBits(GPIOC, GPIO_Pin_11);  // DIR2 向后
    delay_ms(time);
    GPIO_SetBits(GPIOC, GPIO_Pin_6);
}

void take1(void) {
    vertical_up(floor1);
    level_forward(forward);
    vertical_up(up);
    level_back(back);
    vertical_down(floor1 + up);
}

void Place1(void) {
    vertical_up(floor1 + up);
    level_forward(forward);
    vertical_down(down);
    level_back(back);
    vertical_down(floor1 + up - down);
}

void Take2(void) {
    vertical_up(floor2);
    level_forward(forward);
    vertical_up(up);
    level_back(back);
    vertical_down(floor2 + up);
}

void Place2(void) {
    vertical_up(floor2 + up);
    level_forward(forward);
    vertical_down(down);
    level_back(back);
    vertical_down(floor2 + up - down-1);
}
