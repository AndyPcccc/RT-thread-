#ifndef APPLICATIONS_PWM_H_
#define APPLICATIONS_PWM_H_

#include "stm32f4xx_hal.h"

extern const int PWM_FREQUENCY;
void Motor_GPIO_Config(void);
void PWM_Config(void);
void Motor_SetSpeed(int motor, int speed);
void STBY_GPIO_Config(void);

#endif
