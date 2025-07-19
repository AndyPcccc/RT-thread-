#ifndef APPLICATIONS_MOVEMENT_H_
#define APPLICATIONS_MOVEMENT_H_

#include "stm32f4xx_hal.h"

void vertical_up(uint16_t length);
void vertical_down(uint16_t length);
void level_forward(uint16_t length);
void level_back(uint16_t length);

void take1(void);
void Place1(void);
void Take2(void);
void Place2(void);

#endif
