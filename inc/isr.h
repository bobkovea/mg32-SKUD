#ifndef ISR_H
#define ISR_H

#include "timers.h"
#include "usart.h"
#include "skud_algo.h"
#include "ibutton.h"
#include "bus.h"

void TIM00_Callback(void);
void TIM01_Callback(void);
void TIM10_Callback(void); 
void TIM16_Callback(void);
void TIM36_Callback(void);

void URT_Rx_Callback(void);

#endif // ISR_H