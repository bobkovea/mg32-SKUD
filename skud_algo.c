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

	TM_Timer_Cmd(TM_INDICATION, ENABLE);
}

void IndicationStop()
{
	// обнуление всяких штук
	TM_Timer_Cmd(TM_INDICATION, DISABLE);
	BUZZER_OFF();
	STALED_OFF();
	onlyLed = 0;
	indicTimeCnt = 1;
};

// h - handler
void hDoorOpened(States_t state, Events_t event)
{	
	TM_Timer_Cmd(TM_INPUT, ENABLE); 
	IndicationStart(AlarmCommon);
};

void hEnteredValidKey(States_t state, Events_t event)
{
	IndicationStart(ValidKey);
};

void hEnteredInvalidKey(States_t state, Events_t event)
{
	IndicationStart(InvalidKey);
};

void hAlarmTimeout(States_t state, Events_t event)
{
	IndicationStop();
};

void hKeyReadingResumed(States_t state, Events_t event)
{
	TM_Timer_Cmd(TM_INPUT, ENABLE);
	IndicationStart(AlarmCommon);
};

void hDoorClosed(States_t state, Events_t event)
{	
	TM_Timer_Cmd(TM_INPUT, DISABLE); 
	IndicationStop();
};


// FSMTable[кол-во состояний][кол-во событий]
Transition_t FSMTable[4][6] =
{
    [sDoorIsClosed][eDoorOpened] 				= { sDoorIsOpenedAlarmOn, hDoorOpened },
	[sDoorIsClosed][eEnteredValidKey] 			= {	sDoorIsClosed,  0 },
	[sDoorIsClosed][eEnteredInvalidKey] 		= { sDoorIsClosed,  0 },
	[sDoorIsClosed][eIndicationEnded] 			= { sDoorIsClosed,  0 },
	[sDoorIsClosed][eAlarmTimeout] 				= { sDoorIsClosed,  0 },
	[sDoorIsClosed][eDoorClosed] 				= { sDoorIsClosed,  0 },
	
	[sDoorIsOpenedAlarmOn][eDoorOpened] 		= { sDoorIsOpenedAlarmOn, 0 },
	[sDoorIsOpenedAlarmOn][eEnteredValidKey] 	= { sDoorIsOpenedAlarmOff, hEnteredValidKey },
	[sDoorIsOpenedAlarmOn][eEnteredInvalidKey] 	= { sKeyReadingSuspended, hEnteredInvalidKey },
	[sDoorIsOpenedAlarmOn][eIndicationEnded] 	= { sDoorIsOpenedAlarmOn, 0 },
	[sDoorIsOpenedAlarmOn][eAlarmTimeout] 		= { sDoorIsOpenedAlarmOn, hAlarmTimeout },
	[sDoorIsOpenedAlarmOn][eDoorClosed] 		= { sDoorIsOpenedAlarmOn, 0 },
	
	[sKeyReadingSuspended][eDoorOpened] 		= { sKeyReadingSuspended, 0 },
	[sKeyReadingSuspended][eEnteredValidKey] 	= { sKeyReadingSuspended, 0 },
	[sKeyReadingSuspended][eEnteredInvalidKey] 	= { sKeyReadingSuspended, 0 },
	[sKeyReadingSuspended][eIndicationEnded] 	= { sDoorIsOpenedAlarmOn, hKeyReadingResumed },
	[sKeyReadingSuspended][eAlarmTimeout] 		= { sKeyReadingSuspended, 0 },
	[sKeyReadingSuspended][eDoorClosed] 		= { sKeyReadingSuspended, 0 },
	
	[sDoorIsOpenedAlarmOff][eDoorOpened] 		= { sDoorIsOpenedAlarmOff, 0 },
	[sDoorIsOpenedAlarmOff][eEnteredValidKey] 	= { sDoorIsOpenedAlarmOff, 0 },
	[sDoorIsOpenedAlarmOff][eEnteredInvalidKey] = { sDoorIsOpenedAlarmOff, 0 },
	[sDoorIsOpenedAlarmOff][eIndicationEnded] 	= { sDoorIsOpenedAlarmOff, 0 },
	[sDoorIsOpenedAlarmOff][eAlarmTimeout] 		= { sDoorIsOpenedAlarmOff, 0 },
	[sDoorIsOpenedAlarmOff][eDoorClosed] 		= { sDoorIsClosed, hDoorClosed },
	
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
	for (uint16_t keyIndex = 0; keyIndex < TotalKeys.value /*KEYS_COUNT*/; keyIndex++)
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







