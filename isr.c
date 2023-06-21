#include "isr.h"

#ifndef ISR_H
#define ISR_H

//----------------------------------------------------------------------------------------
// Обработчик прерывания USART по приему байта
//----------------------------------------------------------------------------------------
void URT_Rx_Callback(void)
{
	Bus_AddNewByte();
}

//----------------------------------------------------------------------------------------
// Обработчики прерывания по переполнению таймеров 
//----------------------------------------------------------------------------------------

// T = 5 ms
void TIM00_Callback (void) // TM_READ_GERKON
{
	// если дверь закрыта
	if (!doorIsOpened)
	{
		if (!GERKON_PIN) // если дверь открылась
		{
			if (gerkonFilterCnt < gerkonFilterMax) // фильтруем вход - вдруг дребезг?
			{
				++gerkonFilterCnt; 
			}
			else
			{
				putEvent(eDoorOpened); // событие "дверь открылась"
				doorIsOpened = 1; // дверь официально открыта
			}
		}
	}
	
	else // аналогично обрабатываем закрытие двери
	{
		if (GERKON_PIN)
		{
			if (gerkonFilterCnt > 0)
			{
				--gerkonFilterCnt;
			}
			else
			{
				putEvent(eDoorClosed);
				doorIsOpened = 0;
			}
		}
		
	}
	
	// Каждый новый байт сбрасывает счетчик usUsart в 1
	// Через 80 мс после прихода последнего байта все переменные очищаются
	// и можно вновь принимать посылку
	if (usUsart >= 1)
	{
		usUsart++;
		if (usUsart > 16)
			Bus_ClearBuffer();
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
void TIM10_Callback (void) // TM_ALARM_TIMEOUT
{
//	if (alarmTimeoutCnt++ == alarmTimeoutMax)
//	{
//		TM_Timer_Cmd(TM_ALARM_TIMEOUT, DISABLE);
//		alarmTimeoutCnt = 0;
//		putEvent(eAlarmTimeout);
//	}
}

// T = 100 ms
void TIM16_Callback (void) // TM_READ_KEY
{
	if (DS1990A_GetKeyID() == KEY_ON_LINE)  
	{		
		TM_Timer_Cmd(TM_READ_KEY, DISABLE); // отключаем чтение ключа до проверки

		if (IsKeyValid()) // если ключ подошел
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
void TIM36_Callback (void) // TM_INDICAION
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
#endif // ISR_H