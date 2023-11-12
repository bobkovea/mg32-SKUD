#include "variables.h"

Variable_t GerkonFiltTime 		= 	{ __GERKON_FILT_TIME, 		__GERKON_FILT_TIME, 	 HWORD, 	GERKON_FILT_TIME_POS 		};
Variable_t ProtectionDelayTime 	= 	{ __PROTECTION_DELAY_TIME, 	__PROTECTION_DELAY_TIME, HWORD, 	PROTECTION_DELAY_TIME_POS 	};
Variable_t BuzzerOffTime 		= 	{ __BUZZER_OFF_TIME, 		__BUZZER_OFF_TIME, 		 HWORD, 	BUZZER_OFF_TIME_POS 		};
Variable_t CheckKeyDisabled 	= 	{ __CHECK_KEY_DISABLED, 	__CHECK_KEY_DISABLED, 	 BYTE, 		CHECK_KEY_DISABLED_POS		};
Variable_t AccessIsGiven 		= 	{ __ACCESS_IS_GIVEN, 		__ACCESS_IS_GIVEN,		 BYTE, 		ACCESS_IS_GIVEN_POS 		};
Variable_t ValidKeyIndex 		= 	{ __VALID_KEY_INDEX, 		__VALID_KEY_INDEX,		 HWORD, 	VALID_KEY_INDEX_POS 		};
Variable_t TotalKeys 			= 	{ __TOTAL_KEYS, 			__TOTAL_KEYS, 			 HWORD, 	TOTAL_KEYS_POS 				};
Variable_t ActiveKeys 			= 	{ __ACTIVE_KEYS, 			__ACTIVE_KEYS, 			 HWORD, 	ACTIVE_KEYS_POS 			};
Variable_t FlashResourse 		= 	{ __FLASH_RESOURCE, 		__FLASH_RESOURCE, 		 HWORD, 	FLASH_RESOURCE_POS 			};

Variable_t *variables[VAR_TOTAL_COUNT] =
{
	&GerkonFiltTime,
	&ProtectionDelayTime,
	&BuzzerOffTime,
	&CheckKeyDisabled,
	&AccessIsGiven,
	&ValidKeyIndex,
	&TotalKeys,
	&ActiveKeys,
	&FlashResourse,
};
