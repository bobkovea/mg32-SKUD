#ifndef EVENTS_H
#define EVENTS_H
#include "MG32x02z__Common_DRV.h"
#include "packages.h"

#define EVENT_COUNT 3

typedef struct
{
	uint8_t eventNum;
	uint8_t repetitionCount;
	uint8_t status;
	uint8_t time;
	uint16_t keyIndex;
} Event_t;

extern Event_t eventDoor;
extern Event_t eventAccess;
extern Event_t eventAlarm;

extern Event_t *events[3];
	



#endif // EVENTS_H