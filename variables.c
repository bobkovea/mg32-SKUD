#include "MG32x02z__Common_DRV.h"
#include "variables.h"
#include "flash.h"

Variable_t GerkonFiltTime 		= 	{ __GERKON_FILT_TIME, 		__GERKON_FILT_TIME, 	 2, GERKON_FILT_TIME_POS 		};
Variable_t SendAlarmTime 		= 	{ __SEND_ALARM_TIME, 		__SEND_ALARM_TIME, 		 2, SEND_ALARM_TIME_POS 	  	};
Variable_t ReactivateAlarmTime 	= 	{ __REACTIVATE_ALARM_TIME, 	__REACTIVATE_ALARM_TIME, 2, REACTIVATE_ALARM_TIME_POS 	};
Variable_t BuzzerOffTime 		= 	{ __BUZZER_OFF_TIME, 		__BUZZER_OFF_TIME, 		 2, BUZZER_OFF_TIME_POS 		};
Variable_t SendOfflineEvents 	= 	{ __SEND_OFFLINE_EVENTS, 	__SEND_OFFLINE_EVENTS, 	 1, SEND_OFFLINE_EVENTS_POS 	};
Variable_t FreeAccess 			= 	{ __FREE_ACCESS, 			__FREE_ACCESS, 			 1, FREE_ACCESS_POS 			};
Variable_t MasterSlave 			= 	{ __MASTER_SLAVE, 			__MASTER_SLAVE, 		 1, MASTER_SLAVE_POS 			};
Variable_t TotalKeys 			= 	{ __TOTAL_KEYS, 			__TOTAL_KEYS, 			 2, TOTAL_KEYS_POS 				};
Variable_t ActiveKeys 			= 	{ __ACTIVE_KEYS, 			__ACTIVE_KEYS, 			 2, ACTIVE_KEYS_POS 			};
Variable_t FlashResourse 		= 	{ __FLASH_RESOURCE, 		__FLASH_RESOURCE, 		 2, FLASH_RESOURCE_POS 			};

Variable_t *variables[VAR_COUNT] =
{
	&GerkonFiltTime,
	&SendAlarmTime,
	&ReactivateAlarmTime,
	&BuzzerOffTime,
	&SendOfflineEvents,
	&FreeAccess,
	&MasterSlave,
	&TotalKeys,
	&ActiveKeys,
	&FlashResourse,
};
