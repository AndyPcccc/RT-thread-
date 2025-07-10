#ifndef __SERIAL_COMM_OPENMV_H
#define __SERIAL_COMM_OPENMV_H

#include "stm32f4xx.h"

void USART2_Init(void);
void USART2_SendData(uint8_t data);
uint8_t USART2_ReceiveData(void);

#endif
