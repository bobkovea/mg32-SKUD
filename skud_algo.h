#ifndef SKUD_ALGO_H
#define SKUD_ALGO_H
#include "stdint.h"
// текущее состояние записывается во флеш (если это связано с тревогой)

#define eNoEvent 0xFF
#define sInitialState 0xFF

// s - state
typedef enum 
{
	sDoorIsClosed = 0,
	sDoorIsOpenedAlarmOn,
	sDoorIsOpenedAlarmOff,
	sKeyReadingSuspended,
} States_t; 

// e - event
typedef enum 
{
	eDoorOpened = 0,
	eEnteredValidKey,
	eEnteredInvalidKey,
	eIndicationEnded,
	eAlarmTimeout,
	eDoorClosed,
} Events_t;

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

extern uint32_t indicTimeCnt;
extern uint32_t indicTimeMax;
extern uint8_t indicSpeed;
extern uint8_t onlyLed;

extern uint8_t gerkonState;

#define INDIC_SPEED_ALARM 10
#define INDIC_SPEED_VALID_KEY 5
#define INDIC_SPEED_INVALID_KEY 3

#define INDIC_CNT_ALARM 0
#define INDIC_CNT_INVALID_KEY 12
#define INDIC_CNT_VALID_KEY 16


uint8_t IsKeyActive(void);

#endif // SKUD_ALGO_H