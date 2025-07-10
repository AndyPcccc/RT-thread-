#include "delay.h"

static uint32_t fac_us = 0;

void delay_init(void) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); // 使用主频 HCLK（84MHz）
		fac_us = 16000000 / 1000000;  // 运行中发现实际是 16MHz，故修改

}

void delay_us(uint32_t nus) {
    uint32_t temp;
    SysTick->LOAD = nus * fac_us;  // 设置倒计时时间
    SysTick->VAL = 0;              // 清空当前值
    SysTick->CTRL = 0x01;          // 启动 SysTick（不使能中断）

    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));  // 等待计数结束

    SysTick->CTRL = 0;  // 关闭计数器
    SysTick->VAL = 0;   // 清空当前值
}

void delay_ms(uint32_t nms) {
    while (nms--) {
        delay_us(1000);  // 每次延时1ms
    }
}
