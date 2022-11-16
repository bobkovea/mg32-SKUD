#ifndef IAP_H
#define IAP_H

#include "MG32x02z_DRV.h"
	
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
void IAP_Erase_OnePage (uint16_t PageNumber);
uint8_t IAP_WriteSingleWord(uint32_t WordIndexInIAP, uint32_t WordValue);
uint8_t IAP_WriteMultipleWord(uint32_t WordIndexInIAP, uint32_t DataStartAddress, uint32_t Length);
uint8_t IAP_ReadByte(uint32_t ByteIndexInIAP);
uint32_t IAP_ReadWord(uint32_t WordIndexInIAP);
uint32_t IAP_GetPageNumberOfByte(uint32_t ByteIndexInIAP);
uint32_t IAP_GetNumberOfPages(void);
uint8_t IAP_IsEqualToRAM(uint32_t StartIndex, void* StructInRAMPointer, uint32_t StructInRAMSize);
void IAP_CopyIAPInRAM(uint32_t StartIndex, void* StructInRAMPointer, uint32_t StructInRAMSize);
uint8_t IAP_CopyRAMInIAP(uint32_t StartIndex, void* StructInRAMPointer, uint32_t StructInRAMSize);
uint32_t IAP_IsAreaEmpty(uint32_t StartIndex, uint32_t EndIndex);
uint32_t IAP_IsFullEmpty(void);

DRV_Return IAP_Erase_Page(uint32_t StartPageAddress, uint32_t PageQuantity);
DRV_Return IAP_Single_Write(uint32_t IAPStartAddress, uint32_t ProgramData);
DRV_Return IAP_Multiple_Write(uint32_t IAPStartAddress, uint32_t DataStartAddress, uint32_t Length);

#endif