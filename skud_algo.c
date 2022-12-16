#include "skud_algo.h"
#include "stdint.h"
#include "gpio.h"
#include "timers.h"

States_t currentState = sDoorIsClosed;
Events_t currentEvent = eNoEvent;
Events_t newEvent = eNoEvent;

#define CNT_AlarmCommon 500
#define CNT_ValidKey 250
#define CNT_InvalidKey 100

#define PEEMAX_AlarmCommon -1
#define PEEMAX_ValidKey 4 * 2
#define PEEMAX_InvalidKey 5 * 2

void IndicationStart(Indication_t indicType)
{
//	TM36->CNT.W = 0;
	TM_Timer_Cmd(TM36, DISABLE);
	BUZZER_PIN = 0;
	STALED_PIN = 1;
	peeCnt = 0;
	
	switch ((uint8_t)indicType)
	{
		case AlarmCommon:
			peeMax = PEEMAX_AlarmCommon;
			TM_Counter_Config(TM36, 0, CNT_AlarmCommon);
			TM_Timer_Cmd(TM36, ENABLE);
		break;
		
		case ValidKey:
			peeMax = PEEMAX_ValidKey;
			TM_Counter_Config(TM36, 0, CNT_ValidKey);
			TM_Timer_Cmd(TM36, ENABLE);
			break;
		
		case InvalidKey:
			peeMax = PEEMAX_InvalidKey;
			TM_Counter_Config(TM36, 0, CNT_InvalidKey);
			TM_Timer_Cmd(TM36, ENABLE);
			break;
		
		case OnlyLED:
			onlyLed = 1;
			TM_Counter_Config(TM36, 0, CNT_AlarmCommon);
			break;
		
		default: 
			break;	
	}
}

void IndicationStop()
{
	TM_Timer_Cmd(TM36, DISABLE);
	BUZZER_PIN = 0;
	STALED_PIN = 1;
	// обнуление всяких штук
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
	// прописать потом все случаи во избежание гонки потоков
	
    [sDoorIsClosed][eDoorOpened] = { sDoorIsOpenedAlarmOn, hDoorOpened },
	
	[sDoorIsOpenedAlarmOn][eDoorClosed] = { sDoorIsClosed, hDoorClosed },

	[sDoorIsOpenedAlarmOn][eEnteredInvalidKey] = { sKeyReadingSuspended, hEnteredInvalidKey },
	
	[sDoorIsOpenedAlarmOn][eAlarmTimeout] = { sDoorIsOpenedAlarmOn, hAlarmTimeout },
		
	[sDoorIsOpenedAlarmOn][eEnteredValidKey] = { sDoorIsOpenedAlarmOff, hEnteredValidKey },
	
	[sKeyReadingSuspended][eKeyReadingResumed] = { sDoorIsOpenedAlarmOn, hKeyReadingResumed },
	
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












//#include "gpio.h"
//#include "usart.h"

//volatile uint8_t CurState = StateClosed;
//volatile uint8_t CurEvent = EventNull;

//volatile uint32_t alarmTimeoutCnt = 0;
//volatile uint32_t alarmTimeoutCntMax = 50; // длительность интервала до отправки сигнала аларма (cек * 10)

//volatile uint32_t alarmReloadCnt = 0;
//volatile uint32_t alarmReloadCntMax = 50; // длительность интервала до автоматической активации сигналки после её снятия (cек * 10)

////boolean waitBitch = FALSE;
//volatile uint32_t waitBitchCnt = 0;
//volatile uint32_t waitBitchCntMax = 20; // длительность интервала до разрешения повторного поднесения ключа (cек * 10)

//volatile uint32_t buzzerFreq = UINT32_MAX; // период следования "писков" зумера (сек / 100)
//volatile uint32_t buzzerCnt = 1;

//volatile uint8_t piskNumCnt = 0;
//volatile uint32_t piskNumMax = UINT16_MAX; // количество "писков" зумера

//uint8_t GetCurEvent (void)
//{
//	uint8_t tmp = CurEvent;
//	CurEvent = EventNull;
//	return tmp;
//};



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



