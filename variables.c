#include "MG32x02z__Common_DRV.h"
#include "variables.h"
#include "flash_static.h"

void InitVar (Variable_t *var, uint8_t byteSize, uint16_t factoryValue, uint8_t indexOnROMPage)
{
	var->byteSize = byteSize;
	var->factoryValue = factoryValue;
	var->indexOnROMPage = indexOnROMPage;
}

// код переменной = индекс переменной
void InitVariables()
{
	InitVar(&GerkonFiltTime, 		2, __GERKON_FILT_TIME, 		GERKON_FILT_TIME_POS);
	InitVar(&SendAlarmTimePos, 		2, __SEND_ALARM_TIME, 		SEND_ALARM_TIME_POS);
	InitVar(&ReactivateAlarmTime,  	2, __REACTIVATE_ALARM_TIME, REACTIVATE_ALARM_TIME_POS);
	InitVar(&BuzzerOffTime, 		2, __BUZZER_OFF_TIME, 		BUZZER_OFF_TIME_POS);
	InitVar(&SendOfflineEvents, 	1, __SEND_OFFLINE_EVENTS, 	SEND_OFFLINE_EVENTS_POS);
	InitVar(&FreeAccess, 			1, __FREE_ACCESS, 			FREE_ACCESS_POS);
	InitVar(&MasterSlave, 			1, __MASTER_SLAVE, 			MASTER_SLAVE_POS);
	InitVar(&TotalKeys, 			2, __TOTAL_KEYS, 			TOTAL_KEYS_POS);
	InitVar(&ActiveKeys, 			2, __ACTIVE_KEYS, 			ACTIVE_KEYS_POS);
	InitVar(&FlashResourse, 		2, __FLASH_RESOURCE, 		FLASH_RESOURCE_POS);
}
Variable_t *variables[VAR_COUNT] =
{
	&GerkonFiltTime,
	&SendAlarmTimePos,
	&ReactivateAlarmTime,
	&BuzzerOffTime,
	&SendOfflineEvents,
	&FreeAccess,
	&MasterSlave,
	&TotalKeys,
	&ActiveKeys,
	&FlashResourse,
};