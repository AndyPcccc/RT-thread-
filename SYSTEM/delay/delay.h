#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

// 初始化延时功能
void delay_init(void);

// 微秒级延时
void delay_us(uint32_t nus);

// 毫秒级延时
void delay_ms(uint32_t nms);

#endif


























