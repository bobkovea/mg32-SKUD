#include "iap.h"

//----------------------------------------------------------------------------------------
// Функция выделяет память под IAP
// Выделяемая память не может быть меньше одной страницы 
// (512 или 1024 байта в зависимости от контроллера)
//----------------------------------------------------------------------------------------
void IAP_Init(uint32_t IAPSize)
{
	UnProtectModuleReg(CSCprotect);
	CSC_IHRCO_Cmd(ENABLE); // принудительно включаем IHRCO (для флеша)
	while(CSC_GetClockSourceState(CSC_IHRCO_STA) == DRV_Unready)
		;
	CSC_ClearFlag(CSC_IHRCOF);
	ProtectModuleReg(CSCprotect);
	
	MEM_SetIAPSize(IAPSize);
//	MEM_SetIAPSizeLock(); // не обязательно
}

//----------------------------------------------------------------------------------------
// Функция очищает одну страницу IAP по её порядковому номеру
//----------------------------------------------------------------------------------------
void IAP_Erase_OnePage (uint16_t pageNumber)
{
	IAP_Erase_Page(IAP_START_ADDRESS + (IAP_PAGE_SIZE * pageNumber), 1);
}

//----------------------------------------------------------------------------------------
// Функция очищает всю выделенную под IAP flash-память
//----------------------------------------------------------------------------------------
void IAP_FullErase(void)
{
	IAP_Erase_Page(IAP_START_ADDRESS, MEM_GetIAPSize() / IAP_PAGE_SIZE);
}


//----------------------------------------------------------------------------------------
// Функция читает 1 байт из IAP по индексу байта на странице
// Индекс изменяется от 0 до размера страницы IAP в байтах 
//----------------------------------------------------------------------------------------
uint8_t IAP_ReadByte(uint8_t pageNumber, uint16_t byteIndexOnPage)
{
	return *(uint8_t *)(IAP_START_ADDRESS + 
		pageNumber * IAP_PAGE_SIZE + byteIndexOnPage);
}


//----------------------------------------------------------------------------------------
// Функция читает слово (4 байта) из IAP по индексу слова на странице
// Индекс изменяется от 0 до размера страницы IAP в байтах 
//----------------------------------------------------------------------------------------
uint32_t IAP_ReadWord(uint8_t pageNumber, uint32_t wordIndexOnPage)
{
	return *(uint32_t *)(IAP_START_ADDRESS + 
		pageNumber * IAP_PAGE_SIZE + (wordIndexOnPage * 4));
}

//----------------------------------------------------------------------------------------
// Функция записывает слово (4 байта) по индексу слова на странице
// pageNumber - номер страницы в IAP
// wordIndexOnPage - индекс записываемого слова на странице в IAP (от 0 до IAP_SIZE / 4)
// startAddrInRAM - указатель на копируемый участок в ОЗУ;
// wordsCount - количество записываемых слов
//----------------------------------------------------------------------------------------
uint8_t IAP_WriteSingleWord(uint8_t pageNumber, uint8_t wordIndexOnPage, uint32_t wordValue)
{
	return IAP_Single_Write(IAP_START_ADDRESS + pageNumber * IAP_PAGE_SIZE 
		+ (wordIndexOnPage * 4), wordValue);
} 

//----------------------------------------------------------------------------------------
// Функция записывает слова (4 байта) из ОЗУ в IAP, начиная с адреса 
// pageNumber - номер страницы в IAP
// startWordIndexOnPage - стартовый индекс слова на странице в IAP 
// startAddrInRAM - указатель на копируемый участок в ОЗУ;
// wordsCount - количество записываемых слов
//----------------------------------------------------------------------------------------

uint8_t IAP_WriteMultipleWord(uint8_t pageNumber, uint8_t startWordIndexOnPage, void *startAddrInRAM, uint32_t wordsCount)
{
	return IAP_Multiple_Write(IAP_START_ADDRESS + pageNumber * IAP_PAGE_SIZE
		+ (startWordIndexOnPage * 4), (uint32_t)startAddrInRAM, wordsCount * 4);
}

//----------------------------------------------------------------------------------------
// Функция копирует данные из IAP в структуру ОЗУ
// pageNumber - номер страницы в IAP
// startByteIndexOnPage -  стартовый индекс байта на странице в IAP 
// startAddrInRAM - указатель на копируемый участок в ОЗУ;
// bytesCount - количество копируемых байтов

void IAP_CopyFromIAPToRAM(uint8_t pageNumber, uint32_t startByteIndexOnPage, void *startAddrInRAM, uint32_t bytesCount)  
{ 	
	memcpy(startAddrInRAM, (void *)(IAP_START_ADDRESS + pageNumber * IAP_PAGE_SIZE
		+ startByteIndexOnPage), bytesCount * 4);
}

//----------------------------------------------------------------------------------------
// Функция сравнивает состояние участка в IAP с участком в ОЗУ
// startByteIndex - стартовый индекс байта в IAP;
// structInRAMPointer - указатель на структуру с данными;
// structInRAMSize - размер структуры в байтах.
//----------------------------------------------------------------------------------------
uint8_t IAP_IsEqualToRAM(uint32_t startByteIndex, void *startAddrInRAM, uint32_t bytesCount) 
{
	return !memcmp((void *) (IAP_START_ADDRESS + startByteIndex), 
					startAddrInRAM, 
					bytesCount);
}

//-----------------------------Фундаментальные функции----------------------------------//

//----------------------------------------------------------------------------------------
// Функция очищает произвольное количества страниц, начиная с выбранного адреса
// Стартовый адрес должен быть кратен размеру страницы 
//----------------------------------------------------------------------------------------
DRV_Return IAP_Erase_Page(uint32_t StartPageAddress, uint32_t PageQuantity)
{
    DRV_Return lDRV_Return = DRV_Success;
    uint32_t lCount;
    uint32_t *lptrDest_addr;

    // Проверить, включена ли RC-цепочка
    if(CSC->CR0.MBIT.IHRCO_EN == 0)
        return DRV_Failure;

	// проверка на кратность адреса начала стирания 512 или 1024 (в зависимости от МК)
	if((StartPageAddress & (IAP_PAGE_SIZE - 1)) != 0)
			return DRV_Failure;      
	// Не выходим ли мы за края IAP-памяти?
    if(((StartPageAddress) < 0x1A000000) || ((StartPageAddress) >= 0x1C000000))
        return DRV_Failure;

    lptrDest_addr = (uint32_t *)StartPageAddress;
    lCount = 0;

    __MEM_UnProtect();
    __MEM_Enable();
    __MEM_Access_Enable(MEM_ACCESS_IAP_WRITE);
    __MEM_SetWriteMode(IAPErase);
    __MEM_MultipleWriteUnProtect();

    do {
        // Mem Flag Clear.
        MEM->STA.B[0] = (MEM_STA_WPEF_mask_b0 | MEM_STA_EOPF_mask_b0);
        __ISB();
        *lptrDest_addr = 0xFFFFFFFF;

        if((MEM->STA.B[0] & (MEM_STA_WPEF_mask_b0 | MEM_STA_EOPF_mask_b0)) != MEM_STA_EOPF_mask_b0)
        {
            lDRV_Return = DRV_Failure;
            break;
        }
      #if defined(MG32_1ST) || defined(MG32_2ND)
        lptrDest_addr += 0x100;
      #endif
      #if defined(MG32_3RD) || defined(MG32_4TH)
        lptrDest_addr += 0x80;
      #endif       
    } while(++lCount < PageQuantity);

    __MEM_UnProtect();
    __MEM_MultipleWriteProtect();
    __MEM_SetWriteMode(None);
    __MEM_Access_Disable(MEM_ACCESS_IAP_WRITE);
    __MEM_Disable();
    __MEM_Protect();

    return lDRV_Return;
}

//----------------------------------------------------------------------------------------
// Функция записывает в IAP 4-байтое число по адресу 
// Адрес в памяти должен быть кратен 4
//----------------------------------------------------------------------------------------
DRV_Return IAP_Single_Write(uint32_t IAPStartAddress, uint32_t ProgramData)
{
    // Проверить, включена ли RC-цепочка
    if(CSC->CR0.MBIT.IHRCO_EN == 0)
        return DRV_Failure;

    // Проверить кратность целевого адреса 4
    if(((uint32_t)IAPStartAddress & 0x03) != 0)
        return DRV_Failure;
	// Не выходим ли мы за края IAP-памяти?
    if(((IAPStartAddress) < 0x1A000000) || ((IAPStartAddress) >= 0x1C000000))
        return DRV_Failure;

    __MEM_UnProtect();
    __MEM_Enable();
    __MEM_Access_Enable(MEM_ACCESS_IAP_WRITE);
    __MEM_SetWriteMode(IAPProgram);
    __MEM_SingleWriteUnProtect();

    // Mem Flag Clear.
    MEM->STA.B[0] = (MEM_STA_WPEF_mask_b0 | MEM_STA_EOPF_mask_b0);
    __ISB();

    *(uint32_t *)IAPStartAddress = ProgramData;
	
    __MEM_UnProtect();
    __MEM_SetWriteMode(None);
    __MEM_Access_Disable(MEM_ACCESS_IAP_WRITE);
    __MEM_Disable();
    __MEM_Protect();

    // Check MEM Flash Flag
    if(((MEM->STA.B[0] & MEM_STA_WPEF_mask_b0) != 0) && ((MEM->STA.B[0] & MEM_STA_EOPF_mask_b0) == 0))
        return DRV_Failure;

    return DRV_Success;
}

//----------------------------------------------------------------------------------------
// Функция записывает произвольное количество 4-байтных чисел начиная со стартового адреса в ОЗУ
// Стартовый адрес в IAP должен быть кратен размеру страницы 
//----------------------------------------------------------------------------------------
DRV_Return IAP_Multiple_Write(uint32_t IAPStartAddress, uint32_t DataStartAddress, uint32_t Length)
{
    DRV_Return lSMP_Return = DRV_Success;
    uint32_t lCount;
    uint32_t *lptrSrc_addr;
    uint32_t *lptrDest_addr;
    

    // Проверить, включена ли RC-цепочка
    if(CSC->CR0.MBIT.IHRCO_EN == 0)
        return DRV_Failure;

    // Проверить кратность целевого адреса 4
    if(((IAPStartAddress & 0x03) != 0) && ((DataStartAddress & 0x03) != 0))
        return DRV_Failure;
	// Не выходим ли мы за края IAP-памяти?
    if(((IAPStartAddress) < 0x1A000000) || ((IAPStartAddress) >= 0x1C000000))
        return DRV_Failure;

    lptrSrc_addr = (uint32_t *)DataStartAddress;
    lptrDest_addr = (uint32_t *)IAPStartAddress;
    lCount = 0;

    __MEM_UnProtect();
    __MEM_Enable();
    __MEM_Access_Enable(MEM_ACCESS_IAP_WRITE);
    __MEM_SetWriteMode(IAPProgram);
    __MEM_MultipleWriteUnProtect();
    __MEM_Protect();

    do {
        // Mem Flag Clear.
        MEM->STA.B[0] = (MEM_STA_WPEF_mask_b0 | MEM_STA_EOPF_mask_b0);
        __ISB();
        *lptrDest_addr = *lptrSrc_addr;

        if((MEM->STA.B[0] & (MEM_STA_WPEF_mask_b0 | MEM_STA_EOPF_mask_b0)) != MEM_STA_EOPF_mask_b0)
        {
            lSMP_Return = DRV_Failure;
            break;
        }
        lptrSrc_addr ++;
        lptrDest_addr ++;
    } while(++lCount < Length);

    __MEM_UnProtect();
    __MEM_MultipleWriteProtect();
    __MEM_SetWriteMode(None);
    __MEM_Access_Disable(MEM_ACCESS_IAP_WRITE);
    __MEM_Disable();
    __MEM_Protect();

    return lSMP_Return;
}
