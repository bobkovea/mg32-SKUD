#include "skud_algo.h"

State_t currentState;

volatile uint8_t indicWaitCnt = 0;
volatile uint8_t indicWaitMax = INDIC_WAIT_MAX;
volatile uint32_t indicTimeCnt = 1;
volatile uint32_t indicTimeMax = INDIC_CNT_ALARM;
volatile uint8_t indicSpeed = INDIC_SPEED_ALARM;
volatile uint8_t buzzerIsMuted = 0;
volatile uint8_t indicationPhase = 1;

volatile uint32_t muteTimeoutCnt = 0;
volatile uint32_t muteTimeoutMax = MUTE_SOUND_MAX;

volatile uint32_t gerkonFilterCnt = 0;
volatile uint32_t gerkonFilterMax = GERKON_FILTER_MAX;
volatile uint8_t doorIsOpened = 0;

volatile uint32_t protectionDelayCnt = 0;
volatile uint32_t protectionDelayMax = PROTECTION_DELAY_MAX;

void ProvideAccessForever();
void ProtectionDelayEnable(); 

// Реакция на изменение значения переменной по протоколу
void SetVariableCallback(uint8_t varNumber)
{
	/* Перевод передаваемых величин во внутренние переменные таймеров */
	switch (varNumber)
	{
		case 0x00:
		gerkonFilterMax = GerkonFiltTime.value / 5; // т.к. период таймера = 5 мс и ед.изм. - мс
		break;
		
		case 0x01:
		protectionDelayMax = ProtectionDelayTime.value * 60000 / 5; // т.к. период таймера = 5 мс и ед.изм. - мин	
		break;
		
		case 0x02:
		muteTimeoutMax = BuzzerOffTime.value * 60000 / 100; // т.к. период таймера = 100 мс и ед.изм. - мин	
		break;
					
		case 0x03:
		if (CheckKeyDisabled.value)
			ProvideAccessForever();
		else 
			ProtectionDelayEnable(); 
		break;
	}
}
	
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
	TM_Timer_Cmd(TM_INDICATION, DISABLE);
	BUZZER_OFF();
	STALED_OFF();
	buzzerIsMuted = 0;
	indicTimeCnt = 1;
	indicationPhase = 1;
};

void MuteBuzzerCountdownEnable()
{
	muteTimeoutCnt = 0;
	TM_Timer_Cmd(TM_MUTE_SOUND, ENABLE); 
}

void MuteBuzzerCountdownDisable()
{
	TM_Timer_Cmd(TM_MUTE_SOUND, DISABLE); 
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

void ProtectionDelayDisable()
{
	TM_Timer_Cmd(TM_PROTECTION_DELAY, DISABLE); 
};

void MuteBuzzer()
{
	buzzerIsMuted = TRUE;
	BUZZER_OFF();
}

void UnmuteBuzzer()
{
	BACKL_PIN = !indicationPhase; // изменить BACKL_PIN
	buzzerIsMuted = FALSE;
}

void DefineInitialState()
{
	if (CheckKeyDisabled.value) // если включен режим доступа без ключа
	{ 
		currentState = sAccessGiven; // переходим в состояние доступа до выключения режима доступа без ключа
	}
	
	else if (AccessIsGiven.value) // если до этого был введен верный ключ
	{
		currentState = sAccessGiven; // переходим в состояние доступа
		ProtectionDelayEnable(); // и запускаем отсчет времени доступа
	}
	else
	{
		currentState = sNoAccessSleep; // переходим в состояние сна (нормальная ситуация)
	}
}

void ProvideAccessForever()
{
	IndicationStop();
	ReadingKeyDisable();
	ProtectionDelayDisable(); 
	MuteBuzzerCountdownDisable();
	currentState = sAccessGiven; // переходим 
}

// h - handler
/* **************************** */

// переход из состояния сна в состояние ожидания ввода ключа
void hSleepToWaiting(State_t state, Event_t event)
{
	MuteBuzzerCountdownEnable(); // отсчет до заглушения индикации начат
	ReadingKeyEnable(); // чтение ключей начато
	IndicationStart(AlarmCommon); // начинаем проигрывать сигнал, требуя ввести ключ
}

// переход из состояния ожидания ввода ключа в состояние после ввода верного ключа
void hWaitingToAccess(State_t state, Event_t event)
{
	AccessIsGiven.value = 1; // запоминаем, что доступ был выдан
	ValidKeyIndex.value = CurKeyIndex; // запоминаем индекс открывшего ключа
	API_CopyVariablesPage0ToFlash();  // обновляем первую страницу флеша с переменными
	
	ReadingKeyDisable(); // чтение ключей остановлено
	ProtectionDelayEnable(); // запускаем отсчет времени доступа
	
	MuteBuzzerCountdownDisable(); // отсчет до заглушения индикации остановлен
	UnmuteBuzzer(); // включаем пищалку, если вдруг звук был заглушен по таймеру
	IndicationStart(ValidKey); // проигрываем сигнал верного ключа
}
// переход из состояния после ввода верного ключа в состояние сна
void hAccessToSleep(State_t state, Event_t event)
{
	AccessIsGiven.value = 0; // запоминаем, что доступ закончился
	API_CopyVariablesPage0ToFlash();
	// если дверь открыта, то сразу тревога
	if (doorIsOpened)
		putEvent(eDoorOpened);		
}

// логика разрешения чтения ключей жестко связана с логикой индикации, но здесь это оправдано
void hReadingKeySuspend(State_t state, Event_t event)
{
	ReadingKeyDisable(); // прекращаем чтение ключа на время проигрывания индикации
	
	UnmuteBuzzer(); // если вдруг звук заглушен по таймеру, то включаем вновь
	MuteBuzzerCountdownEnable(); // запускаем отсчет заглушения пищалки
	IndicationStart(InvalidKey); // прогрываем сигнал неверного ключа
}

void hReadingKeyResume(State_t state, Event_t event)
{	
	if (doorIsOpened == 1) ReadingKeyEnable(); // если дверь открыта, то возобновляем чтение ключа
	IndicationStart(AlarmCommon); // если дверь открыта, то возобновляем чтение ключа
}

void hDoorClosedNoAccess(State_t state, Event_t event)
{	
	ReadingKeyDisable(); // прекращаем чтение ключа пока дверь вновь не откроют
	
	MuteBuzzerCountdownDisable(); // дверь закрылась раньше таймера - убираем отсчет заглушения пищалки
	MuteBuzzer(); // оставляем только световую индикацию
}

void hDoorOpenedNoAccess(State_t state, Event_t event)
{
	ReadingKeyEnable(); // возобновляем чтение ключа
	
	UnmuteBuzzer(); // опять включаем звук в дополнение к световой индикации
	MuteBuzzerCountdownEnable(); // вновь запускаем отсчет заглушения пищалки
}

void hMuteBuzzer(State_t state, Event_t event)
{
	MuteBuzzer();	
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
	[sNoAccessWaitingKey][eAlarmTimeout] 		= { sNoAccessWaitingKey, hMuteBuzzer },
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
		// реакция на событие в зависимости от текущего состояния
		// почему это работает?
		TransitionCallback_t worker = FSMTable[currentState][newEvent].worker;
		if (worker != NULL)
		{
			worker(currentState, newEvent);
		}
		
		currentState = FSMTable[currentState][newEvent].newState; // переходим в новое состояние

	}
}
