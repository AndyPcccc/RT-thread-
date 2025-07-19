#include <rtthread.h>
#include <rtdevice.h>
#include "serial_comm_openmv.h"

#define OPENMV_UART_NAME "uart2"

rt_device_t openmv_serial = RT_NULL;

// 初始化串口设备
void USART2_Init(void)
{
    openmv_serial = rt_device_find(OPENMV_UART_NAME);
    if (openmv_serial == RT_NULL)
    {
        return;
    }

    rt_device_open(openmv_serial, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
}

// 阻塞式发送一个字节
void USART2_SendData(uint8_t data)
{
    rt_device_write(openmv_serial, 0, &data, 1);
}

// 阻塞式接收一个字节
uint8_t USART2_ReceiveData(void)
{
    uint8_t ch = 0;
    while (rt_device_read(openmv_serial, 0, &ch, 1) == 0)
    {
        rt_thread_mdelay(10);
    }
    return ch;
}

// 清空 openmv 串口接收缓冲区（uart2）
void USART2_ClearBuffer(void)
{
    uint8_t ch;
    while (rt_device_read(openmv_serial, 0, &ch, 1) == 1)
    {
        // 丢弃 ch，直到无新数据可读
    }
}
