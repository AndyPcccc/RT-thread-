#ifndef __SERIAL_COMM_SCREEN_H
#define __SERIAL_COMM_SCREEN_H

#include <stdint.h>

void SCREEN_UART_Init(void);
void UART3_SendChar(char c);
void UART3_SendString(const char *str);
void UART3_SendCommand(int index, char value);
void UART3_SendByte(uint8_t byte);
uint8_t UART3_ReceiveByte(void);

#endif
