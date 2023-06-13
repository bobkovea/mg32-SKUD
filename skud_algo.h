#ifndef SKUD_ALGO_H
#define SKUD_ALGO_H
#include "stdint.h"
#include "buffer.h"
	
// текущее состояние записывается во флеш (если это связано с тревогой)
#define eNoEvent 0xFF
#define sInitialState 0xFF

#define MAX_EVENTS_NUM 5

// s - state
typedef enum 
{
	sDoorIsClosed = 0,
	sDoorIsOpenedAlarmOn = 1,
	sDoorIsOpenedAlarmOff = 2,
	sKeyReadingSuspended = 3,
} State_t; 

// e - event
typedef enum 
{
	eDoorOpened = 0,
	eEnteredValidKey = 1,
	eEnteredInvalidKey = 2,
	eIndicationEnded = 3,
	eAlarmTimeout = 4,
	eDoorClosed = 5,
} Event_t;

typedef void (*TransitionCallback_t)(State_t state, Event_t event);

typedef struct
{
    State_t newState;
    TransitionCallback_t worker;
} Transition_t;

extern State_t currentState;
extern Event_t currentEvent;
extern Event_t newEvent;


// h - handler
void hDoorOpened(State_t state, Event_t event);
void hEnteredValidKey(State_t state, Event_t event);
void hEnteredInvalidKey(State_t state, Event_t event);
void hAlarmTimeout(State_t state, Event_t event);
void hKeyReadingResumed(State_t state, Event_t event);
void hDoorClosedAlarmOn(State_t state, Event_t event);
void hDoorClosedAlarmOff(State_t state, Event_t event);
void HandleEvent();

typedef enum
{
	AlarmCommon,
	ValidKey,
	InvalidKey,
	OnlyLED
} Indication_t;

void IndicationStart(Indication_t indicType);
void IndicationStop();

extern volatile uint8_t indicWaitCnt;
extern volatile uint8_t indicWaitMax;
extern volatile uint32_t indicTimeCnt;
extern volatile uint32_t indicTimeMax;
extern volatile uint8_t indicSpeed;
extern volatile uint8_t onlyLed;

extern volatile uint32_t alarmTimeoutCnt;
extern volatile uint32_t alarmTimeoutMax;

extern volatile uint8_t gerkonStateFilter;
extern volatile uint8_t gerkonStateFilterMax;
extern volatile uint8_t oldGerkonState;
extern volatile uint8_t gerkonState;

// перерыв в индикации до смены на другой тип индикации
#define INDIC_WAIT_MAX 2 // 200 мс

// желаемое количество писков
#define INDIC_PEECNT_VALID_KEY 4
#define INDIC_PEECNT_INVALID_KEY 3

// интервал между переключениями пищалки
#define INDIC_SPEED_ALARM 6 // 600 мс
#define INDIC_SPEED_VALID_KEY 2 // 200 мс
#define INDIC_SPEED_INVALID_KEY 1 // 100 мс

// расчет макс. значения счетчика для реализации заданных выше величин
#define INDIC_CNT_ALARM UINT32_MAX
#define INDIC_CNT_VALID_KEY (INDIC_PEECNT_VALID_KEY * INDIC_SPEED_VALID_KEY * 2)
#define INDIC_CNT_INVALID_KEY (INDIC_PEECNT_INVALID_KEY * INDIC_SPEED_INVALID_KEY * 2)

#define ALARM_TIMEOUT_MAX 20

uint8_t IsKeyActive(void);

#endif // SKUD_ALGO_H