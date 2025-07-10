#include "delay.h"

static uint32_t fac_us = 0;

void delay_init(void) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); // ʹ����Ƶ HCLK��84MHz��
		fac_us = 16000000 / 1000000;  // �����з���ʵ���� 16MHz�����޸�

}

void delay_us(uint32_t nus) {
    uint32_t temp;
    SysTick->LOAD = nus * fac_us;  // ���õ���ʱʱ��
    SysTick->VAL = 0;              // ��յ�ǰֵ
    SysTick->CTRL = 0x01;          // ���� SysTick����ʹ���жϣ�

    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));  // �ȴ���������

    SysTick->CTRL = 0;  // �رռ�����
    SysTick->VAL = 0;   // ��յ�ǰֵ
}

void delay_ms(uint32_t nms) {
    while (nms--) {
        delay_us(1000);  // ÿ����ʱ1ms
    }
}
