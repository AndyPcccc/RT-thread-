#ifndef APPLICATIONS_HCSR04_H_
#define APPLICATIONS_HCSR04_H_

#include "stm32f4xx_hal.h"

void HCSR04_Init(void);
uint32_t HCSR04_GetDistance(void);

#endif
