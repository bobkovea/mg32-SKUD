#ifndef IAP_H
#define IAP_H

#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_MEM_DRV.h"
#include "MG32x02z_CSC_DRV.h"

#if defined(MG32_1ST) || defined(MG32_2ND) // MG32F02A132, MG32F02A072, MG32F02A032
#define IAP_SIZE_1024 1024UL
#define IAP_SIZE_2048 2048UL 
#define IAP_SIZE_3072 3072UL
#define IAP_SIZE_4096 4096UL
#define IAP_PAGE_SIZE 1024UL
#endif

#if defined(MG32_3RD) || defined(MG32_4TH) // MG32F02x128, MG32F02x064, MG32F02V032
#define IAP_SIZE_512 512UL
#define IAP_SIZE_1024 1024UL
#define IAP_SIZE_1536 1536UL
#define IAP_SIZE_2048 2048UL
#define IAP_SIZE_2560 2560UL
#define IAP_SIZE_3072 3072UL
#define IAP_SIZE_3584 3584UL
#define IAP_SIZE_4096 4096UL
#define IAP_PAGE_SIZE 512UL
#endif
// минимальный размер выделяемой IAP  (флеша для переменных) равен размеру одной страницы
#define MIN_IAP_SIZE IAP_PAGE_SIZE
// начальный адрес IAP
#define IAP_START_ADDRESS 0x1A000000UL
 	
void IAP_Init(uint32_t IAPSize);
void IAP_FullErase(void);
void IAP_Erase_OnePage (uint16_t pageNumber);
uint8_t IAP_WriteSingleWord(uint8_t pageNumber, uint8_t wordIndexOnPage, uint32_t wordValue);
uint8_t IAP_WriteMultipleWord(uint8_t pageNumber, uint8_t startWordIndexOnPage, void *startAddrInRAM, uint32_t wordsCount);
uint8_t IAP_ReadByte(uint8_t pageNumber, uint16_t byteIndexOnPage);
uint32_t IAP_ReadWord(uint8_t pageNumber, uint32_t wordIndexOnPage);
void IAP_CopyFromIAPToRAM(uint8_t pageNumber, uint32_t startByteIndexOnPage, void *startAddrInRAM, uint32_t bytesCount);
uint8_t IAP_IsEqualToRAM(uint32_t startByteIndex, void* startAddrInRAM, uint32_t bytesCount);

DRV_Return IAP_Erase_Page(uint32_t StartPageAddress, uint32_t PageQuantity);
DRV_Return IAP_Single_Write(uint32_t IAPStartAddress, uint32_t ProgramData);
DRV_Return IAP_Multiple_Write(uint32_t IAPStartAddress, uint32_t DataStartAddress, uint32_t Length);

#endif