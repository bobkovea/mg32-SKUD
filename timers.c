#include "timers.h"

// Посылка принята целиком - пришло время её разобрать
void TIM01_Callback (void)
{
	PRSM3_ParseMessage();
}
// T = 5 ms
void TIM10_Callback (void)
{
	// Каждый новый байт сбрасывает счетчик usUsart в 1
	// Через 80 мс после прихода последнего байта все переменные очищаются
	// (в случае, если посылка зависла)
	
	// Попробовать TM10->CNT.W = 0 и вкл/выкл 
	
	gerkonState = GERKON_PIN; // + filter

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
	if (DS1990A_GetKeyID() == KEY_ON_LINE)
	{
		if (IsKeyActive(KeyRaw) == KEY_STATUS_ACTIVATED)
			currentEvent = eEnteredValidKey;
		else
			currentEvent = eEnteredInvalidKey;
	}

}

// T = 100 ms
void TIM36_Callback (void)
{
	if (indicTimeCnt == indicTimeMax)
	{
		BUZZER_PIN = 0;
		STALED_PIN = 1;
		TM_Timer_Cmd(TM36, DISABLE);
		currentEvent = eIndicationEnded; // в обработчике мб CNT.W = 0, не выключать таймер
		return;
	}
	
	if (indicTimeCnt % indicSpeed == 0) // indicTimeCnt изначально уже = 1
	{
		BUZZER_PIN = !BUZZER_PIN; // изначально = 0
		STALED_PIN = !STALED_PIN;
	}
	
	++indicTimeCnt;
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
	// а если прерывание зайдет во время задержки? мб __disable_irq?
	// а это сколько тактов?
	for (uint32_t i = 0; i < time; i++)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

void TIM_Config()
{
	TM_TimeBaseInitTypeDef TM_TimeBase_InitStruct;
    TM_TimeBaseStruct_Init(&TM_TimeBase_InitStruct);
	
	// TM_DELAY_MS
    TM_TimeBase_InitStruct.TM_Period = TM_DELAY_MS_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_DELAY_MS_PRESCALER - 1;
    TM_TimeBase_Init(TM_DELAY_MS, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM_DELAY_MS, TMx_TOF);
	
	// TM_URT_RECEIVE
    TM_TimeBase_InitStruct.TM_Period = TM_URT_RECEIVE_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_URT_RECEIVE_PRESCALER - 1;
    TM_TimeBase_Init(TM_URT_RECEIVE, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_URT_RECEIVE, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_URT_RECEIVE, ENABLE); // включаем общие прерывания таймера
	TM_ClearFlag(TM_URT_RECEIVE, TMx_TOF);
	
	NVIC_EnableIRQ(TM0x_IRQn); 
	NVIC_SetPriority(TM0x_IRQn, 0);
	
	// TM_URT_RECEIVE
    TM_TimeBase_InitStruct.TM_Period = TM_PRSM_RESET_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_PRSM_RESET_PRESCALER - 1;
    TM_TimeBase_Init(TM_PRSM_RESET, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_PRSM_RESET, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_PRSM_RESET, ENABLE); // включаем общие прерывания таймера
	TM_ClearFlag(TM_PRSM_RESET, TMx_TOF);
	
	NVIC_EnableIRQ(TM10_IRQn);
	NVIC_SetPriority(TM10_IRQn, 0);
	
	// TM_INPUT
    TM_TimeBase_InitStruct.TM_Period = TM_INPUT_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_INPUT_PRESCALER - 1;
    TM_TimeBase_Init(TM_INPUT, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM_INPUT, TMx_TOF);
	
	NVIC_EnableIRQ(TM1x_IRQn);
	NVIC_SetPriority(TM1x_IRQn, 0);
	
	
	// TM_INDICATION
    TM_TimeBase_InitStruct.TM_Period = TM_INDICATION_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_INDICATION_PRESCALER - 1;
    TM_TimeBase_Init(TM_INDICATION, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM_INDICATION, TMx_TOF);
	
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

