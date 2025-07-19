#include "stm32f4xx_hal.h"
#include "sensor.h"

// 定义 8 个全局变量（从左到右）
uint8_t sensor1 = 1; // PE5
uint8_t sensor2 = 1; // PE3
uint8_t sensor3 = 1; // PG12
uint8_t sensor4 = 1; // PG14
uint8_t sensor5 = 1; // PE6
uint8_t sensor6 = 1; // PE2
uint8_t sensor7 = 1; // PG11
uint8_t sensor8 = 1; // PG13

// 初始化 GPIO 输入引脚
void TrackSensor_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    // PE2, PE3, PE5, PE6
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // PG11, PG12, PG13, PG14
    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    // 初始化传感器值
    sensor1 = sensor2 = sensor3 = sensor4 = sensor5 = sensor6 = sensor7 = sensor8 = 1;
}

// 获取传感器实时值（左到右）
void Update_Sensor_Values(void)
{
    sensor1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);   // 左1
    sensor2 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);   // 左2
    sensor3 = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_12);  // 左3
    sensor4 = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14);  // 左4
    sensor5 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);   // 右4
    sensor6 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);   // 右3
    sensor7 = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11);  // 右2
    sensor8 = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_13);  // 右1
}
