#include "skud.h"
#include "gpio.h"
#include "usart.h"

uint8_t CurState = StateClosed;
uint8_t CurEvent = EventNull;

uint8_t access = 0;
uint32_t alarmCnt = 0;
uint32_t alarmCntMax = 50;

uint32_t buzzerFreq = 0;
uint32_t buzzerCnt = 0;
uint32_t buzzerCntMax = 0;


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
//					StartRing(MediumRing, UINT32_MAX);
					CurState = StateOpenedAlarm;
					CurEvent = EventOpened;
					TM_Timer_Cmd(TM36, ENABLE); 
					TM_Timer_Cmd(TM16, ENABLE); 
					URT_Write(CurState);
				}
			}
			
			break;
			
		case StateOpenedAlarm:
			// запуск тревоги
			// и мониторим ключ
			
			if (access == 1)	
			{
				
//				StartRing(FastRing, 700); // вместо секунд сколько раз пищит
//				StopRing(); // троекратный сигнал, а потом стоп
				TM_Timer_Cmd(TM16, DISABLE); // сделать отдельные функции
//				alarmCnt = 0;
				access = 0;
				CurState = StateOpenedValidOk;
				URT_Write(CurState);
				CurEvent = EventValidKey;
				
			}
//			
			else if (access == 2)	
			{
				CurEvent = EventNotValidKey;
//					StartRing(FastFastRing, 500);
				access = 0;
			}
			
			
//			else if (alarmCnt >= alarmCntMax)
//			{
//				CurState = StateOpenedAlarmTimeout;
//				URT_Write(CurState);
//			}
			
			break;
			
	
		case StateOpenedValidOk:
			if (GERKON_PIN)
			{
				delay_ms(100);
				if (GERKON_PIN)
				{
					CurState = StateClosed;
					URT_Write(CurState);
				}
			}
			break;
			
		case StateOpenedAlarmTimeout:
			if (access)
			{
				
				TM_Timer_Cmd(TM16, DISABLE); 
				access = 0;
				alarmCnt = 0;
				CurState = StateOpenedValidOk;	
				URT_Write(CurState);
			}
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

