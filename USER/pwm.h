#ifndef __PWM_H
#define __PWM_H 
#include "stm32f4xx.h"
#include "delay.h"//void delay_ms(u16 nms);
extern const int PWM_FREQUENCY;
void Motor_GPIO_Config(void);
void PWM_Config(void);
void Motor_SetSpeed(int motor, int speed);
void STBY_GPIO_Config(void);
#endif
