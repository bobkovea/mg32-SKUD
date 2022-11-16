#ifndef FLASH_H
#define FLASH_H
#include "MG32x02z_DRV.h"
#include "iap.h"
#include "packages.h"

#define IAP_PAGE_COUNT 19
#define IAP_SIZE (IAP_PAGE_COUNT * IAP_PAGE_SIZE)

uint32_t ActivateKey(uint8_t operationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB);
uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB);
uint32_t DoCommand(uint8_t commNum, uint8_t commArg);

uint32_t AddKey(uint8_t newStatus, uint8_t keyIndexLSB, uint8_t keyIndexMSB, uint8_t *keyMSB);
uint32_t SetVariablePack(uint8_t *packStartAddr);

uint32_t GetVariable(uint8_t varNumber);
uint32_t GetKeyStatus(uint16_t keyIndex);

uint32_t CopyFlashPageToRAM(uint8_t pageNumber);
uint32_t CopyRAMToFlashPage(uint8_t pageNumber);

void FlashFirstInit(void);

void FlashTestFill(void);

typedef union 
{
	uint8_t byte[1024];
	uint32_t word[128];
} flash_block_t;


//----------------------------------------------------------------------------------------
// Номера страниц
//----------------------------------------------------------------------------------------
#define PAGE_NUMBER_VARS 0
#define PAGE_NUMBER_EVENTS 1
#define PAGE_NUMBER_KEYSTATUS 2
#define PAGE_NUMBER_KEYS_0 3

//----------------------------------------------------------------------------------------
// Позиции переменных в памяти
//----------------------------------------------------------------------------------------

// Страница 0: Внутренние переменные

#define FIRST_WRITE_VALUE_POS 0

#define FLASH_RESOURCE_POS 1

#define GERKON_FILT_TIME_POS 10
#define SEND_ALARM_TIME_POS 11
#define REACTIVATE_ALARM_TIME_POS 12
#define BUZZER_OFF_TIME_POS 13
#define SEND_OFFLINE_EVENTS_POS 14
#define FREE_ACCESS_POS 15
#define MASTER_SLAVE_POS 16
#define TOTAL_KEYS_POS 17
#define ACTIVE_KEYS_POS 18

// Страница 1: Архив событий

#define EVENT_DOOR_STATUS 0
#define EVENT_DOOR_TIME 1
#define EVENT_DOOR_COUNT 2

#define EVENT_ACCESS_STATUS 10
#define EVENT_ACCESS_TIME 11
#define EVENT_ACCESS_COUNT 12

#define EVENT_ALARM_STATUS 20
#define EVENT_ALARM_DOOR_TIME 21
#define EVENT_ALARM_COUNT 22
 
// Страница 2: Статус ключей доступа

// позиции с 0 до 1023


// Страницы 3-19: Ключи доступа

// позиции с 0 до 63

#endif // FLASH_H
