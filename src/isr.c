#include "isr.h"

/*----------------------------------------------------------------------------------------
// Обработчик прерывания USART по приему байта
----------------------------------------------------------------------------------------*/

void URT_Rx_Callback(void)
{
	Bus_AddNewByte();
}


/*----------------------------------------------------------------------------------------
// Обработчики прерывания по переполнению таймеров 
----------------------------------------------------------------------------------------*/


/* Опрос геркона + таймаут приема посылки */
// T = 5мс
void TIM00_Callback (void) // TM_READ_GERKON
{
	if (!doorIsOpened) // если дверь закрыта
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
	

/* Обратный отсчет времени доступа после ввода ключа */
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

/* Обратный отсчет времени до заглушения пищалки */
// T = 100 ms
void TIM10_Callback (void) // TM_MUTE_SOUND
{
	if (muteTimeoutCnt++ == muteTimeoutMax)
	{
		TM_Timer_Cmd(TM_MUTE_SOUND, DISABLE);
		muteTimeoutCnt = 0;
		putEvent(eAlarmTimeout);
	}
}

/* Мониторинг и проверка ключа на линии */
// T = 100 ms
void TIM16_Callback (void) // TM_READ_KEY
{
	if (DS1990A_GetKeyID() == KEY_ON_LINE)  
	{		
		TM_Timer_Cmd(TM_READ_KEY, DISABLE); // отключаем чтение ключа до проверки

		if (API_IsRawKeyValid()) // если ключ подошел
		{
			putEvent(eEnteredValidKey);
		}
		else  // если ключ не подошел
		{
			putEvent(eEnteredInvalidKey);
		}
	}
}

/* Индикация */
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
		putEvent(eIndicationEnded);
		return;
	}
	
	if (indicTimeCnt++ % indicSpeed == 0) // indicTimeCnt изначально уже = 1
	{
		indicationPhase = !indicationPhase;
		if (buzzerIsMuted == 0) 
		{
			BACKL_PIN = !indicationPhase; // изначально = 0
		}
		STALED_PIN = indicationPhase;
	}
}