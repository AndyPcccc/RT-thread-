#include "serial_comm_screen.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

#define SCREEN_UART_NAME "uart3"

rt_device_t screen_uart = RT_NULL;

// 初始化串口设备
void SCREEN_UART_Init(void)
{
    // 查找设备
    screen_uart = rt_device_find(SCREEN_UART_NAME);
    if (screen_uart == RT_NULL)
    {
        // 找不到设备
        return;
    }

    // 以读写方式打开串口（阻塞方式）
    rt_device_open(screen_uart, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
}

// 发送一个字符
void UART3_SendChar(char c)
{
    if (screen_uart)
        rt_device_write(screen_uart, 0, &c, 1);
}

// 发送字符串
void UART3_SendString(const char *str)
{
    if (screen_uart && str)
        rt_device_write(screen_uart, 0, str, rt_strlen(str));
}

// 发送 TJC 控件命令
void UART3_SendCommand(int index, char value)
{
    char buffer[50];
    rt_sprintf(buffer, "main.t%d.txt=\"%c\"", index, value);

    UART3_SendString(buffer);

    // 使用逐字节方式发结束符
    UART3_SendChar(0xFF);
    UART3_SendChar(0xFF);
    UART3_SendChar(0xFF);
}

// 发送单字节
void UART3_SendByte(uint8_t byte)
{
    if (screen_uart)
        rt_device_write(screen_uart, 0, &byte, 1);
}

// 阻塞接收一个字节
uint8_t UART3_ReceiveByte(void)
{
    uint8_t ch = 0;
    if (screen_uart)
        rt_device_read(screen_uart, 0, &ch, 1);
    return ch;
}
