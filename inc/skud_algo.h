#ifndef SKUD_ALGO_H
#define SKUD_ALGO_H

#include "stdint.h"
#include "ring_buffer.h"
#include "gpio.h"
#include "timers.h"
#include "keys.h"
#include "variables.h"
#include "bus.h"
#include "api.h"
#include "onewire.h"

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
#define MUTE_SOUND_MAX 20 // 2 сек
#define PROTECTION_DELAY_MAX 4000 // 20 сек

// типы индикации
typedef enum
{
	AlarmCommon, // тип индикации: обычная  
	ValidKey, // тип индикации: введен верный ключ
	InvalidKey, // тип индикации: введен неверный ключ
} Indication_t;

// s - state, состояния системы
typedef enum 
{
	sNoAccessSleep = 0, // состояние сна: ждем открытие двери шкафа
	sNoAccessWaitingKey = 1, // состояние ожидания ввода ключа: работает индикация
	sAccessGiven = 2, // состояние снятой сигнализации
} State_t; 

// e - event, события системы
typedef enum 
{
	eDoorOpened = 0, // событие: дверь открылась
	eEnteredValidKey = 1, // событие: введен верный ключ
	eEnteredInvalidKey = 2, // событие: введен неверный ключ
	eAlarmTimeout = 3, // событие: время индикации при открытой двери без доступа прошло
	eDoorClosed = 4, // событие: дверь закрылась
	eProtectionRestored = 5, // событие: истекло время доступа введенного ключа
	eIndicationEnded = 6, // событие: цикл индикации завершился
	eBusMessage = 7, // событие: пришла посылка от Контроллера
	eNoEvent = 255 // событие: нет события
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
extern volatile uint8_t buzzerIsMuted;

extern volatile uint32_t muteTimeoutCnt;
extern volatile uint32_t muteTimeoutMax;

extern volatile uint32_t gerkonFilterCnt;
extern volatile uint32_t gerkonFilterMax;
extern volatile uint8_t doorIsOpened;

extern volatile uint32_t protectionDelayCnt;
extern volatile uint32_t protectionDelayMax;

void DefineInitialState(void);
void HandleEvent(void);
void SetVariableCallback(uint8_t varNumber);

uint8_t API_IsRawKeyValid(void); // перенести в другой файл

#endif // SKUD_ALGO_H