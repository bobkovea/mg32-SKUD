#ifndef FLASH_H
#define FLASH_H
#include "iap.h"

// ключ во флеше
#define FlashKeyValue 0xAA

// Верхний порог скользящего среднего по умолчанию
#define ThrHighDefault 40

// устанавливаем выравнивание равным 4 байтам (похоже, и так по умолчанию 4)
#pragma pack(push)
#pragma pack(4)
// структура 

//typedef union
//{
//	uint8_t byte[1024];
//	uint32_t word[128];
//} flash_page;

typedef struct {
	uint8_t FlashKey; // флаг чистоты flash, НЕ равен 0xFF!
	uint8_t ThrHigh; // верхний порог скользящего среднего
	uint32_t NWrite; // количество стираний страницы
	uint32_t CheckSum; // контрольная сумма
} Config_t;
#pragma pack(pop)

// флаги возврата обработки флеша при включении МК
typedef enum  {
	OK_EMPTY = 0x00,
	OK_NOT_EMPTY= 0x01,
	ERROR_BAD_MEMORY = 0x02,
	ERROR_CRC = 0x03,
} FlashStatus;

extern Config_t cfg;
extern uint32_t CurLastBlockPos;
	
FlashStatus FlashStartupHandle(void);
void FlashUpdate(void);
uint8_t IsEnoughSpace(uint32_t CurPos, uint32_t BlockSize);
uint16_t GetBlocksLeft(uint32_t CurLastBlockPos, uint32_t BlockSize);
uint32_t FindLastBlockPos(uint32_t FromPos, uint32_t ToPos, uint32_t BlockSize);
void FillStructureDefault(void);


#endif // FLASH_H