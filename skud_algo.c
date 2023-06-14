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
volatile uint8_t buzzerOn = 1;

volatile uint32_t alarmTimeoutCnt = 0;
volatile uint32_t alarmTimeoutMax = ALARM_TIMEOUT_MAX;

volatile uint8_t gerkonStateFilter = 0;
volatile uint8_t gerkonStateFilterMax = 20;
volatile uint8_t oldGerkonState = 0;
volatile uint8_t gerkonState = 0;

void IndicationStart(Indication_t indicType)
{
	BUZZER_OFF();
	STALED_OFF();
	indicTimeCnt = 1;
	indicWaitCnt = 0;
	buzzerOn = 1;
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
			buzzerOn = 0;
			indicSpeed = INDIC_SPEED_ALARM;
			indicTimeMax = INDIC_CNT_ALARM;
			break;
	
		default: 
			return;	
	}

	TM_Timer_Cmd(TM_INDICATION, ENABLE);
}

void BuzzerUnmute()
{
	BUZZER_OFF();
}

void BuzzerMute()
{
	BUZZER_ON();
}

void IndicationStop()
{
	// обнуление всяких штук
	TM_Timer_Cmd(TM_INDICATION, DISABLE);
	BUZZER_OFF();
	STALED_OFF();
	buzzerOn = 1;
	indicTimeCnt = 1;
};

// h - handler
void hDoorOpened(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_ALARM_TIMEOUT, ENABLE); 
	TM_Timer_Cmd(TM_READ_KEY, ENABLE); 
	if (buzzerOn == 0) buzzerOn = 1;
	else IndicationStart(AlarmCommon);
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

void hDoorClosedAlarmOff(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_READ_KEY, DISABLE); 
	IndicationStop();
};

void hDoorClosedAlarmOn(State_t state, Event_t event)
{
	TM_Timer_Cmd(TM_READ_KEY, DISABLE); 
	BUZZER_OFF();
	buzzerOn = 0;
//	
//	IndicationStart(OnlyLED);
};

void hProtectionRestored(State_t state, Event_t event)
{
	oldGerkonState = 1;
};

// чтобы синъронизировать мигание и пищалку нужно прочитать состояние светодиода

// [текущее состояние][возникшее событие] 		= { новое состояние, функция-обработчик }

void hSleepToWaiting(State_t state, Event_t event)
{
	AlarmTimerEnable();
	ReadingKeyEnable();
//	TM_Timer_Cmd(TM_ALARM_TIMEOUT, ENABLE); 
//	TM_Timer_Cmd(TM_READ_KEY, ENABLE); 
	IndicationStart(AlarmCommon);
}

void hWaitingToAccess(State_t state, Event_t event)
{
//	TM_Timer_Cmd(TM_ALARM_TIMEOUT, DISABLE);
//	TM_Timer_Cmd(TM_READ_KEY, DISABLE);
//	TM_Timer_Cmd(TM_PROTECTION_DELAY, ENABLE);
	AlarmTimerDisable();
	ReadingKeyDisable();


//	ProtectionDelayEnable();

	IndicationStart(ValidKey);
}

void hAccessToSleep(State_t state, Event_t event)
{
	ProtectionDelayDisable();
}

void hMuteBuzzer(State_t state, Event_t event)
{
	buzzerOn = FALSE;
	BUZZER_OFF();
}

void hUnmuteBuzzer(State_t state, Event_t event)
{
	BUZZER_PIN = indicationPhase; // развить идею с фазой индикации (зависимость пищания не от состояния пинов, а от состояния переменной - 0/1)
	buzzerOn = TRUE;
}

// логика разрешения чтения ключей жестко связана с логикой индикации, но здесь это оправдано
void hReadingKeySuspend(State_t state, Event_t event)
{
	ReadingKeyDisable();
	IndicationStart(InvalidKey);
}

void hSendAlarmEvent(State_t state, Event_t event)
{
	
}

Transition_t FSMTable[3][6] =
{
	[sNoAccessSleep][eDoorOpened] 				= { sNoAccessWaitingKey, hSleepToWaiting },
	[sNoAccessSleep][eDoorClosed] 				= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eEnteredValidKey] 			= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eEnteredInvalidKey] 		= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eAlarmTimeout] 			= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eProtectionRestored] 		= { sNoAccessSleep, NULL },
	
	[sNoAccessWaitingKey][eDoorOpened] 			= { sNoAccessWaitingKey, NULL /*hUnmuteBuzzer*/ },
	[sNoAccessWaitingKey][eDoorClosed] 			= { sNoAccessWaitingKey, hMuteBuzzer },
	[sNoAccessWaitingKey][eEnteredValidKey] 	= { sAccessGiven, hWaitingToAccess },
	[sNoAccessWaitingKey][eEnteredInvalidKey] 	= { sNoAccessWaitingKey, hReadingKeySuspend },
	[sNoAccessWaitingKey][eAlarmTimeout] 		= { sNoAccessWaitingKey, hSendAlarmEvent },
	[sNoAccessWaitingKey][eProtectionRestored] 	= { sNoAccessWaitingKey, NULL }, 
	
	// если один аларм сработал, и дверь после этого закрыта,  то перейти в сон?
	// если один аларм сработал, и дверь открыта, то состояние не меняем, но ?
	
	[sAccessGiven][eDoorOpened] 				= { sNoAccessWaitingKey, NULL },
	[sAccessGiven][eDoorClosed] 				= { sNoAccessWaitingKey, NULL },
	[sAccessGiven][eEnteredValidKey] 			= { sAccessGiven, NULL },
	[sAccessGiven][eEnteredInvalidKey] 			= { sNoAccessWaitingKey, NULL },
	[sAccessGiven][eAlarmTimeout] 				= { sNoAccessWaitingKey, NULL },
	[sAccessGiven][eProtectionRestored] 		= { sNoAccessSleep, hAccessToSleep },
}	

// таблица состояний - FSMTable[кол-во состояний][кол-во событий]
Transition_t FSMTable[4][7] =
{
    [sDoorIsClosed][eDoorOpened] 				= { sDoorIsOpened, hDoorOpened }, // дверь открыли
	[sDoorIsClosed][eEnteredValidKey] 			= {	sDoorIsClosed,  NULL },
	[sDoorIsClosed][eEnteredInvalidKey] 		= { sDoorIsClosed,  NULL },
	[sDoorIsClosed][eIndicationEnded] 			= { sDoorIsClosed,  NULL },
	[sDoorIsClosed][eAlarmTimeout] 				= { sDoorIsClosed,  hAlarmTimeout }, // истек таймаут ввода ключа после закрытия двери
	[sDoorIsClosed][eDoorClosed] 				= { sDoorIsClosed,  NULL },
	
	[sDoorIsOpened][eDoorOpened] 				= { sDoorIsOpened, NULL },
	[sDoorIsOpened][eEnteredValidKey] 			= { sAccessGiven, hEnteredValidKey }, // введен верный ключ 
	[sDoorIsOpened][eEnteredInvalidKey] 		= { sKeyReadingSuspended, hEnteredInvalidKey }, // введен неверный ключ
	[sDoorIsOpened][eIndicationEnded] 			= { sDoorIsOpened, NULL },
	[sDoorIsOpened][eAlarmTimeout] 				= { sDoorIsOpened, hAlarmTimeout }, // истек таймаут ввода ключа
	[sDoorIsOpened][eDoorClosed] 				= { sDoorIsClosed, hDoorClosedAlarmOn }, // дверь закрыли, не введя ключ
	[sDoorIsOpened][eProtectionRestored] 		= { sDoorIsOpened, NULL }, // дверь закрыли, не введя ключ
	
	[sKeyReadingSuspended][eDoorOpened] 		= { sKeyReadingSuspended, NULL },
	[sKeyReadingSuspended][eEnteredValidKey] 	= { sKeyReadingSuspended, NULL },
	[sKeyReadingSuspended][eEnteredInvalidKey] 	= { sKeyReadingSuspended, NULL }, 
	[sKeyReadingSuspended][eIndicationEnded] 	= { sDoorIsOpened, hKeyReadingResumed }, // разрешаем повторное чтение ключа
	[sKeyReadingSuspended][eAlarmTimeout] 		= { sKeyReadingSuspended, hAlarmTimeout }, // таймаут истек во время индикации ввода ключа
	[sKeyReadingSuspended][eDoorClosed] 		= { sDoorIsClosed, hDoorClosedAlarmOn }, // закрыли шкаф во время индикации ввода ключа
	[sKeyReadingSuspended][eProtectionRestored] = { sKeyReadingSuspended,  NULL },
	
	[sAccessGiven][eDoorOpened] 				= { sAccessGiven, NULL },
	[sAccessGiven][eEnteredValidKey] 			= { sAccessGiven, NULL },
	[sAccessGiven][eEnteredInvalidKey] 			= { sAccessGiven, NULL },
	[sAccessGiven][eIndicationEnded] 			= { sAccessGiven, NULL }, 
	[sAccessGiven][eAlarmTimeout] 				= { sAccessGiven, NULL },
	[sAccessGiven][eDoorClosed] 				= { sAccessGiven, NULL /*hDoorClosedAlarmOff*/ }, // закрыли дверь после ввода верного ключа
	[sAccessGiven][eProtectionRestored] 		= { sDoorIsClosed,  hProtectionRestored },
	// сделать чтобы не сразу ставилась сигналка после закрытия двери
};

// буфер событий предотвращает потерю информации о переходе к другому состоянию 

void HandleEvent()
{
	Event_t newEvent = getEvent(); // получаем новый ивент из буфера
	if (newEvent != eNoEvent)
	{
		URT_PrintString("Event: ");
		URT_Write(newEvent + '0');
		URT_PrintString("\r\n");
		URT_PrintString("CurState: ");
		URT_Write(currentState + '0');
		URT_PrintString("\r\n");
		
		// реакция на событие в зависимости от текущего состояния
		// почему это работает?
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