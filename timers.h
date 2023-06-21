#ifndef TIMER_H
#define TIMER_H

#include "MG32x02z_TM_DRV.h"
#include "MG32x02z_EXIC_DRV.h" // для прерываний TM00/01
#include "isr.h"

#define TM_READ_GERKON TM00
#define TM_PROTECTION_DELAY TM01
#define TM_ALARM_TIMEOUT TM10
#define TM_READ_KEY TM16
#define TM_INDICATION TM36

// для F_CPU = 8 МГц

#define TM_READ_GERKON_PERIOD 250 // раз 5 мс
#define TM_READ_GERKON_PRESCALER 160

#define TM_PROTECTION_DELAY_PERIOD 250 // раз в 5 мс
#define TM_PROTECTION_DELAY_PRESCALER 160

#define TM_ALARM_TIMEOUT_PERIOD 50000u // раз в 100 мс
#define TM_ALARM_TIMEOUT_PRESCALER 16

#define TM_READ_KEY_PERIOD 50000u // раз в 100 мс
#define TM_READ_KEY_PRESCALER 16

#define TM_INDICATION_PERIOD 50000u // раз в 100 мс
#define TM_INDICATION_PRESCALER 16


//----------------------------------------------------------------------------------------
// Миллисекундный delay
//----------------------------------------------------------------------------------------
__STATIC_INLINE void delay_ms(uint32_t time) 
{
	for (uint32_t i = 0; i < time * 1000; i++)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

//----------------------------------------------------------------------------------------
// Микросекундный delay
//----------------------------------------------------------------------------------------
__STATIC_INLINE void delay_us(uint32_t time)
{
	for (uint32_t i = 0; i < time; i++)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

void TIM_Config();
#endif // TIMER_H