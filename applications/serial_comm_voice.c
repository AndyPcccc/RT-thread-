#include "serial_comm_voice.h"
#include "fmq.h"
#include "pwm.h"
#include "serial_comm_screen.h"
#include <rtdevice.h>
#include <rtthread.h>

rt_device_t voice_uart = RT_NULL;

volatile uint8_t voice_cmd = 0;
volatile uint8_t voice_wakeup_flag = 0;
volatile uint8_t override_data = 0;
volatile uint8_t route_active_flag = 0;

// 中断接收回调函数
static rt_err_t voice_rx_callback(rt_device_t dev, rt_size_t size)
{
    uint8_t ch;
    rt_device_read(dev, 0, &ch, 1);
    voice_cmd = ch;

    if (ch == '8')
    {
        voice_wakeup_flag = 1;
        Motor_SetSpeed(1, 0); Motor_SetSpeed(2, 0);
        Motor_SetSpeed(3, 0); Motor_SetSpeed(4, 0);
        Voice_QuickBeep();
    }
    else if (ch == '9')
    {
        voice_wakeup_flag = 0;
        Voice_QuickBeep();
    }
    else if (!route_active_flag && ch >= '1' && ch <= '4')
    {
        override_data = ch - '0';
    }

    return RT_EOK;
}

// 初始化语音串口（使用 UART5）
void VOICE_UART5_Init(void)
{
    voice_uart = rt_device_find("uart5");
    if (voice_uart == RT_NULL)
    {
        return;
    }

    rt_device_open(voice_uart, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(voice_uart, voice_rx_callback);
}

// 快速蜂鸣器提示
void Voice_QuickBeep(void)
{
    Buzzer_On();  rt_thread_mdelay(100);
    Buzzer_Off(); rt_thread_mdelay(100);
    Buzzer_On();  rt_thread_mdelay(100);
    Buzzer_Off();
}

// 等待语音“继续”或超时
void Wait_For_Resume(void)
{
    uint16_t timeout = 100;

    while (voice_wakeup_flag)
    {
        rt_thread_mdelay(50);
        UART3_SendCommand(2, '0');

        if (voice_cmd == '9')
        {
            voice_wakeup_flag = 0;
            voice_cmd = 0;
            UART3_SendCommand(2, '1');
            Voice_QuickBeep();
            Motor_SetSpeed(1, -150); Motor_SetSpeed(2, -5);
            Motor_SetSpeed(3, -150); Motor_SetSpeed(4, -5);
            break;
        }
        else if (voice_cmd == '0')
        {
            timeout = 0xFFFF;
        }

        if (timeout != 0xFFFF && timeout-- == 0)
        {
            voice_wakeup_flag = 0;
            UART3_SendCommand(2, '1');
            Voice_QuickBeep();
            Motor_SetSpeed(1, -150); Motor_SetSpeed(2, -5);
            Motor_SetSpeed(3, -150); Motor_SetSpeed(4, -5);
            break;
        }
    }

    voice_cmd = 0;
}

// 主循环中处理暂停
void Voice_Check_MainLoop(void)
{
    if (voice_wakeup_flag)
    {
        Motor_SetSpeed(1, 0); Motor_SetSpeed(2, 0);
        Motor_SetSpeed(3, 0); Motor_SetSpeed(4, 0);
        UART3_SendCommand(2, '0');
    }
}

// 状态复位
void Voice_ResetState(void)
{
    voice_cmd = 0;
    override_data = 0;
    voice_wakeup_flag = 0;
    route_active_flag = 0;
}
