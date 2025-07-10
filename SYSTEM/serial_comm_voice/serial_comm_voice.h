#ifndef __SERIAL_COMM_VOICE_H
#define __SERIAL_COMM_VOICE_H

#include "stm32f4xx.h"

extern volatile uint8_t voice_cmd;             
extern volatile uint8_t voice_wakeup_flag;     
extern volatile uint8_t override_data;         
extern volatile uint8_t route_active_flag;     

void VOICE_UART5_Init(void);  
void Voice_ResetState(void);
void Voice_Check_MainLoop(void);
void Voice_QuickBeep(void);
void Wait_For_Resume(void);

#endif
