#include "timers.h"
#include "prsm3.h"
#include "MG32x02z_GPIO_DRV.h"
#include "usart.h"
#include "gpio.h"
#include "skud_algo.h"



// Посылка принята целиком - пришло время её разобрать
void TIM01_Callback (void) {
	
	PRSM3_ParseMessage();
}

// Вызывается каждые 5 мс, считывает значения входов
void TIM10_Callback (void) {
		
//		// Каждый новый байт сбрасывает счетчик usUsart в 1
//		// Через 80 мс после прихода последнего байта все переменные очищаются
	
		if (usUsart >= 1) {
			usUsart++;
			if (usUsart > 16)
				PRSM3_clearBuffer();
		}
}

// T = 100 ms
void TIM16_Callback (void) {
	
//	alarmReloadCnt++;
//	alarmTimeoutCnt++;
//	waitBitchCnt++;
}

// T = 10 ms
void TIM36_Callback (void) {
	
//	switch (GetCurEvent())
//	{
//		case EventNull:
//			break;
//		
//		case EventOpened:
//			alarmTimeoutCnt = 0;
//		
//			buzzerCnt = 1;
//			piskNumMax = UINT16_MAX; // бесконечно пищим (настроить, чтоб не совсем бесконечно)
//			buzzerFreq = 100;
//			break;
//	
//		case EventValidKey:
//			
//			BUZZER_PIN = 0;
//			buzzerCnt = 1;
//			buzzerFreq = 20;
//			
//			piskNumCnt = 0;
//			piskNumMax = 4;
//			break;		
//		
//		case EventNotValidKey:
//			
//			BUZZER_PIN = 0;
//			buzzerCnt = 1;
//			buzzerFreq = 10;
//		
//			piskNumCnt = 0;
//			piskNumMax = 3;
//		
////			waitBitch = TRUE;
//			break;	
//		
//		case EventTimeout:
//			alarmTimeoutCntMax = UINT32_MAX; //  это событие срабатывает единожды (до снятия тревоги)
//			break;
//		
//		case EventReadyForNewKey:
//			
//			waitBitchCnt = 0;
////			waitBitch = FALSE;
//		
//			buzzerCnt = 1;
//			piskNumMax = UINT16_MAX; // бесконечно пищим
//			buzzerFreq = 100;
//			break;
//		
//		case EventReactivateAlarm:
//			
//			break;		
//	}
//	
//	if (!(buzzerCnt++ % buzzerFreq))
//	{	
//		BUZZER_PIN = !BUZZER_PIN;
//		piskNumCnt++;
//	}
//	
//	if (piskNumCnt >= piskNumMax * 2) // криво, оптимизировать
//	{
//		BUZZER_PIN = 0;
//		buzzerFreq = UINT32_MAX; // возможно, стоит сделать buzzerCnt uint16
//	}
}


//----------------------------------------------------------------------------------------
// Блокирующая задержка на 1 мс (предварительно настроить таймер)
//----------------------------------------------------------------------------------------
void delay_one_ms(void) { 
	// убрать флаги
	// вместо вкл/выкл сделать сброс TM00->CNT.W = 0x00000000;
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
	
	for (uint32_t i = 0; i < time_ms; i++)
		delay_one_ms();
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
	
	
	// попробовать на таймере вместо вкл/выкл сделать сброс
}


//----------------------------------------------------------------------------------------
// Микросекундный delay
//----------------------------------------------------------------------------------------
void delay_us(uint32_t time_us) {
	uint32_t i = 0;
	while (i++ < time_us)
		delay_one_us();
}

