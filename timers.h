#ifndef TIMER_H
#define TIMER_H

#include "MG32x02z_TM_DRV.h"
#include "device_config.h"
#include "gpio.h"
#include "prsm3.h"
#include "variables.h"
#include "usart.h"
#include "skud_algo.h"
#include "ibutton.h"

#define TM_DELAY_MS TM00
#define TM_URT_RECEIVE TM01
#define TM_PRSM_RESET TM10
#define TM_INPUT TM16
#define TM_INDICATION TM36

// для F_CPU = 8МГц

#define TM_DELAY_MS_PERIOD 250 // раз в 1 мс
#define TM_DELAY_MS_PRESCALER 32

#define TM_URT_RECEIVE_PERIOD 250 // раз в 0,25 мс
#define TM_URT_RECEIVE_PRESCALER 8

#define TM_PRSM_RESET_PERIOD 40000u // раз 5 мс
#define TM_PRSM_RESET_PRESCALER 1

#define TM_INPUT_PERIOD 50000u // раз в 100 мс
#define TM_INPUT_PRESCALER 16

#define TM_INDICATION_PERIOD 50000u // раз в 100 мс
#define TM_INDICATION_PRESCALER 16

void TIM01_Callback(void);
void TIM10_Callback(void); 
void TIM16_Callback(void);
void TIM36_Callback(void);

void TM0x_IRQHandler(void);
void TM10_IRQHandler(void);
void TM1x_IRQHandler(void);
void TM3x_IRQHandler(void);

void TIM_Config();
void delay_ms(uint32_t time);
void delay_us(uint32_t time);
#endif // TIMER_H