#include "flash.h"
#include "keys.h"
#include "variables.h"
#include "usart.h"
// отделить запись и чтение из флеша от записи ответной посылки в массив RecBytes
//

flash_block_t fpage;

void FlashTestFill(void)
{
	AddKey(ACTKEY_ACTIVATE, 0, 0, key1);
	AddKey(ACTKEY_DEACTIVATE, 1, 0, key2);
	AddKey(ACTKEY_NOACTION, 2, 0, key3);
	AddKey(ACTKEY_DEACTIVATE, 3, 0, key4);
	AddKey(ACTKEY_NOACTION, 4, 0, key5);
}

void FlashFirstInit(void)
{
	if (IAP_ReadWord(FIRST_WRITE_VALUE_POS) == __FIRST_WRITE_VALUE)
		return;
	
	// флаг записи флеша
	IAP_WriteSingleWord(FIRST_WRITE_VALUE_POS, __FIRST_WRITE_VALUE);
	// количество перезаписей
	IAP_WriteSingleWord(FLASH_RESOURCE_POS, __FLASH_RESOURCE);
	
	for (uint8_t i = 0; i < VAR_COUNT; i++)
	{
		IAP_WriteSingleWord(PAGE_NUMBER_VARS * IAP_PAGE_SIZE + variables[i]->indexOnPage,
							variables[i]->factoryValue);
	}
} 

uint32_t GetVariable(uint8_t varNumber)
{
	if (varNumber > VAR_COUNT) return UINT32_MAX;
	return IAP_ReadWord(PAGE_NUMBER_VARS * IAP_PAGE_SIZE + variables[varNumber]->indexOnPage * 4);
}

uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB)
{
	if (varNumber > VAR_COUNT_WRITABLE) return UINT32_MAX;
	
	uint16_t var = varValueLSB | (varValueMSB << 8);
	
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	fpage.word[variables[varNumber]->indexOnPage] = var;
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	
	return 0;
}

uint32_t DoCommand(uint8_t commNum, uint8_t commArg)
{
	if (commArg > 0x02) return UINT32_MAX;

	switch (commNum)
	{
		case COMM_ALLKEYACT: // (де)активация всех ключей
			
			CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
		
			for(uint16_t i = 0; i < IAP_PAGE_SIZE; i++)
			{
				if (fpage.byte[i] != KEY_STATUS_FREE) 
					fpage.byte[i] = commArg;
			}
			
			if (commArg == KEY_STATUS_DEACTIVATED)
				fpage.word[ACTIVE_KEYS_POS] = 0;
			else 
				fpage.word[ACTIVE_KEYS_POS] = fpage.word[TOTAL_KEYS_POS];
			
			IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
			CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
			
			break;
		
		case COMM_FACTORY_NUM: // к дефолтным значениям
			
			CopyFlashPageToRAM(PAGE_NUMBER_VARS);
		
			for(uint8_t i = 0; i < VAR_COUNT_WRITABLE; i++)
				fpage.word[variables[i]->indexOnPage] = variables[i]->factoryValue;
			
			fpage.word[FLASH_RESOURCE_POS]++;
		
			IAP_Erase_OnePage(PAGE_NUMBER_VARS);
			CopyRAMToFlashPage(PAGE_NUMBER_VARS);
		
			break;
		
		default:
			return UINT32_MAX;
	}	
	return 0;
}

uint32_t SetVariablePack(uint8_t *packStartAddr)
{
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	uint8_t *tmpAddr = packStartAddr;
	uint16_t var; 
	
	for (uint8_t i = 0; i < VAR_COUNT_WRITABLE; i++)
	{
		// отделяем двухбайтные переменные от однобайтных
		var = 0;
		for (uint8_t byteNum = 0; byteNum < variables[i]->byteSize; byteNum++)
			var |= *tmpAddr++ << (8 * byteNum);
		fpage.word[variables[i]->indexOnPage] = var;
	}

	fpage.word[FLASH_RESOURCE_POS]++;
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	return 0;
}


uint32_t ActivateKey(uint8_t operationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB)
{
	if (operationType > 0x01) return UINT32_MAX;
	
	uint16_t keyIndex = keyIndexLSB | (keyIndexMSB << 8);
	
	if (keyIndex >= IAP_PAGE_SIZE) return UINT32_MAX;
	
	if (GetKeyStatus(keyIndex) == KEY_STATUS_FREE) return UINT32_MAX;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	fpage.byte[keyIndex] = operationType;

	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	return 0;
}

uint32_t GetKeyStatus(uint16_t keyIndex)
{
	return IAP_ReadByte (PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE + keyIndex);
}

uint32_t AddKey(uint8_t activationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB, uint8_t *keyStartAddr)
{
	
	if (activationType > 0x02) return UINT32_MAX;
	
	uint16_t keyIndex = keyIndexLSB | (keyIndexMSB << 8);
	
	if (keyIndex >= IAP_PAGE_SIZE) return UINT32_MAX;
	
	uint8_t oldKeyStatus = GetKeyStatus(keyIndex);
	
	// изменяем переменные
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	
	switch (oldKeyStatus)
	{
		case KEY_STATUS_FREE:
			fpage.word[TOTAL_KEYS_POS]++;
			if (activationType == ACTKEY_ACTIVATE)
				fpage.word[ACTIVE_KEYS_POS]++;	
			break;
		
		case KEY_STATUS_DEACTIVATED:
			if (activationType == ACTKEY_ACTIVATE)
				fpage.word[ACTIVE_KEYS_POS]++;	
			break;
		
		case KEY_STATUS_ACTIVATED:
			if (activationType == ACTKEY_DEACTIVATE)
				fpage.word[ACTIVE_KEYS_POS]--;	
			break;
		
		default:
			break;
	}

	fpage.word[FLASH_RESOURCE_POS]++;
	
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	
	
	// добавляем/меняем сам ключ
	
	uint8_t keyPageNum = PAGE_NUMBER_KEYS_0 + keyIndex / KEYS_COUNT_ON_PAGE; // номер страницы, на которой находится целевой ключ
	uint8_t keyPosOnPage = (keyIndex % KEYS_COUNT_ON_PAGE) * KEY_ENCRYPTED_SIZE; // позиция ключа на странице флеша (номер байта)

	CopyFlashPageToRAM(keyPageNum); 
	memcpy(&fpage.byte[keyPosOnPage], keyStartAddr, KEY_ENCRYPTED_SIZE);

	IAP_Erase_OnePage(keyPageNum);
	CopyRAMToFlashPage(keyPageNum);
	
	// изменяем статус ключа
	
	if (activationType == oldKeyStatus)
		return 0;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	
	if ((activationType == ACTKEY_NOACTION) && (oldKeyStatus == KEY_STATUS_FREE))
		fpage.byte[keyIndex] = KEY_STATUS_DEACTIVATED;
	else 
		fpage.byte[keyIndex] = activationType;
	
	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	
	return 0;
}

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


