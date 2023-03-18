#include "timers.h"

volatile uint8_t gerkonStateFilter = 0;
volatile uint8_t gerkonStateFilterMax = 20;
volatile uint8_t oldGerkonState = 0;
volatile uint8_t gerkonState = 0;

volatile uint8_t alarmTimeoutCnt = 0;
volatile uint32_t alarmTimeoutMax = 20;

// T = 5 ms
void TIM00_Callback (void) // TM_PRSM_RESET
{
	// Попробовать TM10->CNT.W = 0 и вкл/выкл
	
	// фильтр
	
	if (GERKON_PIN == 0)
	{
		if (gerkonStateFilter < gerkonStateFilterMax)
			++gerkonStateFilter;
		else 
			gerkonState = 1;	
	}
	else
	{
		if (gerkonStateFilter > 0)
			--gerkonStateFilter;
		else
			gerkonState = 0;
	}

	// событие открытия/закрытия двери
	if (oldGerkonState == 0 && gerkonState == 1)
	{
		oldGerkonState = gerkonState;
		currentEvent = eDoorOpened;	
	}
	else if (oldGerkonState == 1 && gerkonState == 0)
	{
		oldGerkonState = gerkonState;
		currentEvent = eDoorClosed;	
	}
	
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
	
// Посылка принята целиком - пришло время её разобрать
void TIM01_Callback (void)
{
	usUsart = 0;
	PRSM3_ParseMessage();
}

// Счетчик аларма T = 100 ms
void TIM10_Callback (void)
{
	if (alarmTimeoutCnt < alarmTimeoutMax)
	{
		++alarmTimeoutCnt;
	}
	else
	{
		alarmTimeoutCnt = 0;
		currentEvent = eAlarmTimeout;
	}
}


// T = 100 ms
// TM_READ_KEY
void TIM16_Callback (void)
{
	if (DS1990A_GetKeyID() == KEY_ON_LINE)  
	{
		TM_Timer_Cmd(TM_READ_KEY, DISABLE);
		
		if (IsKeyActive())
			currentEvent = eEnteredValidKey;
		else
			currentEvent = eEnteredInvalidKey;
	}
}

// T = 100 ms
void TIM36_Callback (void)
{
	// Проверки для бесконечного alarmCommon нет из-за огромности UINT32_MAX
	if (indicWaitCnt < indicWaitMax)
	{
		++indicWaitCnt;
		return;
	}

	if (indicTimeCnt == indicTimeMax)
	{
		BUZZER_OFF();
		STALED_OFF();
		TM_Timer_Cmd(TM_INDICATION, DISABLE);
		currentEvent = eIndicationEnded; // в обработчике мб CNT.W = 0, не выключать таймер
		return;
	}
	
	if (indicTimeCnt++ % indicSpeed == 0) // indicTimeCnt изначально уже = 1
	{
		if (onlyLed == 0) 
		{
			//BACKL_PIN = !BACKL_PIN; // изначально = 0
		}
		STALED_PIN = !STALED_PIN;
	}
}

//----------------------------------------------------------------------------------------
// Миллисекундный delay
//----------------------------------------------------------------------------------------
void delay_ms(uint32_t time) 
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
void delay_us(uint32_t time)
{
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
	
	// TM_PRSM_RESET
    TM_TimeBase_InitStruct.TM_Period = TM_PRSM_RESET_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_PRSM_RESET_PRESCALER - 1;
    TM_TimeBase_Init(TM_PRSM_RESET, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_PRSM_RESET, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_PRSM_RESET, ENABLE); // включаем общие прерывания таймера
	TM_ClearFlag(TM_PRSM_RESET, TMx_TOF);
	
	// TM_URT_RECEIVE
    TM_TimeBase_InitStruct.TM_Period = TM_URT_RECEIVE_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_URT_RECEIVE_PRESCALER - 1;
    TM_TimeBase_Init(TM_URT_RECEIVE, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_URT_RECEIVE, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_URT_RECEIVE, ENABLE); // включаем общие прерывания таймера
	TM_ClearFlag(TM_URT_RECEIVE, TMx_TOF);

	// TM_ALARM_TIMEOUT
    TM_TimeBase_InitStruct.TM_Period = TM_ALARM_TIMEOUT_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_ALARM_TIMEOUT_PRESCALER - 1;
    TM_TimeBase_Init(TM_ALARM_TIMEOUT, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_ALARM_TIMEOUT, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_ALARM_TIMEOUT, ENABLE); // включаем общие прерывания таймера
	TM_ClearFlag(TM_ALARM_TIMEOUT, TMx_TOF);
	
	// TM_READ_KEY
    TM_TimeBase_InitStruct.TM_Period = TM_READ_KEY_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_READ_KEY_PRESCALER - 1;
    TM_TimeBase_Init(TM_READ_KEY, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM_READ_KEY, TMx_TOF);
	TM_IT_Config(TM_READ_KEY, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_READ_KEY, ENABLE); // включаем общие прерывания таймера

	// TM_INDICATION
    TM_TimeBase_InitStruct.TM_Period = TM_INDICATION_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_INDICATION_PRESCALER - 1;
    TM_TimeBase_Init(TM_INDICATION, &TM_TimeBase_InitStruct);
	TM_ClearFlag(TM_INDICATION, TMx_TOF);
	TM_IT_Config(TM_INDICATION, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_INDICATION, ENABLE); // включаем общие прерывания таймера
		
	// TM_PRSM_RESET и TM_URT_RECEIVE
	NVIC_EnableIRQ(TM0x_IRQn); 
	NVIC_SetPriority(TM0x_IRQn, 0);
	
	// TM_ALARM_TIMEOUT
	NVIC_EnableIRQ(TM10_IRQn); 
	NVIC_SetPriority(TM10_IRQn, 3);
	
	// TM_READ_KEY
	NVIC_EnableIRQ(TM1x_IRQn);
	NVIC_SetPriority(TM1x_IRQn, 1);
	
	// TM_INDICATION
	NVIC_EnableIRQ(TM3x_IRQn);
	NVIC_SetPriority(TM3x_IRQn, 2);
}

//----------------------------------------------------------------------------------------
// Обработчики прерываний
//----------------------------------------------------------------------------------------
void TM0x_IRQHandler(void)
{
	if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm00_b0)
	{
		// прерывание по переполнению таймера
		if (TM_GetSingleFlagStatus(TM00, TMx_TOF) == DRV_Happened)
		{
			TIM00_Callback();
			TM_ClearFlag (TM00, TMx_TOF);
		}	
	}		
		
	else if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm01_b0)
		// прерывание по переполнению таймера
	{
		if (TM_GetSingleFlagStatus(TM01, TMx_TOF) == DRV_Happened)
		{
			TIM01_Callback();
			TM_ClearFlag (TM01, TMx_TOF);
		}		
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

