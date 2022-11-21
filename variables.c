#include "MG32x02z__Common_DRV.h"
#include "variables.h"
#include "flash.h"

Variable_t GerkonFiltTime 		= 	{ 2, 	__GERKON_FILT_TIME, 		GERKON_FILT_TIME_POS 		};
Variable_t SendAlarmTimePos 	= 	{ 2, 	__SEND_ALARM_TIME, 			SEND_ALARM_TIME_POS 		};
Variable_t ReactivateAlarmTime 	= 	{ 2, 	__REACTIVATE_ALARM_TIME, 	REACTIVATE_ALARM_TIME_POS 	};
Variable_t BuzzerOffTime 		= 	{ 2, 	__BUZZER_OFF_TIME, 			BUZZER_OFF_TIME_POS 		};
Variable_t SendOfflineEvents 	= 	{ 1, 	__SEND_OFFLINE_EVENTS, 		SEND_OFFLINE_EVENTS_POS 	};
Variable_t FreeAccess 			= 	{ 1, 	__FREE_ACCESS, 				FREE_ACCESS_POS 			};
Variable_t MasterSlave 			= 	{ 1, 	__MASTER_SLAVE, 			MASTER_SLAVE_POS 			};
Variable_t TotalKeys 			= 	{ 2, 	__TOTAL_KEYS, 				TOTAL_KEYS_POS 				};
Variable_t ActiveKeys 			= 	{ 2, 	__ACTIVE_KEYS, 				ACTIVE_KEYS_POS 			};
Variable_t FlashResourse 		= 	{ 2, 	__FLASH_RESOURCE, 			FLASH_RESOURCE_POS 			};

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
