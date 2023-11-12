#ifndef VARIABLES_H
#define VARIABLES_H
#include "stdint.h"
#include "flash.h"

#define VAR_WRITABLE_COUNT 4
#define VAR_PAGE0_COUNT 6
#define VAR_TOTAL_COUNT 9

#define BYTE 1
#define HWORD 2

// значения по умолчанию
#define __FIRST_WRITE_VALUE 0xAA

#define __GERKON_FILT_TIME 100
#define __PROTECTION_DELAY_TIME 1 // 60
#define __BUZZER_OFF_TIME 1 // 5
#define __CHECK_KEY_DISABLED 0

#define __ACCESS_IS_GIVEN 0
#define __VALID_KEY_INDEX 0xFFFF

#define __TOTAL_KEYS 0
#define __ACTIVE_KEYS 0
#define __FLASH_RESOURCE 1

typedef struct 
{
	uint16_t value;
	const uint16_t factoryValue;
	const uint8_t byteSize;
	const uint8_t indexOnPage;
} Variable_t;

// изменяемые непосредственно по запросу
extern Variable_t GerkonFiltTime; // время фильтрации открытия дверцы
extern Variable_t ProtectionDelayTime; // время предоставления доступа к шкафу после ввода верного ключа
extern Variable_t BuzzerOffTime; // время отключения звуковой сигнализации
extern Variable_t CheckKeyDisabled; // при == 1 система приводится к состоянию "sAccessGiven" и более не выводится из него

// изменяемые косвенно в процессе работы
extern Variable_t AccessIsGiven; // если == 1, то мы находимся в состоянии "sAccessGiven"
								 // и по истечении "ProtectionDelayTime" перейдем в состояние "sNoAccessSleep"
extern Variable_t ValidKeyIndex; // если != 0xFFFF, то необходимо отправить открывший ключ, после этого сбрасывается

extern Variable_t TotalKeys;
extern Variable_t ActiveKeys;
extern Variable_t FlashResourse;

extern Variable_t *variables[VAR_TOTAL_COUNT];

#endif // VARIABLES_H

