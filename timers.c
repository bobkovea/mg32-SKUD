#include "timers.h"
#include "prsm3.h"
#include "MG32x02z_GPIO_DRV.h"
#include "usart.h"
#include "gpio.h"
#include "skud.h"


// Посылка принята целиком - пришло время её разобрать
void TIM01_Callback (void) {
	
	PRSM3ReceiveLineComplete();
}

// Вызывается каждые 5 мс, считывает значения входов
void TIM10_Callback (void) {
	
	
//		uint8_t i = 0;
//	
//		if (mn < 0xFF) // зачем это вообще?
//			mn++;
//		if (mn == MaxValue) 
//			InpWasChange = 0xFF; // это нигде даже не обнуляется потом
//		
//			for (i = 0; i < 16; i++) {
//				
//				if (InputRead(i)) {
//					 // Добавляем к фильтру 1
//					if (ModInpVar[i] < MaxValue)
//						ModInpVar[i]++;
//					 // Проверяем достигнут ли порог срабатывания входа
//					if (ModInpVar[i] >= ThrHigh)		  
//						ModInp |= (1 << i);
//				} else {
//					// Убавляем от фильтра 1
//					if (ModInpVar[i] > 0)
//						ModInpVar[i]--;
//					// Проверяем достигнут ли порог срабатывания входа
//					if (ModInpVar[i] <= ThrLow)
//						ModInp &= ~(1 << i);
//				}
//			}

//		// Каждый новый байт сбрасывает счетчик usUsart в 1
//		// Через 80 мс после прихода последнего байта все переменные очищаются
		if (usUsart >= 1) {
			usUsart++;
			if (usUsart > 16) {
				clearBuffer();
			}
		}
}

// T = 100 ms
void TIM16_Callback (void) {
	alarmCnt++;
	if (DS1990A_GetID()) // если считан ключ DS1990A
	{
		
		// если ключа нет в базе
		if (CheckTruth(keyCurrent) == UINT32_MAX)
		{
			URT_Write(0xFE);
			access = 2; // not valid id
		}
			
		else {
			URT_Write(0xDC);
			access = 1; // valid id
		}
	}
}

void TIM36_Callback (void) {
	
	switch (GetCurEvent())
	{
		case EventNull:
			break;
		
		case EventOpened:
			buzzerCnt = 0;
			buzzerCntMax = UINT32_MAX;
			buzzerFreq = 100;
			break;
		
		case EventValidKey:
			buzzerCnt = 0;
			buzzerCntMax = 100;
			buzzerFreq = 20;
			break;		
		
		case EventNotValidKey:
			buzzerCnt = 0;
			buzzerCntMax = 100;
			buzzerFreq = 5;
			break;	
		
//		case EventTimeout:
//			buzzerCntMax = UINT32_MAX;
//			buzzerFreq = 50;
//			break;
	}
	
	if (!(buzzerCnt++ % buzzerFreq))
	{
		BUZZER_PIN = !BUZZER_PIN;
	}
	
	if (buzzerCnt > buzzerCntMax)
	{
		switch (CurState)
		{
			// если ключ неверный, возаращаемся к аларм-писку
			case StateOpenedAlarm:
				buzzerCnt = 0;
				buzzerFreq = 100;
				buzzerCntMax = UINT32_MAX;
				return;
			
			// если ключ верный, то замолкаем
			case StateOpenedValidOk:
				buzzerCnt = 0;
				BUZZER_PIN = 0;
				TM_Timer_Cmd(TM36, DISABLE);
				return;	
		}

	}


}


//----------------------------------------------------------------------------------------
// Блокирующая задержка на 1 мс (предварительно настроить таймер)
//----------------------------------------------------------------------------------------
void delay_one_ms(void) {
	TM_ClearFlag(TM00, TMx_TOF); 
	TM_Timer_Cmd(TM00, ENABLE);
	
	while(TM_GetSingleFlagStatus(TM00, TMx_TOF) == DRV_UnHappened)
		;
	TM_Timer_Cmd(TM00, DISABLE);
	TM_ClearFlag(TM00, TMx_TOF); 
}


//----------------------------------------------------------------------------------------
// Миллисекундный delay
//----------------------------------------------------------------------------------------
void delay_ms(uint32_t time_ms) {
	uint32_t i = 0;
	while (i++ < time_ms) {
		delay_one_ms();
	}
}

//----------------------------------------------------------------------------------------
// Блокирующая задержка на 1 мкс
//----------------------------------------------------------------------------------------
void delay_one_us(void) {
	__NOP(); 
	__NOP();
//	__NOP(); 
//	__NOP();
//	__NOP(); 
//	__NOP();
//	__NOP(); 
//	__NOP();
}


//----------------------------------------------------------------------------------------
// Микросекундный delay
//----------------------------------------------------------------------------------------
void delay_us(uint32_t time_us) {
	uint32_t i = 0;
	while (i++ < time_us)
		delay_one_us();
}

