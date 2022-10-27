#include "skud.h"
#include "gpio.h"
#include "usart.h"

volatile uint8_t CurState = StateClosed;
volatile uint8_t CurEvent = EventNull;

volatile uint32_t alarmTimeoutCnt = 0;
volatile uint32_t alarmTimeoutCntMax = 50;

volatile uint32_t alarmReloadCnt = 0;
volatile uint32_t alarmReloadCntMax = 50;

volatile uint32_t buzzerFreq = UINT32_MAX;
volatile uint32_t buzzerCnt = 1;


//boolean waitBitch = FALSE;
volatile uint32_t waitBitchCnt = 0;
volatile uint32_t waitBitchCntMax = 20;

volatile uint8_t piskNumCnt = 0;
volatile uint32_t piskNumMax = 4;

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
					
					while(waitBitchCnt < waitBitchCntMax) // сделать на прерываниях
						;
					
					CurEvent = EventReadyForNewKey;
				}

				else 
				{
					
					CurState = StateOpenedValidOk;
					CurEvent = EventValidKey;
					alarmReloadCnt = 0;
				}
			}
			
			else if (alarmTimeoutCnt >= alarmTimeoutCntMax)
			{

				// +отправить сообщение
				CurEvent = EventTimeout;
			}
			
			break;
			
	
		case StateOpenedValidOk:
			
			if (alarmReloadCnt >= alarmReloadCntMax)
			{
				CurState = StateClosed;
				STALED_PIN = 1;
//				CurEvent = EventReactivateAlarm;
			}
			break;
	}

};



