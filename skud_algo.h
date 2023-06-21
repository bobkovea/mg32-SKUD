#ifndef SKUD_ALGO_H
#define SKUD_ALGO_H

#include "stdint.h"
#include "ring_buffer.h"
#include "gpio.h"
#include "timers.h"
#include "md5.h"
#include "keys.h"
#include "onewire.h"
#include "variables.h"
#include "bus.h"

// перерыв в индикации до смены на другой тип индикации
#define INDIC_WAIT_MAX 1 // 100 мс

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

#define GERKON_FILTER_MAX 20 // 100 мс
#define ALARM_TIMEOUT_MAX 20 // 2 сек
#define PROTECTION_DELAY_MAX 4000 // 20 сек

// типы индикации
typedef enum
{
	AlarmCommon,
	ValidKey,
	InvalidKey,
} Indication_t;

// s - state, состояния системы
typedef enum 
{
	sNoAccessSleep = 0,
	sNoAccessWaitingKey = 1,
	sAccessGiven = 2,
} State_t; 

// e - event, события системы
typedef enum 
{
	eDoorOpened = 0,
	eEnteredValidKey = 1,
	eEnteredInvalidKey = 2,
	eAlarmTimeout = 3,
	eDoorClosed = 4,
	eProtectionRestored = 5,
	eIndicationEnded = 6,
	eBusMessage = 7,
	eNoEvent = 255
} Event_t;

typedef void (*TransitionCallback_t)(State_t state, Event_t event);

typedef struct
{
    State_t newState;
    TransitionCallback_t worker;
} Transition_t;

extern State_t currentState;

extern volatile uint8_t indicWaitCnt;
extern volatile uint8_t indicWaitMax;
extern volatile uint32_t indicTimeCnt;
extern volatile uint32_t indicTimeMax;
extern volatile uint8_t indicSpeed;
extern volatile uint8_t indicationPhase;
extern volatile uint8_t buzzerMuted;

extern volatile uint32_t alarmTimeoutCnt;
extern volatile uint32_t alarmTimeoutMax;

extern volatile uint32_t gerkonFilterCnt;
extern volatile uint32_t gerkonFilterMax;
extern volatile uint8_t doorIsOpened;

extern volatile uint32_t protectionDelayCnt;
extern volatile uint32_t protectionDelayMax;

void DefineInitialState(void);
void HandleEvent(void);

uint8_t IsKeyValid(void); // перенести в другой файл

#endif // SKUD_ALGO_H