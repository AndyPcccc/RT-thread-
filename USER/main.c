#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"
#include "sensor.h"
#include "hcsr04.h"
#include "fmq.h"
#include "serial_comm_openmv.h"
#include "stepping.h"  
#include "serial_comm_screen.h"
#include "serial_comm_voice.h"
#include "movement.h"
#include "ADC.h"

const int PWM_FREQUENCY = 20000;  // 20kHz PWM 频率

uint8_t openmv_data = 0;
uint8_t counter = 0;
uint8_t return_phase = 0;


// 巡线调整
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
        delay_ms(200);
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


// 让小车启动
void Start_to_Move() {
    Motor_SetSpeed(1, -200);
    Motor_SetSpeed(2, -200); 
    Motor_SetSpeed(3, -200); 
    Motor_SetSpeed(4, -200);
    delay_ms(350); 
}

// 让小车停止
void Stop_Moving() {
    Motor_SetSpeed(1, 0);
    Motor_SetSpeed(2, 0);
    Motor_SetSpeed(3, 0);
    Motor_SetSpeed(4, 0);
}

uint8_t Get_Target_Number(void) {
    if (override_data >= 1 && override_data <= 4) {
        return override_data;
    }

    while (1) {
        if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET) {
            char ch = USART2_ReceiveData();
            if (ch >= '1' && ch <= '4') {
                return ch - '0';
            }
        }

        if (voice_wakeup_flag) {
            Voice_QuickBeep();
            return 0;
        }
    }
}




// 判断执行语音控制（取货）或视觉控制（放货）
void Execute_Action(void) {
    if (override_data >= 1 && override_data <= 4) {
        UART3_SendCommand(0, '3'); 
				Take2();
    } else if (openmv_data >= 1 && openmv_data <= 4) {
        UART3_SendCommand(0, '4'); 
				Place2();
    }
}

int main(void) {
			int32_t distance;
			
			USART2_Init();
			TrackSensor_GPIO_Init();
			Motor_GPIO_Config();
			PWM_Config();
			STBY_GPIO_Config();
			delay_init();
			HCSR04_Init();
			Buzzer_Init();
			DIR_Init();                      
			ENA_Init();                       
			TIM3_PWM_Init(100, 500);        
			USART2_Init();
			SCREEN_UART_Init();  
			VOICE_UART5_Init();   
			ADC_Config();
			Disable_All_Motors();
			
				while(1){
        // 变量初始化
        openmv_data = 0;
        counter = 0;
				override_data = 0;
        return_phase = 0;
        route_active_flag = 0;
				voice_cmd = 0;
        voice_wakeup_flag = 0;
					
        delay_ms(3000);
				
				Buzzer_On();
				delay_ms(200);
				Buzzer_Off();
				UART3_SendCommand(0, '1');
				UART3_SendCommand(2, '1');
				
				delay_ms(3000);
									
				vertical_up(16);
				delay_ms(2000);
				
				openmv_data = Get_Target_Number();

				UART3_SendCommand(1, openmv_data + '0');    

				vertical_down(15);
				delay_ms(1000);
				
				Buzzer_On();
				delay_ms(200);
				Buzzer_Off();
        
				//进入运动过程
        if (openmv_data >= 1 && openmv_data <= 4) {
            route_active_flag = 1;
						
					//出发过程
						UART3_SendCommand(0, '2');
            Start_to_Move();

							while (counter < openmv_data) {

									if (voice_wakeup_flag) {
											Wait_For_Resume();  // 若唤醒则等待处理
									}

									distance = HCSR04_GetDistance(); 

									if (distance < 5 ) {
											Stop_Moving();
										  Buzzer_On();
										  delay_ms(300);
											UART3_SendCommand(2, '0'); 
									} else {
											Buzzer_Off();
											UART3_SendCommand(2, '1'); 
											Line_Tracking_Adjustment();
									}

									delay_ms(50);
							}
					
            Stop_Moving();
            delay_ms(1000);

						//装取货过程
            Execute_Action();  // ← 语音 or 视觉决定调用哪个动作
            delay_ms(2000);

						//返回过程
            return_phase = 1;
            UART3_SendCommand(0, '5');
						Start_to_Move();
						
							while (counter < 5) {

									if (voice_wakeup_flag) {
											Stop_Moving();
											Wait_For_Resume();  // 若唤醒则等待处理
									}

									distance = HCSR04_GetDistance(); 

									if (distance < 5) {
											Stop_Moving();
											Buzzer_On();
										  delay_ms(300);
											UART3_SendCommand(2, '0'); 
									} else {
											Buzzer_Off();
											UART3_SendCommand(2, '1'); 
											Line_Tracking_Adjustment();
									}

									delay_ms(50);
							}


            Stop_Moving();
        }

        Voice_ResetState();  // 重置语音控制标志
			}
}

