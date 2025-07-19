#ifndef APPLICATIONS_STEPPING_H_
#define APPLICATIONS_STEPPING_H_

#include "stm32f4xx_hal.h"

void DIR_Init(void);
void ENA_Init(void);
void TIM3_PWM_Init(uint16_t arr, uint16_t psc);

void Enable_Motor1_Only(void);
void Enable_Motor2_Only(void);
void Disable_All_Motors(void);

#endif
