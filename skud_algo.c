#include "skud_algo.h"


State_t currentState = sNoAccessSleep;

volatile uint8_t indicWaitCnt = 0;
volatile uint8_t indicWaitMax = INDIC_WAIT_MAX;
volatile uint32_t indicTimeCnt = 1;
volatile uint32_t indicTimeMax = INDIC_CNT_ALARM;
volatile uint8_t indicSpeed = INDIC_SPEED_ALARM;
volatile uint8_t buzzerMuted = 0;
volatile uint8_t indicationPhase = 1;

volatile uint32_t alarmTimeoutCnt = 0;
volatile uint32_t alarmTimeoutMax = ALARM_TIMEOUT_MAX;

volatile uint8_t gerkonFilterCnt = 0;
volatile uint8_t gerkonFilterMax = 20;
volatile uint8_t oldGerkonState = 0;
volatile uint8_t gerkonState = 0;

volatile uint16_t protectionDelayCnt = 0;
volatile uint16_t protectionDelayMax = PROTECTION_DELAY_MAX;

void IndicationStart(Indication_t indicType)
{
	BUZZER_OFF();
	STALED_OFF();
	indicTimeCnt = 1;
	indicWaitCnt = 0;
	indicationPhase = 1;
	
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
	
		default: 
			return;	
	}

	TM_Timer_Cmd(TM_INDICATION, ENABLE);
}

void IndicationStop()
{
//	TM_Timer_Cmd(TM_INDICATION, DISABLE);
	BUZZER_OFF();
	STALED_OFF();
	buzzerMuted = 0;
	indicTimeCnt = 1;
	indicationPhase = 1;
};

void AlarmCountdownEnable() // -static inline
{
	TM_Timer_Cmd(TM_ALARM_TIMEOUT, ENABLE); 
}

void AlarmCountdownDisable()
{
	TM_Timer_Cmd(TM_ALARM_TIMEOUT, DISABLE); 
	alarmTimeoutCnt = 0;
}

void ReadingKeyEnable()
{
	TM_Timer_Cmd(TM_READ_KEY, ENABLE); 
}

void ReadingKeyDisable()
{
	TM_Timer_Cmd(TM_READ_KEY, DISABLE); 
	OneWire_SetDirection(PINX_Mode_Digital_I);  // 1-wire на вход (на всякий случай)
}

void ProtectionDelayEnable()
{
	TM_Timer_Cmd(TM_PROTECTION_DELAY, ENABLE); 
};

void MuteBuzzer()
{
	buzzerMuted = TRUE;
	BUZZER_OFF();
}

void UnmuteBuzzer()
{
	BACKL_PIN = !indicationPhase;
	buzzerMuted = FALSE;
}

// h - handler
/* **************************** */

void hSleepToWaiting(State_t state, Event_t event)
{
	// ... // отправляем сигнал об открытии двери
	AlarmCountdownEnable(); // отсчет до тревоги запущен
	ReadingKeyEnable(); // чтение ключей начато
	IndicationStart(AlarmCommon); // начинаем проигрывать сигнал, требуя ввести ключ
}

void hWaitingToAccess(State_t state, Event_t event)
{
	AlarmCountdownDisable(); // отсчет до тревоги остановлен
	ReadingKeyDisable(); // чтение ключей остановлено
	ProtectionDelayEnable(); // чтение ключей остановлено
	IndicationStart(ValidKey); // прогрываем сигнал верного ключа
}

void hAccessToSleep(State_t state, Event_t event)
{
	oldGerkonState = 0; // в случае, если дверь открыта, то это приведет к тревоге
}

// логика разрешения чтения ключей жестко связана с логикой индикации, но здесь это оправдано
void hReadingKeySuspend(State_t state, Event_t event)
{
	ReadingKeyDisable(); // прекращаем чтение ключа на интервал времени
	IndicationStart(InvalidKey); // прогрываем сигнал неверного ключа
}

void hReadingKeyResume(State_t state, Event_t event)
{	
	if (gerkonState == 1) ReadingKeyEnable(); // если дверь открыта, то возобновляем чтение ключа
	IndicationStart(AlarmCommon); // если дверь открыта, то возобновляем чтение ключа
}

void hDoorClosedNoAccess(State_t state, Event_t event)
{	
	ReadingKeyDisable(); // прекращаем чтение ключа пока дверь не откроют
	MuteBuzzer(); // оставляем только световую индикацию
}

void hDoorOpenedNoAccess(State_t state, Event_t event)
{
	ReadingKeyEnable(); // возобновляем чтение ключа
	UnmuteBuzzer(); // опять включаем звук в дополнение к световой индикации
	
	// возможно опять вкл.
}

void hSendAlarmEvent(State_t state, Event_t event)
{
	MuteBuzzer(); // если закрыть и открыть опять дверь, то бесконечно опять будет пищать
	// доработать
	
}

void hIndicationStop(State_t state, Event_t event)
{
	IndicationStop();
}

void hParseBusMessage(State_t state, Event_t event)
{
	Bus_ParseMessage();
}

// 	таблица состояний - FSMTable[кол-во состояний][кол-во событий] =
// 	[текущее состояние][возникшее событие] 		= { новое состояние, функция-обработчик }

Transition_t FSMTable[3][8] =
{
	[sNoAccessSleep][eDoorOpened] 				= { sNoAccessWaitingKey, hSleepToWaiting },
	[sNoAccessSleep][eDoorClosed] 				= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eEnteredValidKey] 			= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eEnteredInvalidKey] 		= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eAlarmTimeout] 			= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eProtectionRestored] 		= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eIndicationEnded] 			= { sNoAccessSleep, NULL },
	[sNoAccessSleep][eBusMessage] 				= { sNoAccessSleep, hParseBusMessage },
	
	[sNoAccessWaitingKey][eDoorOpened] 			= { sNoAccessWaitingKey, hDoorOpenedNoAccess },
	[sNoAccessWaitingKey][eDoorClosed] 			= { sNoAccessWaitingKey, hDoorClosedNoAccess },
	[sNoAccessWaitingKey][eEnteredValidKey] 	= { sAccessGiven, hWaitingToAccess },
	[sNoAccessWaitingKey][eEnteredInvalidKey] 	= { sNoAccessWaitingKey, hReadingKeySuspend },
	[sNoAccessWaitingKey][eAlarmTimeout] 		= { sNoAccessWaitingKey, hSendAlarmEvent },
	[sNoAccessWaitingKey][eProtectionRestored] 	= { sNoAccessWaitingKey, NULL }, 
	[sNoAccessWaitingKey][eIndicationEnded] 	= { sNoAccessWaitingKey, hReadingKeyResume },
	[sNoAccessWaitingKey][eBusMessage] 			= { sNoAccessWaitingKey, hParseBusMessage },
		
	[sAccessGiven][eDoorOpened] 				= { sAccessGiven, NULL },
	[sAccessGiven][eDoorClosed] 				= { sAccessGiven, NULL },
	[sAccessGiven][eEnteredValidKey] 			= { sAccessGiven, NULL },
	[sAccessGiven][eEnteredInvalidKey] 			= { sAccessGiven, NULL },
	[sAccessGiven][eAlarmTimeout] 				= { sAccessGiven, NULL },
	[sAccessGiven][eProtectionRestored] 		= { sNoAccessSleep, hAccessToSleep },
	[sAccessGiven][eIndicationEnded] 			= { sAccessGiven, hIndicationStop },
	[sAccessGiven][eBusMessage] 				= { sAccessGiven, hParseBusMessage },
	// если один аларм сработал, и дверь после этого закрыта,  то перейти в сон?
	// если один аларм сработал, и дверь открыта, то состояние не меняем, но ?
};

// буфер событий предотвращает потерю информации о переходе к другому состоянию 

void HandleEvent()
{
	Event_t newEvent = getEvent(); // получаем новый ивент из буфера
	if (newEvent != eNoEvent)
	{
//		URT_PrintString("Event: ");
//		URT_Write(newEvent + '0');
//		URT_PrintString("\r\n");
//		URT_PrintString("CurState: ");
//		URT_Write(currentState + '0');
//		URT_PrintString("\r\n");
		
		// реакция на событие в зависимости от текущего состояния
		// почему это работает?
		TransitionCallback_t worker = FSMTable[currentState][newEvent].worker;
		if (worker != NULL)
		{
			worker(currentState, newEvent);
		}
		
		currentState = FSMTable[currentState][newEvent].newState; // переходим в новое состояние
		
//		URT_PrintString("NewState: ");
//		URT_Write(currentState + '0');
//		URT_PrintString("\r\n");
//		URT_PrintString("*********");
//		URT_PrintString("\r\n");
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