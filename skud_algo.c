#include "skud_algo.h"
#include "stdint.h"
#include "gpio.h"
#include "timers.h"

States_t currentState = sDoorIsClosed;
Events_t currentEvent = eNoEvent;
Events_t newEvent = eNoEvent;
uint8_t indicWaitCnt;
uint8_t indicWaitMax = INDIC_WAIT_MAX;
uint32_t indicTimeCnt;
uint32_t indicTimeMax;
uint8_t indicSpeed;
uint8_t onlyLed;
uint8_t gerkonState;

void IndicationStart(Indication_t indicType)
{
//	TM36->CNT.W = 0;
	BUZZER_OFF();
	STALED_OFF();
	indicTimeCnt = 1;
	indicWaitCnt = 0;

	switch ((uint8_t)indicType)
	{
		case AlarmCommon:
			indicSpeed = INDIC_SPEED_ALARM;
			indicTimeMax = INDIC_CNT_ALARM;

			break;
		
		case ValidKey:
			indicSpeed = INDIC_SPEED_VALID_KEY;
			indicTimeMax = INDIC_CNT_VALID_KEY;
			break;
		
		case InvalidKey:
			indicSpeed = INDIC_SPEED_INVALID_KEY;
			indicTimeMax = INDIC_CNT_INVALID_KEY;
			break;
		
		case OnlyLED: // в AlarmCommon
			onlyLed = 1;
			indicSpeed = INDIC_SPEED_ALARM;
			indicTimeMax = INDIC_CNT_ALARM;
			break;
	
		default: 
			return;	
	}

	TM_Timer_Cmd(TM36, ENABLE);
}

void IndicationStop()
{
	// обнуление всяких штук
	TM_Timer_Cmd(TM36, DISABLE);
	BUZZER_OFF();
	STALED_OFF();
	onlyLed = 0;
	indicTimeCnt = 1;

};


// h - handler
void hDoorOpened(States_t state, Events_t event)
{
	IndicationStart(AlarmCommon);
};

void hEnteredValidKey(States_t state, Events_t event)
{
	IndicationStop();
};

void hEnteredInvalidKey(States_t state, Events_t event)
{
	IndicationStart(InvalidKey);
};

void hAlarmTimeout(States_t state, Events_t event)
{
	
};

void hKeyReadingResumed(States_t state, Events_t event)
{
	
};

void hDoorClosed(States_t state, Events_t event)
{
	
};


// FSMTable[кол-во состояний][кол-во событий]

Transition_t FSMTable[4][6] =
{
	// прописать потом все случаи во избежание последствий гонки потоков
	
    [sDoorIsClosed][eDoorOpened] = { sDoorIsOpenedAlarmOn, hDoorOpened },
	
	[sDoorIsOpenedAlarmOn][eDoorClosed] = { sDoorIsClosed, hDoorClosed },

	[sDoorIsOpenedAlarmOn][eEnteredInvalidKey] = { sKeyReadingSuspended, hEnteredInvalidKey },
	
	[sDoorIsOpenedAlarmOn][eAlarmTimeout] = { sDoorIsOpenedAlarmOn, hAlarmTimeout },
		
	[sDoorIsOpenedAlarmOn][eEnteredValidKey] = { sDoorIsOpenedAlarmOff, hEnteredValidKey },
	
	[sKeyReadingSuspended][eIndicationEnded] = { sDoorIsOpenedAlarmOn, hKeyReadingResumed },
	
	[sDoorIsOpenedAlarmOff][eDoorClosed] = { sDoorIsClosed, hDoorClosed },
	
	/* 
	[sDoorIsClosedAlarmReady]...
	*/
};

// что сделать с лучае, если события произошли почти одновременно, не успев обработаться? 
// очередь событий? скорее игнорировать опоздавшего? мб это не страшно, если вся таблица переходов будет прописана

void HandleEvent()
{
	if (currentEvent != eNoEvent)
	{
        Events_t newEvent = currentEvent;
        currentEvent = eNoEvent;
		
		States_t newState = FSMTable[currentState][newEvent].newState;
		TransitionCallback_t worker = FSMTable[currentState][newEvent].worker;
		if (worker != 0)
		{
			worker(currentState, newEvent);
		}
		currentState = newState;
	}
}

uint8_t IsKeyActive(void)
{
	for (uint16_t keyIndex = 0; keyIndex < 2 /*TotalKeys.value*/; keyIndex++)
    {
		if (IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, keyIndex) == KEY_STATUS_ACTIVATED)
		{
			if(IAP_IsEqualToRAM(PAGE_NUMBER_KEYS_0 * IAP_PAGE_SIZE + keyIndex * KEY_ENCRYPTED_SIZE, KeyRaw, KEY_RAW_SIZE))
//			if(IAP_IsEqualToRAM(PAGE_NUMBER_KEYS_0 * IAP_PAGE_SIZE + keyIndex * KEY_ENCRYPTED_SIZE, KeyEncrypted, KEY_ENCRYPTED_SIZE))
			{
				return KEY_STATUS_ACTIVATED;
			}
		}
    }
	return KEY_STATUS_DEACTIVATED;
}








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



