#include "skud.h"
#include "gpio.h"
#include "usart.h"

uint8_t CurState = StateClosed;
uint8_t CurEvent = EventNull;

uint32_t alarmTimeoutCnt = 0;
uint32_t alarmTimeoutCntMax = 300;

uint32_t alarmReloadCnt = 0;
uint32_t alarmReloadCntMax = 1000;

uint32_t buzzerFreq = UINT32_MAX;
uint32_t buzzerCnt = 1;


boolean waitBitch = FALSE;
uint32_t waitBitchCnt = 0;
uint32_t waitBitchMax = 20;

uint8_t piskNumCnt = 0;
uint32_t piskNumMax = 4;

boolean alarmAuto = 1;
boolean alarmManual = 1;

uint8_t GetCurEvent (void)
{
	uint8_t tmp = CurEvent;
	CurEvent = EventNull;
	return tmp;
};



void MonitorKey(void)
{
	switch (CurState)
	{
		case StateClosed:

			if (!GERKON_PIN)
			{
//				delay_ms(100); // антидребезг
//				if (!GERKON_PIN)
//				{
					CurState = StateOpenedAlarm;
					CurEvent = EventOpened;
//				}
			}
			
			break;
			
		case StateOpenedAlarm:
			// запуск тревоги
			// и мониторим ключ
		
			// if !waitBitch
			if (DS1990A_GetID()) // если считан ключ DS1990A
			{
				// если ключа нет в базе
				if (CheckTruth(keyCurrent) == UINT32_MAX)
				{
					
					CurEvent = EventNotValidKey;
					waitBitchCnt = 0;
					
					while(waitBitchCnt < waitBitchMax)
						;
					STALED_PIN = 1;
					
					CurEvent = EventReadyForNewKey;
				}

				else 
				{
					CurState = StateOpenedValidOk;
					CurEvent = EventValidKey;
				}
			}
			
			else if (alarmTimeoutCnt >= alarmTimeoutCntMax)
			{
				// отправить сообщение
				CurEvent = EventTimeout;
			}
			
			break;
			
	
		case StateOpenedValidOk:
			
			if (alarmReloadCnt >= alarmReloadCntMax)
			{
				CurState = StateClosed;
				CurEvent = EventReactivateAlarm;
			}
			
			
//			if (GERKON_PIN)
//			{
//				delay_ms(100);
//				if (GERKON_PIN)
//				{
//					CurState = StateClosed;
//					URT_Write(CurState);
//				}
//			}
			break;
			
//		case StateOpenedAlarmTimeout:


//				CurState = StateOpenedValidOk;	

//			break;
			
		default:
			break;
	}

};



