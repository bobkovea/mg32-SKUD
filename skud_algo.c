//#include "skud_algo.h"
//#include "gpio.h"
//#include "usart.h"

//volatile uint8_t CurState = StateClosed;
//volatile uint8_t CurEvent = EventNull;

//volatile uint32_t alarmTimeoutCnt = 0;
//volatile uint32_t alarmTimeoutCntMax = 50; // длительность интервала до отправки сигнала аларма (cек * 10)

//volatile uint32_t alarmReloadCnt = 0;
//volatile uint32_t alarmReloadCntMax = 50; // длительность интервала до автоматической активации сигналки после её снятия (cек * 10)

////boolean waitBitch = FALSE;
//volatile uint32_t waitBitchCnt = 0;
//volatile uint32_t waitBitchCntMax = 20; // длительность интервала до разрешения повторного поднесения ключа (cек * 10)

//volatile uint32_t buzzerFreq = UINT32_MAX; // период следования "писков" зумера (сек / 100)
//volatile uint32_t buzzerCnt = 1;

//volatile uint8_t piskNumCnt = 0;
//volatile uint32_t piskNumMax = UINT16_MAX; // количество "писков" зумера

//uint8_t GetCurEvent (void)
//{
//	uint8_t tmp = CurEvent;
//	CurEvent = EventNull;
//	return tmp;
//};



//void MonitorKey(void)
//{
//	switch (CurState)
//	{
//		case StateClosed:

//		if (!GERKON_PIN) // можно опрос геркона с антидребезгом в прерывание
//			{
//				delay_ms(100); // антидребезг
//				if (!GERKON_PIN)
//				{
//					CurState = StateOpenedAlarm;
//					CurEvent = EventOpened;
//				}
//			}
//			
//			break;
//			
//		case StateOpenedAlarm:
//			// запуск тревоги
//			// и мониторим ключ
//	
//			// if !waitBitch
//			if (DS1990A_GetID()) // если считан ключ DS1990A
//			{
//				// если ключа нет в базе
//				if (CheckTruth(keyCurrent) == UINT32_MAX)
//				{
//					
//					CurEvent = EventNotValidKey;
//					waitBitchCnt = 0;
//					
//					while(waitBitchCnt < waitBitchCntMax) // сделать на прерываниях
//						;
//					
//					CurEvent = EventReadyForNewKey;
//				}

//				else 
//				{
//					CurState = StateOpenedValidOk;
//					CurEvent = EventValidKey;
//					alarmReloadCnt = 0;
//				}
//			}
//			
//			else if (alarmTimeoutCnt >= alarmTimeoutCntMax)
//			{
//			
//				// +отправить сообщение
//				CurEvent = EventTimeout;
//			}
//			
//			break;
//			
//	
//		case StateOpenedValidOk:
//			
//			if (alarmReloadCnt >= alarmReloadCntMax)
//			{
//				CurState = StateClosed;
//				STALED_PIN = 1;
////				CurEvent = EventReactivateAlarm;
//			}
//			break;
//	}

//};



