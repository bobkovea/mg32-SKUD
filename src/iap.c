#include "iap.h"

/* 	
	Для работы с пользовательским флешем рекомендуется использовать функционал iap.h.
	Функции ниже использовать напрямую тоже можно, но они менее удобны.
*/


/*----------------------------------------------------------------------------------------
// Функция очищает произвольное количества страниц, начиная с выбранного адреса
// Args: 	StartPageAddress - адрес начала страницы (д.б. кратен IAP_PAGE_SIZE!)
			PageQuantity - количество стираемых страниц
----------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------
// Функция записывает в IAP слово (4 байта) по выбранному адресу 
// Args: 	IAPStartAddress - адрес в памяти (д.б. кратен 4!)
			ProgramData - записываемое значение
----------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------
// Функция записывает в IAP произвольное количество слов (4 байта), начиная со стартового адреса
// Args: 	IAPStartAddress - стартовый адрес в IAP (д.б. кратен 4!)
			DataStartAddress -  стартовый адрес в ОЗУ
			Length - длина записываемых данных (в словах)
----------------------------------------------------------------------------------------*/

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
