#include <rtthread.h>
#include "stm32f4xx_hal.h"
#include "pwm.h"
#include "sensor.h"
#include "hcsr04.h"
#include "fmq.h"
#include "serial_comm_openmv.h"
#include "stepping.h"
#include "serial_comm_screen.h"
#include "serial_comm_voice.h"
#include "movement.h"

// 全局变量
uint8_t openmv_data = 0;
uint8_t counter = 0;
uint8_t return_phase = 0;
extern rt_device_t openmv_serial;

// 巡线调整逻辑
void Line_Tracking_Adjustment() {
    Update_Sensor_Values();
    if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
    sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 0) {
    Motor_SetSpeed(1, -950);
    Motor_SetSpeed(2, -5);
    Motor_SetSpeed(3, -950);
    Motor_SetSpeed(4, -5);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 0 && sensor8 == 1) {
    Motor_SetSpeed(1, -625);
    Motor_SetSpeed(2, -50);
    Motor_SetSpeed(3, -625);
    Motor_SetSpeed(4, -50);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 0 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -410);
    Motor_SetSpeed(2, -100);
    Motor_SetSpeed(3, -410);
    Motor_SetSpeed(4, -100);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && (sensor4 == 0 || sensor5 == 0) &&
         sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -200);
    Motor_SetSpeed(2, -200);
    Motor_SetSpeed(3, -200);
    Motor_SetSpeed(4, -200);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 0 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -100);
    Motor_SetSpeed(2, -410);
    Motor_SetSpeed(3, -100);
    Motor_SetSpeed(4, -410);
    }
    else if (sensor1 == 1 && sensor2 == 0 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -50);
    Motor_SetSpeed(2, -625);
    Motor_SetSpeed(3, -50);
    Motor_SetSpeed(4, -625);
    }
    else if (sensor1 == 0 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 0) {
    Motor_SetSpeed(1, -5);
    Motor_SetSpeed(2, -950);
    Motor_SetSpeed(3, -5);
    Motor_SetSpeed(4, -950);
    }
    else if (sensor1 == 0 && sensor2 == 0 && sensor3 == 0 && sensor4 == 0 &&
         sensor5 == 0 && sensor6 == 0 && sensor7 == 0 && sensor8 == 0) {
    Motor_SetSpeed(1, 0);
    Motor_SetSpeed(2, 0);
    Motor_SetSpeed(3, 0);
    Motor_SetSpeed(4, 0);

        counter++;

        Motor_SetSpeed(1, -200);
        Motor_SetSpeed(2, -200);
        Motor_SetSpeed(3, -200);
        Motor_SetSpeed(4, -200);
        rt_thread_mdelay(200);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -200);
    Motor_SetSpeed(2, -200);
    Motor_SetSpeed(3, -200);
    Motor_SetSpeed(4, -200);
    }

    // 连续两个传感器为 0 的特殊情况
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 0 && sensor8 == 0) {
    Motor_SetSpeed(1, -850);
    Motor_SetSpeed(2, -5);
    Motor_SetSpeed(3, -850);
    Motor_SetSpeed(4, -5);
    }
    else if (sensor1 == 1 && sensor2 == 0 && sensor3 == 0 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 0 && sensor7 == 0 && sensor8 == 1) {
    Motor_SetSpeed(1, -725);
    Motor_SetSpeed(2, -50);
    Motor_SetSpeed(3, -725);
    Motor_SetSpeed(4, -50);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 0 && sensor6 == 0 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -515);
    Motor_SetSpeed(2, -100);
    Motor_SetSpeed(3, -515);
    Motor_SetSpeed(4, -100);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 1 && sensor4 == 0 &&
         sensor5 == 0 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -200);
    Motor_SetSpeed(2, -200);
    Motor_SetSpeed(3, -200);
    Motor_SetSpeed(4, -200);
    }
    else if (sensor1 == 1 && sensor2 == 1 && sensor3 == 0 && sensor4 == 0 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -100);
    Motor_SetSpeed(2, -515);
    Motor_SetSpeed(3, -100);
    Motor_SetSpeed(4, -515);
    }
    else if (sensor1 == 1 && sensor2 == 0 && sensor3 == 0 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -50);
    Motor_SetSpeed(2, -725);
    Motor_SetSpeed(3, -50);
    Motor_SetSpeed(4, -725);
    }
    else if (sensor1 == 0 && sensor2 == 0 && sensor3 == 1 && sensor4 == 1 &&
         sensor5 == 1 && sensor6 == 1 && sensor7 == 1 && sensor8 == 1) {
    Motor_SetSpeed(1, -5);
    Motor_SetSpeed(2, -850);
    Motor_SetSpeed(3, -5);
    Motor_SetSpeed(4, -850);
    }
    else {
    Motor_SetSpeed(1, -200);
    Motor_SetSpeed(2, -200);
    Motor_SetSpeed(3, -200);
    Motor_SetSpeed(4, -200);
    }

}

// 小车启动与停止
void Start_to_Move(void)
{
    Motor_SetSpeed(1, -200);
    Motor_SetSpeed(2, -200);
    Motor_SetSpeed(3, -200);
    Motor_SetSpeed(4, -200);
    rt_thread_mdelay(350);
}

void Stop_Moving(void)
{
    Motor_SetSpeed(1, 0);
    Motor_SetSpeed(2, 0);
    Motor_SetSpeed(3, 0);
    Motor_SetSpeed(4, 0);
}

uint8_t Voice_WaitForNumber(void)
{
    uint16_t timeout = 100;  // 最多等待 5 秒（100 × 50ms）

    while (voice_wakeup_flag)
    {
        rt_thread_mdelay(50);  // RTT延时替代 delay_ms
        UART3_SendCommand(2, '0');  // 屏幕提示暂停/等待编号

        // 等待语音识别结果为 1~4，并且当前未在路线中
        if (!route_active_flag && voice_cmd >= '1' && voice_cmd <= '4')
        {
            override_data = voice_cmd - '0';
            openmv_data = override_data;

            voice_cmd = 0;
            voice_wakeup_flag = 0;

            UART3_SendCommand(2, '1');  // 屏幕提示恢复
            Voice_QuickBeep();          // 提示音确认
            UART3_SendCommand(1, openmv_data + '0');  // 显示编号
            return openmv_data;
        }

        // 超时自动退出等待
        if (timeout != 0xFFFF && timeout-- == 0)
        {
            voice_wakeup_flag = 0;
            UART3_SendCommand(2, '1');
            Voice_QuickBeep();
            break;
        }
    }

    voice_cmd = 0;
    return 0;
}

// 获取目标编号（语音或视觉）
uint8_t Get_Target_Number(void)
{
    uint16_t timeout = 80;  // 4秒窗口（80 × 50ms）

    while (timeout--)
    {
        rt_thread_mdelay(50);

        if (override_data >= 1 && override_data <= 4)
        {
            openmv_data = override_data;
            UART3_SendCommand(1, openmv_data + '0');
            return openmv_data;
        }

        if (voice_wakeup_flag)
        {
            return Voice_WaitForNumber();
        }
    }

    // ===== 视觉识别阶段（仅执行一次机械臂动作）=====
    vertical_up(18);
    rt_thread_mdelay(4000);  // 机械臂抬升完成

    USART2_ClearBuffer();  // 使用 RTT 的清空函数

    // 等待识别
    while (1)
    {
        uint8_t ch = 0;
        if (openmv_serial && rt_device_read(openmv_serial, 0, &ch, 1) == 1)
        {
            if (ch >= '1' && ch <= '4')
            {
                openmv_data = ch - '0';
                break;
            }
        }

        rt_thread_mdelay(50);
    }

    UART3_SendCommand(1, openmv_data + '0');
    vertical_down(17);
    rt_thread_mdelay(1000);

    return openmv_data;
}

// 判断执行语音控制（取货）或视觉控制（放货）
void Execute_Action(void)
{
    if (override_data >= 1 && override_data <= 4)
    {
        UART3_SendCommand(0, '3');
        Take2();
    }
    else if (openmv_data >= 1 && openmv_data <= 4)
    {
        UART3_SendCommand(0, '4');
        Place2();
    }
}

// 主线程入口
static void main_thread_entry(void *parameter)
{
    int32_t distance;

    // 初始化外设
    HAL_Init();
    USART2_Init();
    SCREEN_UART_Init();
    VOICE_UART5_Init();
    TrackSensor_GPIO_Init();
    Motor_GPIO_Config();
    PWM_Config();
    STBY_GPIO_Config();
    DIR_Init();
    ENA_Init();
    TIM3_PWM_Init(100, 500);
    HCSR04_Init();
    Buzzer_Init();
    Disable_All_Motors();

    while (1)
    {
        // 状态初始化
        openmv_data = 0;
        counter = 0;
        return_phase = 0;
        override_data = 0;
        voice_cmd = 0;
        voice_wakeup_flag = 0;
        route_active_flag = 0;

        rt_thread_mdelay(3000);

        Buzzer_On();
        rt_thread_mdelay(200);
        Buzzer_Off();
        UART3_SendCommand(0, '1');
        UART3_SendCommand(2, '1');

        rt_thread_mdelay(3000);

        openmv_data = Get_Target_Number();

        Buzzer_On();
        rt_thread_mdelay(200);
        Buzzer_Off();

        // 出发阶段
        if (openmv_data >= 1 && openmv_data <= 4)
        {
            route_active_flag = 1;
            UART3_SendCommand(0, '2');
            Start_to_Move();

            while (counter < openmv_data)
            {
                if (voice_wakeup_flag)
                    Wait_For_Resume();

                distance = HCSR04_GetDistance();

                if (distance < 5 && distance > 1)
                {
                    Stop_Moving();
                    Buzzer_On(); rt_thread_mdelay(300);
                    UART3_SendCommand(2, '0');
                }
                else
                {
                    Buzzer_Off();
                    UART3_SendCommand(2, '1');
                    Line_Tracking_Adjustment();
                }

                rt_thread_mdelay(50);
            }

            Stop_Moving();
            rt_thread_mdelay(1000);

            Execute_Action();
            rt_thread_mdelay(2000);

            // 返回阶段
            return_phase = 1;
            UART3_SendCommand(0, '5');
            Start_to_Move();

            while (counter < 5)
            {
                if (voice_wakeup_flag)
                {
                    Stop_Moving();
                    Wait_For_Resume();
                }

                distance = HCSR04_GetDistance();

                if (distance < 5 && distance > 1)
                {
                    Stop_Moving();
                    Buzzer_On(); rt_thread_mdelay(300);
                    UART3_SendCommand(2, '0');
                }
                else
                {
                    Buzzer_Off();
                    UART3_SendCommand(2, '1');
                    Line_Tracking_Adjustment();
                }

                rt_thread_mdelay(50);
            }

            Stop_Moving();
        }

        Voice_ResetState();
    }
}

// RT-Thread 自动调用主函数
int main(void)
{
    rt_thread_t tid = rt_thread_create("main_thread",
                                       main_thread_entry,
                                       RT_NULL,
                                       4096, 20, 10);
    if (tid)
        rt_thread_startup(tid);
    return 0;
}
