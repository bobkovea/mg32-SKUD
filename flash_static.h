#ifndef FLASH_STATIC_H
#define FLASH_STATIC_H
#include "MG32x02z_DRV.h"
#include "iap.h"

uint32_t GetVariable(uint8_t varNumber);
uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB);
uint32_t SetVariablePack(uint8_t *packStartAddr);
uint32_t ActivateKey(uint8_t varNumber);
uint32_t CopyFlashPageToRAM(uint8_t pageNumber);
uint32_t CopyRAMToFlashPage(uint8_t pageNumber);

typedef union 
{
	uint8_t byte[1024];
	uint32_t word[128];
} flash_block_t;

#define KEY_STATUS_DEACTIVATED 0x00
#define KEY_STATUS_ACTIVATED 0x01
#define KEY_STATUS_FREE 0xFF

#define COMM_ALLKEYACT
#define COMM_FACTORY_NUM

#define WRITABLE_VAR_COUNT 6
#define READABLE_VAR_COUNT 9

uint8_t VarsLenMas[READABLE_VAR_COUNT];

//----------------------------------------------------------------------------------------
// Номера страниц
//----------------------------------------------------------------------------------------
#define PAGE_NUMBER_VARS 0
#define PAGE_NUMBER_EVENTS 1
#define PAGE_NUMBER_KEYSTATUS 2
#define PAGE_NUMBER_KEYS_1 3
#define PAGE_NUMBER_KEYS_2 4


//----------------------------------------------------------------------------------------
// Позиции переменных в памяти
//----------------------------------------------------------------------------------------

// Страница 0: Внутренние переменные

#define FIRST_WRITE_VALUE_POS 0
#define FLASH_RESOURCE_POS 1

// заводские значения переменных
#define __GERKON_FILT_TIME_POS 10
#define __SEND_ALARM_TIME_POS 11
#define __REACTIVATE_ALARM_TIME_POS 12
#define __SEND_OFFLINE_EVENTS_POS 13
#define __FREE_ACCESS_POS 14
#define __MASTER_SLAVE_POS 15

#define GERKON_FILT_TIME_POS 100
#define SEND_ALARM_TIME_POS 101
#define REACTIVATE_ALARM_TIME_POS 102
#define SEND_OFFLINE_EVENTS_POS 103
#define FREE_ACCESS_POS 104
#define MASTER_SLAVE_POS 105
#define TOTAL_KEYS_POS 106
#define ACTIVE_KEYS 107

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

#endif // FLASH_STATIC_H
