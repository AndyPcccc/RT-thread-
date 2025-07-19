#include "pwm.h"
#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

const int PWM_FREQUENCY = 20000;

// ************** 配置电机方向控制 GPIO **************
void Motor_GPIO_Config(void)
{
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    // 电机 1/2：PE9/12/11/13
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_13;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // 电机 3/4：PB6/3/5/11
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_11;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// ************** 配置 PWM **************
void PWM_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    // 使能时钟
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 关闭 USART3（避免占用 PB10）
    __HAL_RCC_USART3_CLK_DISABLE();

    // GPIO 复用配置
    GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    // PA8（TIM1_CH1）、PA1（TIM2_CH2）
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0); // 防止干扰
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_1, GPIO_PIN_RESET);

    // PB10（TIM2_CH3）、PB7（TIM4_CH2）
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

    // 初始化 TIM1
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 84 - 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 999;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&htim1);

    // TIM2 同样配置
    htim2.Instance = TIM2;
    htim2.Init = htim1.Init;
    HAL_TIM_PWM_Init(&htim2);

    htim4.Instance = TIM4;
    htim4.Init = htim1.Init;
    HAL_TIM_PWM_Init(&htim4);

    // 配置 PWM 输出通道
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);

    // 启动输出
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

    // TIM1 是高级定时器，需要开启 MOE
    __HAL_TIM_MOE_ENABLE(&htim1);
}

// ************** 设置电机速度 **************
void Motor_SetSpeed(int motor, int speed)
{
    uint16_t pwm_val = (speed > 0) ? speed : -speed;
    GPIO_PinState dir = (speed > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET;

    switch (motor)
    {
    case 1:
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, dir);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, !dir);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm_val); // PA1
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, dir);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, !dir);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm_val); // PA8
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, dir);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, !dir);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm_val); // PB10
        break;
    case 4:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, dir);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, !dir);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm_val); // PB7
        break;
    }
}

// ************** 配置 STBY（使能）引脚 **************
void STBY_GPIO_Config(void)
{
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET); // STBY = 1
}
