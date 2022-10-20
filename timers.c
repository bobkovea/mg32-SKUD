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

}

// T = 10 ms
void TIM36_Callback (void) {
	
	alarmCnt++;

	if (waitBitch) // рано подносишь ключ!
	{
		if (waitBitchCnt == waitBitchMax)
		{

			waitBitchCnt = 0;
			waitBitch = FALSE;
			
		}
		else
		{
			waitBitchCnt++;
		}
			
	}
	
	switch (GetCurEvent())
	{
		case EventNull:
			break;
		
		case EventOpened:
			buzzerCnt = 0;
			piskNumMax = UINT16_MAX; // бесконечно пищим
			buzzerFreq = 100;
			break;
		
		case EventValidKey:
			alarmCnt = 0;
			alarmCntMax = 500;

			buzzerCnt = 0;
			buzzerFreq = 20;
		
			piskNumCnt = 0;
			piskNumMax = 4;
			break;		
		
		case EventNotValidKey:

			buzzerCnt = 0;
			buzzerFreq = 10;
		
			piskNumCnt = 0;
			piskNumMax = 3;
			break;	
		
		case EventTimeout:
			alarmCntMax = UINT32_MAX; //  это событие срабатывает единожды (до снятия тревоги)
//			buzzerFreq = 50;
			break;
	}
			
	if (!(buzzerCnt++ % buzzerFreq))
	{
		BUZZER_PIN = !BUZZER_PIN;
		if (piskNumCnt++ == piskNumMax * 2) // криво, оптимизировать
		{
//			if (CurState == StateOpenedAlarm)
//			{
//				
//			}
//			
//			else if (CurState == StateOpenedValidOk)
//			{
//			
//			}
				
			if (waitBitch)
			{
				BUZZER_PIN = 0; 
				buzzerCnt = 0;
				piskNumCnt = 0;
				piskNumMax = UINT16_MAX; // бесконечно пищим
				buzzerFreq = 100;
			}
			else
			{
				TM_Timer_Cmd(TM36, DISABLE);
				BUZZER_PIN = 0; 
			}
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

