#include "timers.h"

// T = 5 ms
void TIM00_Callback (void) // TM_READ_GERKON
{
	// возможно изменить на проверки
	
	if (GERKON_PIN == 0) // если дверь открылась
	{
		if (gerkonFilterCnt < gerkonFilterMax)
			++gerkonFilterCnt;
		else 
			gerkonState = 1; 
	}
	else
	{
		if (gerkonFilterCnt > 0)
			--gerkonFilterCnt;
		else
			gerkonState = 0;
	}

	// событие открытия/закрытия двери
	if (oldGerkonState == 0 && gerkonState == 1)
	{
		oldGerkonState = gerkonState;
		putEvent(eDoorOpened);
	}
	else if (oldGerkonState == 1 && gerkonState == 0)
	{
		oldGerkonState = gerkonState;
		putEvent(eDoorClosed);
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
	
// T = 5 ms
void TIM01_Callback (void) // TM_PROTECTION_DELAY
{
	if (protectionDelayCnt++ == protectionDelayMax)
	{
		TM_Timer_Cmd(TM_PROTECTION_DELAY, DISABLE);
		protectionDelayCnt = 0;
		putEvent(eProtectionRestored);
	}
}

// T = 100 ms
void TIM10_Callback (void)
{
	if (alarmTimeoutCnt++ == alarmTimeoutMax)
	{
		TM_Timer_Cmd(TM_ALARM_TIMEOUT, DISABLE);
		alarmTimeoutCnt = 0;
		putEvent(eAlarmTimeout);
	}
}

// T = 100 ms
void TIM16_Callback (void) // TM_READ_KEY
{
	if (DS1990A_GetKeyID() == KEY_ON_LINE)  
	{		
		TM_Timer_Cmd(TM_READ_KEY, DISABLE); // отключаем чтение ключа до проверки

		if (IsKeyActive()) // если ключ подошел
		{
			putEvent(eEnteredValidKey);
		}
		else  // если ключ не подошел
		{
			putEvent(eEnteredInvalidKey);
		}
	}
}

// T = 100 ms
void TIM36_Callback (void)
{
	if (indicWaitCnt < indicWaitMax)
	{
		++indicWaitCnt;
		return;
	}
	
	if (indicTimeCnt == indicTimeMax)
	{
		TM_Timer_Cmd(TM_INDICATION, DISABLE);
		putEvent(eIndicationEnded);
		return;
	}
	
	if (indicTimeCnt++ % indicSpeed == 0) // indicTimeCnt изначально уже = 1
	{
		indicationPhase = !indicationPhase;
		if (buzzerMuted == 0) 
		{
			BACKL_PIN = !indicationPhase; // изначально = 0
		}
		STALED_PIN = indicationPhase;
	}
}

void TIM_Config()
{
	TM_TimeBaseInitTypeDef TM_TimeBase_InitStruct;
    TM_TimeBaseStruct_Init(&TM_TimeBase_InitStruct);
	
	// TM_READ_GERKON
    TM_TimeBase_InitStruct.TM_Period = TM_READ_GERKON_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_READ_GERKON_PRESCALER - 1;
    TM_TimeBase_Init(TM_READ_GERKON, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_READ_GERKON, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_READ_GERKON, ENABLE); // включаем общие прерывания таймера
	
	// TM_PROTECTION_DELAY
    TM_TimeBase_InitStruct.TM_Period = TM_PROTECTION_DELAY_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_PROTECTION_DELAY_PRESCALER - 1;
    TM_TimeBase_Init(TM_PROTECTION_DELAY, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_PROTECTION_DELAY, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_PROTECTION_DELAY, ENABLE); // включаем общие прерывания таймера

	// TM_ALARM_TIMEOUT
    TM_TimeBase_InitStruct.TM_Period = TM_ALARM_TIMEOUT_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_ALARM_TIMEOUT_PRESCALER - 1;
    TM_TimeBase_Init(TM_ALARM_TIMEOUT, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_ALARM_TIMEOUT, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_ALARM_TIMEOUT, ENABLE); // включаем общие прерывания таймера
	
	// TM_READ_KEY
    TM_TimeBase_InitStruct.TM_Period = TM_READ_KEY_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_READ_KEY_PRESCALER - 1;
    TM_TimeBase_Init(TM_READ_KEY, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_READ_KEY, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_READ_KEY, ENABLE); // включаем общие прерывания таймера

	// TM_INDICATION
    TM_TimeBase_InitStruct.TM_Period = TM_INDICATION_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_INDICATION_PRESCALER - 1;
    TM_TimeBase_Init(TM_INDICATION, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_INDICATION, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_INDICATION, ENABLE); // включаем общие прерывания таймера
		
	// TM_READ_GERKON и TM_PROTECTION_DELAY
	NVIC_EnableIRQ(TM0x_IRQn); 
	NVIC_SetPriority(TM0x_IRQn, 1);
	
	// TM_ALARM_TIMEOUT
	NVIC_EnableIRQ(TM10_IRQn); 
	NVIC_SetPriority(TM10_IRQn, 3);
	
	// TM_READ_KEY
	NVIC_EnableIRQ(TM1x_IRQn);
	NVIC_SetPriority(TM1x_IRQn, 0);
	
	// TM_INDICATION
	NVIC_EnableIRQ(TM3x_IRQn);
	NVIC_SetPriority(TM3x_IRQn, 2);
}

//----------------------------------------------------------------------------------------
// Обработчики прерываний
//----------------------------------------------------------------------------------------
void TM0x_IRQHandler(void)
{
	// прерывание по переполнению таймера 00 (только оно разрешено)
	if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm00_b0)
	{
		TIM00_Callback();
		TM_ClearFlag (TM00, TMx_TOF);
	}		
	// прерывание по переполнению таймера 01 (только оно разрешено)
	else if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm01_b0)
	{
		TIM01_Callback();
		TM_ClearFlag (TM01, TMx_TOF);		
	}
}

void TM10_IRQHandler(void)
{
	// прерывание по переполнению таймера 10 (только оно разрешено)
	TIM10_Callback();
	TM_ClearFlag (TM10, TMx_TOF);
}

void TM1x_IRQHandler(void)
{
	// прерывание по переполнению таймера 16 (только оно разрешено)
	TIM16_Callback();
	TM_ClearFlag (TM16, TMx_TOF);
}

void TM3x_IRQHandler(void)
{
	// прерывание по переполнению таймера 36 (только оно разрешено)
	TIM36_Callback();
	TM_ClearFlag (TM36, TMx_TOF);

}

