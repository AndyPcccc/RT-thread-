#include "stm32f4xx.h"
#include "sensor.h"
#include "delay.h"

// ����˸������������������ң�
uint8_t sensor1 = 1; // PE5
uint8_t sensor2 = 1; // PE3
uint8_t sensor3 = 1; // PG12
uint8_t sensor4 = 1; // PG14
uint8_t sensor5 = 1; // PE6
uint8_t sensor6 = 1; // PE2
uint8_t sensor7 = 1; // PG11
uint8_t sensor8 = 1; // PG13

void TrackSensor_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // 1. ʹ�� GPIOE �� GPIOG ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    
    // 2. ���� GPIOE �� PE2, PE3, PE5, PE6 Ϊ����
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    // 3. ���� GPIOG �� PG11, PG12, PG13, PG14 Ϊ����
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOG, &GPIO_InitStruct);
    
    // ��ʼ������������
    sensor1 = sensor2 = sensor3 = sensor4 = sensor5 = sensor6 = sensor7 = sensor8 = 1;
}

void Update_Sensor_Values(void)
{
    // ���´�����ֵ�������ң�
    sensor1 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);  // ��1
    sensor2 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3);  // ��2
    sensor3 = GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_12); // ��3
    sensor4 = GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14); // ��4
    sensor5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);  // ��4
    sensor6 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2);  // ��3
    sensor7 = GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11); // ��2
    sensor8 = GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_13); // ��1
}
