#ifndef SKUD_ALGO_H
#define SKUD_ALGO_H

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

extern volatile uint8_t CurState;
extern volatile uint8_t CurEvent;

extern volatile uint32_t alarmTimeoutCnt;
extern volatile uint32_t alarmTimeoutCntMax;

extern volatile uint32_t alarmReloadCnt;
extern volatile uint32_t alarmReloadCntMax;

extern volatile uint32_t buzzerFreq;
extern volatile uint32_t buzzerCnt;

//extern boolean alarmAuto;

extern volatile uint8_t piskNumCnt;
extern volatile uint32_t piskNumMax;

extern volatile boolean waitBitch;
extern volatile uint32_t waitBitchCnt;
extern volatile uint32_t waitBitchCntMax;

//void StartRing(uint8_t rtype, uint32_t duration_ms);
//void StopRing(void);
void MonitorKey(void);
uint8_t GetCurEvent (void);
#endif // SKUD_ALGO_H