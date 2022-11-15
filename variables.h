#ifndef VARIABLES_H
#define VARIABLES_H
#include "MG32x02z_DRV.h"


#define WRITABLE_VAR_COUNT 7
#define VAR_COUNT 10


// значения по умолчанию
#define __GERKON_FILT_TIME 3
#define __SEND_ALARM_TIME 30
#define __REACTIVATE_ALARM_TIME 5
#define __BUZZER_OFF_TIME 600
#define __SEND_OFFLINE_EVENTS 0
#define __FREE_ACCESS 0
#define __MASTER_SLAVE 0
#define __TOTAL_KEYS 0
#define __ACTIVE_KEYS 0
#define __FLASH_RESOURCE 1
#define __FIRST_WRITE_VALUE 0xAA

typedef struct 
{
	uint8_t byteSize;
	uint16_t factoryValue;
	uint8_t indexOnROMPage;
//	uint16_t lLimit;
//	uint16_t hLimit;
} Variable_t;

extern Variable_t GerkonFiltTime;
extern Variable_t SendAlarmTimePos;
extern Variable_t ReactivateAlarmTime;
extern Variable_t BuzzerOffTime;
extern Variable_t SendOfflineEvents;
extern Variable_t FreeAccess;
extern Variable_t MasterSlave;
extern Variable_t TotalKeys;
extern Variable_t ActiveKeys;
extern Variable_t FlashResourse;

extern Variable_t *variables[VAR_COUNT];

void InitVariables();

#endif // VARIABLES_H

