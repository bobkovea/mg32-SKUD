#include "skud_algo.h"
#include "stdint.h"
#include "gpio.h"
#include "timers.h"
#include "md5.h"

State_t currentState = sDoorIsClosed;
volatile uint8_t indicWaitCnt = 0;
volatile uint8_t indicWaitMax = INDIC_WAIT_MAX;
volatile uint32_t indicTimeCnt = 1;
volatile uint32_t indicTimeMax = INDIC_CNT_ALARM;
volatile uint8_t indicSpeed = INDIC_SPEED_ALARM;
volatile uint8_t onlyLed = 0;

volatile uint32_t alarmTimeoutCnt = 0;
volatile uint32_t alarmTimeoutMax = ALARM_TIMEOUT_MAX;

volatile uint8_t gerkonStateFilter = 0;
volatile uint8_t gerkonStateFilterMax = 20;
volatile uint8_t oldGerkonState = 0;
volatile uint8_t gerkonState = 0;

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
void hDoorOpened(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_ALARM_TIMEOUT, ENABLE); 
	TM_Timer_Cmd(TM_READ_KEY, ENABLE); 
	IndicationStart(AlarmCommon);
};

void hEnteredValidKey(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_ALARM_TIMEOUT, DISABLE);
	alarmTimeoutCnt = 0;
	IndicationStart(ValidKey);
};

void hEnteredInvalidKey(State_t state, Event_t event)
{
	IndicationStart(InvalidKey);
};

void hAlarmTimeout(State_t state, Event_t event)
{
	eventAlarm.repetitionCount++;
	
	// устанавливаем факт тревоги (во флеш)
	// готовимся отправить посылку о тревоге
	// отключаем счет времени до тревоги
	TM_Timer_Cmd(TM_ALARM_TIMEOUT, DISABLE);
};

void hKeyReadingResumed(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_READ_KEY, ENABLE);
	IndicationStart(AlarmCommon);
};

void hDoorClosed(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_READ_KEY, DISABLE); 
	IndicationStop();
};

// таблица состояний - FSMTable[кол-во состояний][кол-во событий]
Transition_t FSMTable[4][6] =
{
    [sDoorIsClosed][eDoorOpened] 				= { sDoorIsOpenedAlarmOn, hDoorOpened },
	[sDoorIsClosed][eEnteredValidKey] 			= {	sDoorIsClosed,  0 },
	[sDoorIsClosed][eEnteredInvalidKey] 		= { sDoorIsClosed,  0 },
	[sDoorIsClosed][eIndicationEnded] 			= { sDoorIsClosed,  0 },
	[sDoorIsClosed][eAlarmTimeout] 				= { sDoorIsClosed,  hAlarmTimeout },
	[sDoorIsClosed][eDoorClosed] 				= { sDoorIsClosed,  0 },
	
	[sDoorIsOpenedAlarmOn][eDoorOpened] 		= { sDoorIsOpenedAlarmOn, 0 },
	[sDoorIsOpenedAlarmOn][eEnteredValidKey] 	= { sDoorIsOpenedAlarmOff, hEnteredValidKey }, 
	[sDoorIsOpenedAlarmOn][eEnteredInvalidKey] 	= { sKeyReadingSuspended, hEnteredInvalidKey },
	[sDoorIsOpenedAlarmOn][eIndicationEnded] 	= { sDoorIsOpenedAlarmOn, 0 },
	[sDoorIsOpenedAlarmOn][eAlarmTimeout] 		= { sDoorIsOpenedAlarmOn, hAlarmTimeout }, 
	[sDoorIsOpenedAlarmOn][eDoorClosed] 		= { sDoorIsClosed, hDoorClosed },
	
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
};

// что сделать с лучае, если события произошли почти одновременно, не успев обработаться? 
// очередь событий? скорее игнорировать опоздавшего? мб это не страшно, если вся таблица переходов будет прописана

void HandleEvent()
{
	Event_t newEvent = getEvent();
	if (newEvent != eNoEvent)
	{
		URT_PrintString("Event: ");
		URT_Write(newEvent + '0');
		URT_PrintString("\r\n");
		URT_PrintString("CurState: ");
		URT_Write(currentState + '0');
		URT_PrintString("\r\n");
		
		// реакция на событие в зависимости от текущего состояния
		TransitionCallback_t worker = FSMTable[currentState][newEvent].worker;
		if (worker)
		{
			worker(currentState, newEvent);
		}
		
		currentState = FSMTable[currentState][newEvent].newState; // переходим в новое состояние
		
		URT_PrintString("NewState: ");
		URT_Write(currentState + '0');
		URT_PrintString("\r\n");
		URT_PrintString("*********");
		URT_PrintString("\r\n");
	}
}

uint8_t IsKeyActive(void)
{
	// зашифровываем ключ в MD5
	MD5_MakeHash(KeyRaw, KEY_RAW_SIZE, KeyEncrypted);
	
	// Проверяем наличие ключа в базе (зашифрованного). Только среди активированных
	for (uint16_t keyIndex = 0; keyIndex < TotalKeys.value /*KEYS_COUNT*/; keyIndex++)
    {
		if (IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, keyIndex) == KEY_STATUS_ACTIVATED)
		{
			//if(IAP_IsEqualToRAM(PAGE_NUMBER_KEYS_0 * IAP_PAGE_SIZE + keyIndex * KEY_ENCRYPTED_SIZE, KeyRaw, KEY_RAW_SIZE))
			if (IAP_IsEqualToRAM(PAGE_NUMBER_KEYS_0 * IAP_PAGE_SIZE + keyIndex * KEY_ENCRYPTED_SIZE, KeyEncrypted, KEY_ENCRYPTED_SIZE))
			{
				return KEY_STATUS_ACTIVATED;
			}
		}
    }
	return KEY_STATUS_DEACTIVATED;
}







