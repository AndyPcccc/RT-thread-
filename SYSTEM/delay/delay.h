#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

// ��ʼ����ʱ����
void delay_init(void);

// ΢�뼶��ʱ
void delay_us(uint32_t nus);

// ���뼶��ʱ
void delay_ms(uint32_t nms);

#endif


























