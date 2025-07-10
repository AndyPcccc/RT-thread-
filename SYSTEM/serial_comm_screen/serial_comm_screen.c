#include "stm32f4xx.h"
#include "serial_comm_screen.h"
#include <stdio.h>
#include <string.h>


void SCREEN_UART_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE);
}


void UART3_SendChar(char c) {
    while (!(USART3->SR & USART_SR_TXE)); 
    USART3->DR = c; 
}


void UART3_SendString(const char *str) {
    while (*str) { 
        UART3_SendChar(*str++); 
    }
}


void UART3_SendCommand(int index, char value) {
    char buffer[50]; 
    snprintf(buffer, sizeof(buffer), "main.t%d.txt=\"%c\"", index, value); 
    UART3_SendString(buffer); // 发送格式化后的字符串
    UART3_SendChar(0xFF); // 发送结束符 (0xFF)
    UART3_SendChar(0xFF); // 发送结束符 (0xFF)
    UART3_SendChar(0xFF); // 发送结束符 (0xFF)
}
void UART3_SendByte(uint8_t byte) {
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, byte);
}

uint8_t UART3_ReceiveByte(void) {
    while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
    return (uint8_t)USART_ReceiveData(USART3);
}
