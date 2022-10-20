#include "skud.h"
#include "gpio.h"
#include "usart.h"

uint8_t CurState = StateClosed;
uint8_t CurEvent = EventNull;

uint8_t access = 0;
uint32_t alarmCnt = 0;
uint32_t alarmCntMax = 300;

uint32_t buzzerFreq = 0;
uint32_t buzzerCnt = 0;
uint32_t buzzerCntMax = 0;

boolean waitBitch = FALSE;
uint32_t waitBitchCnt = 0;
uint32_t waitBitchMax = 200;

uint8_t piskNumCnt = 0;
uint32_t piskNumMax = 4;

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
				delay_ms(100); // антидребезг
				if (!GERKON_PIN)
				{
					CurState = StateOpenedAlarm;
					CurEvent = EventOpened;
					TM_Timer_Cmd(TM36, ENABLE);  
				}
			}
			
			break;
			
		case StateOpenedAlarm:
			// запуск тревоги
			// и мониторим ключ

			if (!waitBitch && DS1990A_GetID()) // если считан ключ DS1990A
			{
				// если ключа нет в базе
				if (CheckTruth(keyCurrent) == UINT32_MAX)
				{
					CurEvent = EventNotValidKey;
					waitBitch = TRUE;
				}

				else 
				{	
				
					CurState = StateOpenedValidOk;
					CurEvent = EventValidKey;
				}
			}
			
	
			else if (alarmCnt >= alarmCntMax)
			{
//				CurState = StateOpenedAlarmTimeout;
				CurEvent = EventTimeout;
			}
			
			break;
			
	
		case StateOpenedValidOk:
		
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
			
		case StateOpenedAlarmTimeout:
//			if (access)
//			{
//				
//				TM_Timer_Cmd(TM16, DISABLE); 
//				access = 0;
//				alarmCnt = 0;
//				CurState = StateOpenedValidOk;	
//				URT_Write(CurState);
//			}
			break;
			
		default:
			break;
	}

};


void StartRing(uint8_t rtype, uint32_t duration_ms)
{
	TM_Timer_Cmd(TM36, DISABLE);
	buzzerCnt = 0;
	
	switch (rtype)
	{
		case LongRing:
			buzzerFreq = 100;
			break;
		
		case MediumRing:
			buzzerFreq = 50;
			break;
		
		case FastRing:
			buzzerFreq = 10;
			break;	
		
		case FastFastRing:
			buzzerFreq = 5;
			break;	
	}
	buzzerCntMax = duration_ms / 10; // при T = 100 ms
	TM_Timer_Cmd(TM36, ENABLE);
}

void StopRing(void)
{
	TM_Timer_Cmd(TM36, DISABLE);
	buzzerCnt = 0;
	BUZZER_PIN = 0;
}

