#ifndef TIMER_H
#define TIMER_H

#include "MG32x02z_TM_DRV.h"

void TM0x_IRQHandler(void);

void TIM00_Callback(void);
void TIM01_Callback(void);
void TIM10_Callback(void);
void TIM16_Callback(void);
void TIM36_Callback(void);

void delay_one_ms(void);
void delay_ms(uint32_t);
void delay_one_us(void);
void delay_us(uint32_t);
#endif // TIMER_H