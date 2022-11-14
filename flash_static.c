#include "flash_static.h"

// отделить запись и чтение из флеша от записи ответной посылки в массив RecBytes



flash_block_t fpage;

uint8_t VarsLenMas[READABLE_VAR_COUNT] = { 2, 2, 2, 2, 1, 1, 1, 2, 2, 2 };

// позиции переменных на странице 
uint8_t VarIndexInROM[READABLE_VAR_COUNT] =
{ 
	GERKON_FILT_TIME_POS, // 0x00
	SEND_ALARM_TIME_POS, // 0x01
	REACTIVATE_ALARM_TIME_POS, // 0x02
	BUZZER_OFF_TIME_POS, // 0x03
	SEND_OFFLINE_EVENTS_POS, // 0x04
	FREE_ACCESS_POS, // 0x05
	MASTER_SLAVE_POS, // 0x06
	TOTAL_KEYS_POS, // 0x07
	ACTIVE_KEYS_POS, // 0x08
	FLASH_RESOURCE_POS // 0x09
};

// позиции дефолтных значений переменных на странице 
uint8_t __VarIndexInROM[WRITABLE_VAR_COUNT] =
{ 
	__GERKON_FILT_TIME_POS, // 0x00
	__SEND_ALARM_TIME_POS, // 0x01
	__REACTIVATE_ALARM_TIME_POS, // 0x02
	__BUZZER_OFF_TIME_POS, // 0x03
	 __SEND_OFFLINE_EVENTS_POS, // 0x04
	__FREE_ACCESS_POS, // 0x05
	__MASTER_SLAVE_POS // 0x06
};



uint32_t GetVariable(uint8_t varCode)
{
	if (varCode > READABLE_VAR_COUNT) return UINT32_MAX;
	return IAP_ReadWord(VarIndexInROM[varCode]);
}


uint32_t SetVariable(uint8_t varCode, uint8_t varValueLSB, uint8_t varValueMSB)
{
	if (varCode > WRITABLE_VAR_COUNT) return UINT32_MAX;
	
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	fpage.word[VarIndexInROM[varCode]] = varValueLSB | (varValueMSB << 8);
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	return 0;
}

uint32_t DoCommand(uint8_t commNum, uint8_t commArg)
{
	if (commNum > 0x01) return UINT32_MAX;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	
	switch (commNum)
	{
		
		case COMM_ALLKEYACT: // (де)активация всех ключей
			
			for(uint16_t i = 0; i < IAP_PAGE_SIZE; i++)
			{
				if (fpage.byte[i] != KEY_STATUS_FREE)
					fpage.byte[i] = commArg;
			}
			
			if (commArg == KEY_STATUS_DEACTIVATED)
				fpage.word[ACTIVE_KEYS_POS] = 0;
			else 
				fpage.word[ACTIVE_KEYS_POS] = fpage.word[TOTAL_KEYS_POS];				
		break;
		
		
		case COMM_FACTORY_NUM: // к дефолтным значениям
			
			for(uint16_t i = 0; i < WRITABLE_VAR_COUNT; i++)
				fpage.word[VarIndexInROM[i]] = fpage.word[__VarIndexInROM[i]];
		break;
		
		default:
			return UINT32_MAX;
	}
	// fpage.word[FLASH_RESOURCE_POS]--; потом добавить на каждую стр? перезаписывать первую?
		IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
		CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
			
	return 0;
}

uint32_t SetVariablePack(uint8_t *packStartAddr)
{
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	
	for (uint8_t i = 0; i < WRITABLE_VAR_COUNT; i++, packStartAddr++)
	{
		if (VarsLenMas[i] == 1)
		{
			fpage.word[VarIndexInROM[i]] = *packStartAddr;
		}

		else if (VarsLenMas[i] == 2)
		{
			fpage.word[VarIndexInROM[i]] = *packStartAddr++;
			fpage.word[VarIndexInROM[i]] |= *packStartAddr << 8;
		}
	}
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	return 0;
}



uint32_t ActivateKey(uint8_t operationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB)
{
	uint16_t keyIndex = keyIndexLSB | (keyIndexMSB << 8);
	
	if (keyIndex >= IAP_PAGE_SIZE) return UINT32_MAX;
	if (IAP_ReadByte(PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE + keyIndex) == KEY_STATUS_FREE) return UINT32_MAX;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	fpage.byte[keyIndex] = operationType;

	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	return 0;
}


uint32_t AddKey(uint8_t newStatus, uint8_t keyIndexLSB, uint8_t keyIndexMSB, uint8_t *keyMSB)
{
	if (newStatus > 0x02) return UINT32_MAX;
	
	uint16_t keyIndex = keyIndexLSB | (keyIndexMSB << 8);
	if (keyIndex >= IAP_PAGE_SIZE) return UINT32_MAX;
	
	uint8_t keyPage = PAGE_NUMBER_KEYS_1 + keyIndex / 64;
	
	CopyFlashPageToRAM(keyPage);
	
	for (uint8_t i = 0; i < 16; i++)
	{
	keyIndex % 64
	}
	IAP_CopyIAPInRAM(pageNumber * IAP_PAGE_SIZE, &fpage, IAP_PAGE_SIZE);
	return 0;
}



//uint32_t CheckValidKey(uint8_t keyIndex)
//{
//	if (IAP_ReadByte(PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE + keyIndex) == KEY_STATUS_ACTIVATED)
//	return 0; // return KEY_OK
//}


uint32_t CopyFlashPageToRAM(uint8_t pageNumber)
{
	IAP_CopyIAPInRAM(pageNumber * IAP_PAGE_SIZE, &fpage, IAP_PAGE_SIZE);
	return 0;
}

uint32_t CopyRAMToFlashPage(uint8_t pageNumber)
{
	IAP_CopyRAMInIAP(pageNumber * IAP_PAGE_SIZE, &fpage, IAP_PAGE_SIZE);
	return 0;
}

//uint32_t CheckValidKey(uint8_t keyIndex)
//{
//	if (IAP_ReadByte(PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE + keyIndex) == KEY_STATUS_ACTIVATED)
//	return 0; // return KEY_OK
//}




