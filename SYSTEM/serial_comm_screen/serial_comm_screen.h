#ifndef __SERIAL_COMM_SCREEN_H
#define __SERIAL_COMM_SCREEN_H

#include "stm32f4xx.h"

// ��ʼ�� UART3��PD8/PD9���������ʹ̶�Ϊ 115200
void SCREEN_UART_Init(void);

// ����/����
void UART3_SendByte(uint8_t byte);
uint8_t UART3_ReceiveByte(void);
void UART3_SendChar(char c);
void UART3_SendString(const char *str);
void UART3_SendCommand(int index, char value);
#endif
