#ifndef SKUD_ALGO_H
#define SKUD_ALGO_H
#include "stdint.h"

	
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
} States_t; 

// e - event
typedef enum 
{
	eDoorOpened = 0,
	eEnteredValidKey = 1,
	eEnteredInvalidKey = 2,
	eIndicationEnded = 3,
	eAlarmTimeout = 4,
	eDoorClosed = 5,
} Events_t;

typedef struct {
	Events_t qu[MAX_EVENTS_NUM];
	uint8_t front;
	uint8_t rear;
} Events_queue_t;


typedef void (*TransitionCallback_t)(States_t state, Events_t event);

typedef struct
{
    States_t newState;
    TransitionCallback_t worker;
} Transition_t;

extern States_t currentState;
extern Events_t currentEvent;
extern Events_t newEvent;


// h - handler
void hDoorOpened(States_t state, Events_t event);
void hEnteredValidKey(States_t state, Events_t event);
void hEnteredInvalidKey(States_t state, Events_t event);
void hAlarmTimeout(States_t state, Events_t event);
void hKeyReadingResumed(States_t state, Events_t event);
void hDoorClosed(States_t state, Events_t event);

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

extern uint8_t indicWaitCnt;
extern uint8_t indicWaitMax;
extern uint32_t indicTimeCnt;
extern uint32_t indicTimeMax;
extern uint8_t indicSpeed;
extern uint8_t onlyLed;

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

uint8_t IsKeyActive(void);

#endif // SKUD_ALGO_H