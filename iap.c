#include "iap.h"

//----------------------------------------------------------------------------------------
// Функция выделяет память под IAP
// Выделяемая память не может быть меньше одной страницы (512 или 1024 байта в зависимости от контроллера)
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
void IAP_Erase_OnePage (uint16_t PageNumber)
{
	IAP_Erase_Page(IAP_START_ADDRESS + (IAP_PAGE_SIZE * PageNumber), 1);
}

//----------------------------------------------------------------------------------------
// Функция очищает всю выделенную под IAP flash-память
//----------------------------------------------------------------------------------------
void IAP_FullErase(void)
{
	IAP_Erase_Page(IAP_START_ADDRESS, MEM_GetIAPSize() / IAP_PAGE_SIZE);
}


//----------------------------------------------------------------------------------------
// Функция читает 1 байт из IAP по индексу байта
// Индекс изменяется от 0 до размера выделенной IAP
//----------------------------------------------------------------------------------------
uint8_t IAP_ReadByte(uint32_t ByteIndexInIAP)
{
	return *(uint8_t *)(IAP_START_ADDRESS + ByteIndexInIAP);
}


//----------------------------------------------------------------------------------------
// Функция читает слово (4 байта) из IAP по индексу байта
// Индекс изменяется от 0 до размера выделенной IAP
//----------------------------------------------------------------------------------------
uint32_t IAP_ReadWord(uint32_t ByteIndexInIAP)
{
	return *(uint32_t *)(IAP_START_ADDRESS + ByteIndexInIAP);
}

//----------------------------------------------------------------------------------------
// Функция записывает слово (4 байта) по индексу
// Индекс изменяется от 0 до размера выделенной IAP / 4
//----------------------------------------------------------------------------------------
uint8_t IAP_WriteSingleWord(uint32_t WordIndexInIAP, uint32_t WordValue)
{
	return IAP_Single_Write(IAP_START_ADDRESS + (WordIndexInIAP * 4), WordValue);
} 


//----------------------------------------------------------------------------------------
// Функция записывает поток слов (4 байта) начиная с индекса памяти
// Индекс изменяется от 0 до размера выделенной IAP / 4
//----------------------------------------------------------------------------------------
uint8_t IAP_WriteMultipleWord(uint32_t WordIndexInIAP, uint32_t DataStartAddress, uint32_t Length)
{
	return IAP_Multiple_Write(IAP_START_ADDRESS + (WordIndexInIAP * 4), DataStartAddress, Length);
} 


//----------------------------------------------------------------------------------------
// Функция копирует данные из структуры в ОЗУ в IAP, возвращает успех (0) или нет (1)
// StartIndex - стартовый индекс в IAP (должен быть кратен 4!);
// StructInRAMPointer - указатель на структуру с данными;
// StructInRAMSize - размер структуры в байтах (должен быть кратен 4!).
//----------------------------------------------------------------------------------------
uint8_t IAP_CopyRAMInIAP(uint32_t StartByteIndex, void *StructInRAMPointer, uint32_t StructInRAMSize)
{
	return IAP_Multiple_Write(IAP_START_ADDRESS + StartByteIndex, 
								(uint32_t)StructInRAMPointer, 
								StructInRAMSize / 4);
}

//----------------------------------------------------------------------------------------
// Функция копирует данные из IAP в структуру ОЗУ
// StartIndex - стартовый индекс в IAP;
// StructInRAMPointer - указатель на структуру с данными;
// StructInRAMSize - размер структуры в байтах.
//----------------------------------------------------------------------------------------
void IAP_CopyIAPInRAM(uint32_t StartByteIndex, void *StructInRAMPointer, uint32_t StructInRAMSize)  
{ 	
	memcpy(StructInRAMPointer, 
			(void *) (IAP_START_ADDRESS + StartByteIndex), 
			StructInRAMSize);
}


//----------------------------------------------------------------------------------------
// Функция сравнивает состояние структуры в IAP со структурой в ОЗУ
// StartByteIndex - стартовый индекс байта в IAP;
// StructInRAMPointer - указатель на структуру с данными;
// StructInRAMSize - размер структуры в байтах.
//----------------------------------------------------------------------------------------
uint8_t IAP_IsEqualToRAM(uint32_t StartByteIndex, void *StructInRAMPointer, uint32_t StructInRAMSize) 
{
	return !memcmp((void *) (IAP_START_ADDRESS + StartByteIndex), 
					StructInRAMPointer, 
					StructInRAMSize);
}

//----------------------------------------------------------------------------------------
// Функция проверяет область выделенной памяти на девственную чистоту
// Индекс от нуля до размера выделенной области в байтах
//----------------------------------------------------------------------------------------
uint32_t IAP_IsAreaEmpty(uint32_t StartIndex, uint32_t EndIndex)
{
	for (uint32_t i = StartIndex; i <= EndIndex; i++) {
		if (IAP_ReadByte(i) != 0xFF)
			return 0;
	}
	return 1;
}

//----------------------------------------------------------------------------------------
// Функция проверяет всю выделенную память на девственную чистоту
//----------------------------------------------------------------------------------------
uint32_t IAP_IsFullEmpty(void) 
{
	return IAP_IsAreaEmpty(0, MEM_GetIAPSize() - 1);
}


//----------------------------------------------------------------------------------------
// Функция возвращает номер страницы байта по индексу
// Индекс изменяется от 0 до размера выделенной IAP
//----------------------------------------------------------------------------------------
uint32_t IAP_GetPageNumberOfByte(uint32_t ByteIndexInIAP)
{
	return ByteIndexInIAP / IAP_PAGE_SIZE;
} 

//----------------------------------------------------------------------------------------
// Функция возвращает количество выделенных страниц для IAP
//----------------------------------------------------------------------------------------
uint32_t IAP_GetNumberOfPages()
{
	return MEM_GetIAPSize() / IAP_PAGE_SIZE;
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
