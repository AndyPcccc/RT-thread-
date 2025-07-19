#ifndef __SERIAL_COMM_OPENMV_H__
#define __SERIAL_COMM_OPENMV_H__

#include <rtdevice.h>
#include <stdint.h>

extern rt_device_t openmv_serial;

void USART2_Init(void);
void USART2_SendData(uint8_t data);
uint8_t USART2_ReceiveData(void);
void USART2_ClearBuffer(void);

#endif
