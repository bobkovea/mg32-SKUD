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
	eDoorOpened,
	eEnteredValidKey,
	eEnteredInvalidKey,
	eIndicationEnds,
	eAlarmTimeout,
	eDoorClosed,
} Events_t;

typedef void (*TransitionCallback_t)(States_t state, Events_t event);

typedef struct
{
    States_t newState;
    TransitionCallback_t worker;
} Transition_t;

States_t currentState;
extern Events_t currentEvent;
Events_t newEvent;

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

extern uint8_t peeCnt;
extern int8_t peeMax;
extern uint8_t onlyLed;












#endif // SKUD_ALGO_H










//#include "keys.h"

//typedef enum {
//	StateClosed = 0x00,
//	StateOpenedAlarm = 0x01,
//	StateOpenedValidOk = 0x02,
//	StateOpenedValidNotOk = 0x03,
//	StateOpenedAlarmTimeout = 0x04,
//} State;

//typedef enum {
//	EventNull = 0x00,
//	EventOpened = 0x01,
//	EventValidKey = 0x02,
//	EventNotValidKey = 0x03,
//	EventTimeout = 0x04,
//	EventReadyForNewKey = 0x05,
//	EventReactivateAlarm = 0x06,
//} Event;


//typedef enum {
//	NoRing,
//	LongRing,
//	MediumRing,
//	FastRing,
//	FastFastRing,
//} RingType;

//extern volatile uint8_t CurState;
//extern volatile uint8_t CurEvent;

//extern volatile uint32_t alarmTimeoutCnt;
//extern volatile uint32_t alarmTimeoutCntMax;

//extern volatile uint32_t alarmReloadCnt;
//extern volatile uint32_t alarmReloadCntMax;

//extern volatile uint32_t buzzerFreq;
//extern volatile uint32_t buzzerCnt;

////extern boolean alarmAuto;

//extern volatile uint8_t piskNumCnt;
//extern volatile uint32_t piskNumMax;

//extern volatile boolean waitBitch;
//extern volatile uint32_t waitBitchCnt;
//extern volatile uint32_t waitBitchCntMax;

////void StartRing(uint8_t rtype, uint32_t duration_ms);
////void StopRing(void);
//void MonitorKey(void);
//uint8_t GetCurEvent (void);
