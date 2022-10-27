#ifndef SKUD_H
#define SKUD_H

#include "keys.h"

typedef enum {
	StateClosed = 0x00,
	StateOpenedAlarm = 0x01,
	StateOpenedValidOk = 0x02,
	StateOpenedValidNotOk = 0x03,
	StateOpenedAlarmTimeout = 0x04,
} State;

typedef enum {
	EventNull = 0x00,
	EventOpened = 0x01,
	EventValidKey = 0x02,
	EventNotValidKey = 0x03,
	EventTimeout = 0x04,
	EventReadyForNewKey = 0x05,
	EventReactivateAlarm = 0x06,
} Event;


typedef enum {
	NoRing,
	LongRing,
	MediumRing,
	FastRing,
	FastFastRing,
} RingType;

extern uint8_t CurState;
extern uint8_t CurEvent;

extern uint32_t alarmTimeoutCnt;
extern uint32_t alarmTimeoutCntMax;

extern uint32_t alarmReloadCnt;
extern uint32_t alarmReloadCntMax;

extern uint32_t buzzerFreq;
extern uint32_t buzzerCnt;

extern boolean alarmAuto;

extern uint8_t piskNumCnt;
extern uint32_t piskNumMax;

extern boolean waitBitch;
extern uint32_t waitBitchCnt;
extern uint32_t waitBitchMax;

void StartRing(uint8_t rtype, uint32_t duration_ms);
void StopRing(void);
void MonitorKey(void);
uint8_t GetCurEvent (void);
#endif // SKUD_H