#ifndef __SENSOR_H
#define __SENSOR_H 
#include "stm32f4xx.h"
extern uint8_t sensor1, sensor2, sensor3, sensor4;
extern uint8_t sensor5, sensor6, sensor7, sensor8;
void TrackSensor_GPIO_Init(void);
void Update_Sensor_Values(void);
#endif
