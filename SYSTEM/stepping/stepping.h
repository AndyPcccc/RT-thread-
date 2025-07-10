#ifndef __STEPPING_H
#define __STEPPING_H

#include "stm32f4xx.h"

void DIR_Init(void);
void ENA_Init(void);
void TIM3_PWM_Init(uint16_t arr, uint16_t psc);

void Enable_Motor1_Only(void); 
void Enable_Motor2_Only(void); 
void Disable_All_Motors(void);          

#endif
