#include "events.h"

Event_t eventDoor = { SCODE_EVENT_DOOR, 0, 0, 0, 0, 0 };
Event_t eventAccess = { SCODE_EVENT_ACCESS, 0, 0, 0, 0, 0 };
Event_t eventAlarm = { SCODE_EVENT_ALARM, 0, 0, 0, 0, 0 };

Event_t *events[3] = { &eventDoor, &eventAccess, &eventAlarm };