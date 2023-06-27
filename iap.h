#ifndef IAP_H
#define IAP_H

#include "MG32x02z_MEM_DRV.h"
#include "MG32x02z_CSC_DRV.h"

// в зависимости от модели МК размер страницы флеша составляет 1024 или 512 байт
#if defined(MG32_1ST) || defined(MG32_2ND) // MG32F02A132, MG32F02A072, MG32F02A032
#define IAP_PAGE_SIZE 1024UL
#elif defined(MG32_3RD) || defined(MG32_4TH) // MG32F02x128, MG32F02x064, MG32F02V032
#define IAP_PAGE_SIZE 512UL
#endif

// начальный адрес IAP
#define IAP_START_ADDRESS 0x1A000000UL

DRV_Return IAP_Erase_Page(uint32_t StartPageAddress, uint32_t PageQuantity);
DRV_Return IAP_Single_Write(uint32_t IAPStartAddress, uint32_t ProgramData);
DRV_Return IAP_Multiple_Write(uint32_t IAPStartAddress, uint32_t DataStartAddress, uint32_t Length);

/* Пользовательские функции */

//----------------------------------------------------------------------------------------
// Функция выделяет память под IAP
// Объем выделяемой памяти кратен размеру одной страницы IAP (см. IAP_PAGE_SIZE)
// Args: 	pageCount - количество выделяемых страницы флеша на пользовательские нужды
//----------------------------------------------------------------------------------------
__STATIC_INLINE void IAP_Init(uint8_t pageCount)
{
	UnProtectModuleReg(CSCprotect);
	CSC_IHRCO_Cmd(ENABLE); // принудительно включаем IHRCO (для флеша)
	while(CSC_GetClockSourceState(CSC_IHRCO_STA) == DRV_Unready)
		;
	CSC_ClearFlag(CSC_IHRCOF);
	ProtectModuleReg(CSCprotect);
	
	MEM_SetIAPSize(IAP_PAGE_SIZE * pageCount);
	MEM_SetIAPSizeLock(); // не обязательно
}

/*----------------------------------------------------------------------------------------
// Функция очищает одну страницу IAP по её порядковому номеру
// Args: 	pageNumber - порядковый номер страницы в IAP
----------------------------------------------------------------------------------------*/
__STATIC_FORCEINLINE void IAP_Erase_OnePage (uint16_t pageNumber)
{
	IAP_Erase_Page(IAP_START_ADDRESS + (IAP_PAGE_SIZE * pageNumber), 1);
}

//----------------------------------------------------------------------------------------
// Функция очищает всю выделенную под IAP flash-память
//----------------------------------------------------------------------------------------
__STATIC_FORCEINLINE void IAP_FullErase(void)
{
	IAP_Erase_Page(IAP_START_ADDRESS, MEM_GetIAPSize() / IAP_PAGE_SIZE);
}


/*----------------------------------------------------------------------------------------
// Функция читает 1 байт из IAP по индексу байта на странице
// Args: 	pageNumber - порядковый номер страницы в IAP
			byteIndexOnPage - индекс читаемого байта на странице в IAP (< IAP_PAGE_SIZE)
----------------------------------------------------------------------------------------*/
__STATIC_FORCEINLINE uint8_t IAP_ReadByte(uint8_t pageNumber, uint16_t byteIndexOnPage)
{
	return *(uint8_t *)(IAP_START_ADDRESS + 
		pageNumber * IAP_PAGE_SIZE + byteIndexOnPage);
}

/*----------------------------------------------------------------------------------------
// Функция читает слово (4 байта) из IAP по индексу слова на странице
// Args: 	pageNumber - порядковый номер страницы в IAP
			wordIndexOnPage - индекс записываемого слова на странице в IAP (< IAP_PAGE_SIZE / 4)
			
----------------------------------------------------------------------------------------*/
__STATIC_FORCEINLINE uint32_t IAP_ReadWord(uint8_t pageNumber, uint8_t wordIndexOnPage)
{
	return *(uint32_t *)(IAP_START_ADDRESS + 
		pageNumber * IAP_PAGE_SIZE + (wordIndexOnPage * 4));
}

/*----------------------------------------------------------------------------------------
// Функция записывает слово (4 байта) по индексу слова на странице
// Args: 	pageNumber - порядковый номер страницы в IAP;
 			wordIndexOnPage - индекс записываемого слова на странице в IAP (< IAP_PAGE_SIZE / 4);
 			startAddrInRAM - указатель на копируемый участок в ОЗУ;
 			wordsCount - количество записываемых слов
----------------------------------------------------------------------------------------*/
__STATIC_FORCEINLINE void IAP_WriteSingleWord(uint8_t pageNumber, uint8_t wordIndexOnPage, uint32_t wordValue)
{
	IAP_Single_Write(IAP_START_ADDRESS + pageNumber * IAP_PAGE_SIZE 
		+ (wordIndexOnPage * 4), wordValue);
} 

/*----------------------------------------------------------------------------------------
// Функция записывает слова (4 байта) из ОЗУ в IAP, начиная с заданного индекса слова
// Args: 	pageNumber - порядковый номер страницы в IAP 
 			startWordIndexOnPage - стартовый индекс слова на странице в IAP (< IAP_PAGE_SIZE / 4)
 			startAddrInRAM - указатель на копируемый участок в ОЗУ;
 			wordsCount - количество записываемых слов
----------------------------------------------------------------------------------------*/

__STATIC_FORCEINLINE void IAP_WriteMultipleWord(uint8_t pageNumber, uint8_t startWordIndexOnPage, void *startAddrInRAM, uint32_t wordsCount)
{
	IAP_Multiple_Write(IAP_START_ADDRESS + pageNumber * IAP_PAGE_SIZE
		+ (startWordIndexOnPage * 4), (uint32_t)startAddrInRAM, wordsCount);
}

/*----------------------------------------------------------------------------------------
// Функция копирует данные из IAP в структуру ОЗУ
// Args:	pageNumber - порядковый номер страницы в IAP
// 			startByteIndexOnPage - стартовый индекс байта на странице в IAP  (< IAP_PAGE_SIZE);
// 			startAddrInRAM - указатель на копируемый участок в ОЗУ;
// 			bytesCount - количество копируемых байтов.
-----------------------------------------------------------------------------------------*/
__STATIC_FORCEINLINE void IAP_CopyFromIAPToRAM(uint8_t pageNumber, uint16_t startByteIndexOnPage, void *startAddrInRAM, uint32_t bytesCount)  
{ 	
	memcpy(startAddrInRAM, (uint8_t*) (IAP_START_ADDRESS + pageNumber * IAP_PAGE_SIZE
		+ startByteIndexOnPage), bytesCount);
}

//----------------------------------------------------------------------------------------
// Функция копирует страницу IAP в массив-буфер в ОЗУ
// Args:	pageNumber - порядковый номер страницы в IAP;
//			dest - указатель на массив-буфер в ОЗУ.
//----------------------------------------------------------------------------------------

__STATIC_FORCEINLINE void IAP_CopyFlashPageToRAM(uint8_t pageNumber, void *dest)
{
	IAP_CopyFromIAPToRAM(pageNumber, 0, dest, IAP_PAGE_SIZE);
}

/*----------------------------------------------------------------------------------------
// Функция копирует массив-буфер в ОЗУ на страницу IAP
// Args:	pageNumber - порядковый номер страницы в IAP;
//			src - указатель на массив-буфер в ОЗУ.
----------------------------------------------------------------------------------------*/

__STATIC_FORCEINLINE void IAP_CopyRAMToFlashPage(uint8_t pageNumber, void *src)
{
	IAP_WriteMultipleWord(pageNumber, 0, src, IAP_PAGE_SIZE / 4);
}

/*----------------------------------------------------------------------------------------
// Функция проверяет на равенство участки памяти в IAP и ОЗУ
// Args:	startByteIndex - стартовый индекс байта в IAP;
// 			startAddrInRAM - адрес начала проверяемой области в ОЗУ;
// 			bytesCount - размер сравниваемой области в байтах.
// Returns: 1 (участки равны)
			0 (участки не равны)
----------------------------------------------------------------------------------------*/
__STATIC_FORCEINLINE uint8_t IAP_IsEqualToRAM(uint32_t startByteIndex, void *startAddrInRAM, uint32_t bytesCount) 
{
	return !memcmp((void *) (IAP_START_ADDRESS + startByteIndex), 
					startAddrInRAM, 
					bytesCount);
}

#endif