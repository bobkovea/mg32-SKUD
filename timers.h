#ifndef TIMER_H
#define TIMER_H

#include "MG32x02z_TM_DRV.h"
#include "device_config.h"
#include "gpio.h"
#include "prsm3.h"
#include "variables.h"
#include "usart.h"
#include "skud_algo.h"

#define F_CPU_BASE 8000000.0f

#define TM_DELAY_MS TM00
#define TM_URT_RECEIVE TM01
//#define  TM10
#define TM_DELAY_US TM16

#define TM_DELAY_MS_Period (F_CPU / F_CPU_BASE) * 99
#define TM_DELAY_MS_Prescaler (F_CPU / F_CPU_BASE) * 79

#define TM_URT_RECEIVE_Period (F_CPU / F_CPU_BASE) * 47
#define TM_URT_RECEIVE_Prescaler (F_CPU / F_CPU_BASE) * 39

void TIM01_Callback(void);
void TIM10_Callback(void);
void TIM16_Callback(void);
void TIM30_Callback(void);

void TM0x_IRQHandler(void);
void TM10_IRQHandler(void);
void TM1x_IRQHandler(void);
void TM3x_IRQHandler(void);

void TIM_Config();
void delay_ms(uint32_t);
void delay_us(uint32_t time);
#endif // TIMER_H