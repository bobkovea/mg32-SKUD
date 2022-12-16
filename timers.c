#include "timers.h"
#include "skud_algo.h"
// Посылка принята целиком - пришло время её разобрать
void TIM01_Callback (void)
{
	PRSM3_ParseMessage();
}

void TIM10_Callback (void)
{
	// Каждый новый байт сбрасывает счетчик usUsart в 1
	// Через 80 мс после прихода последнего байта все переменные очищаются
	// (в случае, если посылка зависла)
	
	if (usUsart >= 1)
	{
		usUsart++;
		if (usUsart > 16)
			PRSM3_clearBuffer();
	}
}

// T = 100 ms
void TIM16_Callback (void)
{	
	if (!GERKON_PIN)
	{
		currentEvent = eDoorOpened;
	}
}

// T = 100 ms
void TIM36_Callback (void)
{
	if (peeCnt == peeMax)
	{
		currentEvent = eIndicationStop;
	}
	
	if (peeCnt++ % 2)
	{
		BUZZER_PIN = 0;
		STALED_PIN = 1;
	}
	else
	{
		BUZZER_PIN = 1;
		STALED_PIN = 0;
	}
}


//----------------------------------------------------------------------------------------
// Миллисекундный delay
//----------------------------------------------------------------------------------------
void delay_ms(uint32_t time) 
{
	TM_Timer_Cmd(TM_DELAY_MS, ENABLE);
	for (uint32_t i = 0; i < time; i++)
	{
		while(TM_GetSingleFlagStatus(TM_DELAY_MS, TMx_TOF) == DRV_UnHappened);
		TM_ClearFlag(TM_DELAY_MS, TMx_TOF); 
	}
	TM_Timer_Cmd(TM_DELAY_MS, DISABLE);
}

//----------------------------------------------------------------------------------------
// Микросекундный delay
//----------------------------------------------------------------------------------------
void delay_us(uint32_t time)
{
	for (uint32_t i = 0; i < time; i++)
	{
		__NOP(); __NOP();
	}
}

void TIM_Config()
{
	TM_TimeBaseInitTypeDef TM_TimeBase_InitStruct;
    TM_TimeBaseStruct_Init(&TM_TimeBase_InitStruct);
	
	// TM_DELAY_MS
    TM_TimeBase_InitStruct.TM_Period = TM_DELAY_MS_Period; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_DELAY_MS_Prescaler;
    TM_TimeBase_Init(TM_DELAY_MS, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM_DELAY_MS, TMx_TOF);
	
	// TM_URT_RECEIVE
    TM_TimeBase_InitStruct.TM_Period = TM_URT_RECEIVE_Period; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_URT_RECEIVE_Prescaler;
    TM_TimeBase_Init(TM_URT_RECEIVE, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_URT_RECEIVE, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_URT_RECEIVE, ENABLE); // включаем общие прерывания таймера
	TM_ClearFlag(TM_URT_RECEIVE, TMx_TOF);
	
	NVIC_EnableIRQ(TM0x_IRQn); 
	NVIC_SetPriority(TM0x_IRQn, 0);
	
	// TM10
    TM_TimeBase_InitStruct.TM_Period = 0; 
    TM_TimeBase_InitStruct.TM_Prescaler = 7;
    TM_TimeBase_Init(TM10, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM10, TMx_TOF);
	
	NVIC_EnableIRQ(TM10_IRQn);
	NVIC_SetPriority(TM10_IRQn, 0);
	
	// TM16
    TM_TimeBase_InitStruct.TM_Period = 0; 
    TM_TimeBase_InitStruct.TM_Prescaler = 7;
    TM_TimeBase_Init(TM16, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM16, TMx_TOF);
	
	NVIC_EnableIRQ(TM1x_IRQn);
	NVIC_SetPriority(TM1x_IRQn, 0);
	
	// TM36
    TM_TimeBase_InitStruct.TM_Period = 0; 
    TM_TimeBase_InitStruct.TM_Prescaler = 7999u;
    TM_TimeBase_Init(TM36, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM36, TMx_TOF);
	
	NVIC_EnableIRQ(TM3x_IRQn);
	NVIC_SetPriority(TM3x_IRQn, 0);
}

//----------------------------------------------------------------------------------------
// Обработчики прерываний
//----------------------------------------------------------------------------------------
void TM0x_IRQHandler(void)
{
	if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm01_b0)
		// прерывание по переполнению таймера
		if (TM_GetSingleFlagStatus(TM01, TMx_TOF) == DRV_Happened)
		{
			TIM01_Callback();
			TM_ClearFlag (TM01, TMx_TOF);
		}		
}

void TM10_IRQHandler(void)
{
	// прерывание по переполнению таймера
    if (TM_GetSingleFlagStatus(TM10, TMx_TOF) == DRV_Happened)
    {
        TIM10_Callback();
        TM_ClearFlag (TM10, TMx_TOF);
    }
}

void TM1x_IRQHandler(void)
{
	// прерывание по переполнению таймера
    if (TM_GetSingleFlagStatus(TM16, TMx_TOF) == DRV_Happened)
    {
        TIM16_Callback();
        TM_ClearFlag (TM16, TMx_TOF);
    }
}

void TM3x_IRQHandler(void)
{
	// прерывание по переполнению таймера
    if (TM_GetSingleFlagStatus(TM36, TMx_TOF) == DRV_Happened)
    {
        TIM36_Callback();
        TM_ClearFlag (TM36, TMx_TOF);
    }
}

