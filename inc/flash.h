#ifndef FLASH_H
#define FLASH_H
#include "MG32x02z_DRV.h"
#include "iap.h"
#include "packages.h"
#include "keys.h"
#include "variables.h"
#include "usart.h"
#include "md5.h"
#include "api.h"

#define IAP_PAGE_COUNT 10

//----------------------------------------------------------------------------------------
// Номера страниц
//----------------------------------------------------------------------------------------
#define PAGE_NUMBER_VARS 0
#define PAGE_NUMBER_KEYSTATUS 1
#define PAGE_NUMBER_KEYS_0 2

//----------------------------------------------------------------------------------------
// Позиции переменных в памяти
//----------------------------------------------------------------------------------------


#define FLASH_RESOURCE_POS 255

/* Страница 0: Внутренние переменные */

#define FIRST_WRITE_VALUE_POS 0

#define GERKON_FILT_TIME_POS 10
#define PROTECTION_DELAY_TIME_POS 11
#define BUZZER_OFF_TIME_POS 12
#define CHECK_KEY_DISABLED_POS 13
#define ACCESS_IS_GIVEN_POS 14
#define VALID_KEY_INDEX_POS 15
 
/* Страница 1: Статус ключей доступа */

// позиции с 0 до KEYS_MAX_INDEX

#define TOTAL_KEYS_POS 253
#define ACTIVE_KEYS_POS 254


/* Страницы 2-8: Ключи доступа */

// позиции с 0 до 63

void PowerOnHandle(void);

void FlashTestFill(void);

typedef union 
{
	uint8_t byte[IAP_PAGE_SIZE];
	uint32_t word[IAP_PAGE_SIZE / 4];
} FlashPage_t;

// массив-копия страницы флеша. Нужен для удобной перезаписи данных во флеш
// для удобства обращения к нему представлен в виде объединения выше
extern FlashPage_t fpage; 

void API_CopyVariablesPage0ToFlash(void);

#endif // FLASH_H
