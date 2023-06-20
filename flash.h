#ifndef FLASH_H
#define FLASH_H
#include "MG32x02z_DRV.h"
#include "iap.h"
#include "packages.h"

#define FAILURE UINT32_MAX
#define SUCCESS 0

#define IAP_PAGE_COUNT 10
#define IAP_SIZE (IAP_PAGE_COUNT * IAP_PAGE_SIZE)

uint32_t ActivateKey(uint8_t operationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB);
uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB);
uint32_t DoCommand(uint8_t commNum, uint8_t commArg);

uint32_t AddKey(uint8_t newStatus, uint8_t keyIndexLSB, uint8_t keyIndexMSB, uint8_t *keyMSB);
uint32_t SetVariablePack(uint8_t *packStartAddr);

uint32_t GetVariable(uint8_t varNumber);
uint32_t GetKeyStatus(uint16_t keyIndex);

uint32_t GetMaxFlashResource(void);
uint32_t UpdateFlashResource(uint8_t curPageNumber);

uint32_t CopyFlashPageToRAM(uint8_t pageNumber);
uint32_t CopyRAMToFlashPage(uint8_t pageNumber);
	
void FlashFirstInit(void);

void FlashTestFill(void);

typedef union 
{
	uint8_t byte[IAP_PAGE_SIZE];
	uint32_t word[IAP_PAGE_SIZE / 4];
} flash_block_t;


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

// позиции с 0 до 999

#define TOTAL_KEYS_POS 253
#define ACTIVE_KEYS_POS 254

/* Страницы 2-17: Ключи доступа */

// позиции с 0 до 63


void CopyVariablesPage0ToFlash(void);

#endif // FLASH_H
