#ifndef EVENTS_H
#define EVENTS_H
#include "stdint.h"
#include "packages.h"
#include "keys.h"

#define EVENT_COUNT 3

typedef struct
{
	uint8_t eventNum; // идентификатор события
	uint8_t repetitionCount; // количество повторений события
	uint8_t status; // актуальный/неактуальный
	uint8_t time; // время
	uint16_t keyIndex; // индекс снявшего сигнализацию ключа (для соотв. события)
} MainEvent_t;

extern volatile MainEvent_t eventDoor;
extern volatile MainEvent_t eventAccess;
extern volatile MainEvent_t eventAlarm;

extern volatile MainEvent_t *events[3];




#endif // EVENTS_H