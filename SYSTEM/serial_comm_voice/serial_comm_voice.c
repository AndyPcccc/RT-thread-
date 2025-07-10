#include "serial_comm_voice.h"
#include "fmq.h"
#include "delay.h"
#include "pwm.h"
#include "serial_comm_screen.h"

volatile uint8_t voice_cmd = 0;
volatile uint8_t voice_wakeup_flag = 0;
volatile uint8_t override_data = 0;
volatile uint8_t route_active_flag = 0;

void VOICE_UART5_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART5, &USART_InitStruct);

    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void UART5_IRQHandler(void) {
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) {
        char ch = USART_ReceiveData(UART5);
        voice_cmd = ch;

        if (ch == '8') {
            voice_wakeup_flag = 1;
						Motor_SetSpeed(1, 0);
						Motor_SetSpeed(2, 0);
						Motor_SetSpeed(3, 0);
						Motor_SetSpeed(4, 0);;
            Voice_QuickBeep();
        } else if (ch == '0') {
            // 保持暂停
        } else if (ch == '9') {
            voice_wakeup_flag = 0;
            Voice_QuickBeep();
        } else if (!route_active_flag && ch >= '1' && ch <= '4') {
            override_data = ch - '0';
        }
    }
}


void Voice_ResetState(void) {
    voice_cmd = 0;
    override_data = 0;
    voice_wakeup_flag = 0;
    route_active_flag = 0;
}

void Voice_Check_MainLoop(void) {
    if (voice_wakeup_flag) {
				Motor_SetSpeed(1, 0);
				Motor_SetSpeed(2, 0);
				Motor_SetSpeed(3, 0);
				Motor_SetSpeed(4, 0);
				UART3_SendCommand(2, '0'); 
    }
}

void Voice_QuickBeep(void) {
    Buzzer_On(); delay_ms(100);
    Buzzer_Off(); delay_ms(100);
    Buzzer_On(); delay_ms(100);
    Buzzer_Off();
}

void Wait_For_Resume(void) {
    uint16_t timeout = 100;  // 最多等 5 秒（100 * 50ms）
    while (voice_wakeup_flag) {
        delay_ms(50);
				UART3_SendCommand(2, '0'); 

        if (voice_cmd == '9') {  // 收到继续
            voice_wakeup_flag = 0;
            voice_cmd = 0;
						UART3_SendCommand(2, '1'); 
            Voice_QuickBeep();
						Motor_SetSpeed(1, -150);
						Motor_SetSpeed(2, -5);
						Motor_SetSpeed(3, -150);
						Motor_SetSpeed(4, -5);
            break;
        } else if (voice_cmd == '0') {  // 收到暂停
            timeout = 0xFFFF;  // 无限等待
        }

        if (timeout != 0xFFFF && timeout-- == 0) {
            voice_wakeup_flag = 0;  // 超时恢复
						UART3_SendCommand(2, '1'); 
            Voice_QuickBeep();
						Motor_SetSpeed(1, -150);
						Motor_SetSpeed(2, -5);
						Motor_SetSpeed(3, -150);
						Motor_SetSpeed(4, -5);
            break;
        }
    }

    voice_cmd = 0;  // 清除状态
}
