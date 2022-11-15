#include "flash_static.h"
#include "keys.h"
#include "variables.h"

// отделить запись и чтение из флеша от записи ответной посылки в массив RecBytes
//

flash_block_t fpage;

void FlashFirstInit(void)
{
	InitVariables();
	
	if (IAP_ReadWord(FIRST_WRITE_VALUE_POS) == __FIRST_WRITE_VALUE)
		return;
	
	// флаг записи флеша
	IAP_Single_Write(IAP_START_ADDRESS, __FIRST_WRITE_VALUE);
	
	// изменить singlewrite на обертку над ним WriteWord (изменить для одного значения)
	// добавить функцию WriteMultipleWord
	for (uint8_t i = 0; i < VAR_COUNT; i++)
	{
		IAP_Single_Write(IAP_START_ADDRESS + PAGE_NUMBER_VARS * IAP_PAGE_SIZE + variables[i]->indexOnROMPage * 4,
						 variables[i]->factoryValue);
	}
	


//	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
//	

//	
//	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
//	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	
	
} 

uint32_t GetVariable(uint8_t varNumber)
{
	if (varNumber > VAR_COUNT) return UINT32_MAX;
	return IAP_ReadWord(variables[varNumber]->indexOnROMPage);
}


uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB)
{
	if (varNumber > VAR_COUNT_WRITABLE) return UINT32_MAX;
	
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	fpage.word[variables[varNumber]->indexOnROMPage] = varValueLSB | (varValueMSB << 8);
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
			
			for(uint16_t i = 0; i < VAR_COUNT_WRITABLE; i++)
				fpage.word[variables[i]->indexOnROMPage] = fpage.word[variables[i]->factoryValue];
		break;
		
		default:
			return UINT32_MAX;
	}
	// fpage.word[FLASH_RESOURCE_POS]--;
	
	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
			
	return 0;
}

uint32_t SetVariablePack(uint8_t *packStartAddr)
{
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	
	for (uint8_t i = 0; i < VAR_COUNT_WRITABLE; i++, packStartAddr++)
	{
		if (variables[i]->byteSize == 1)
		{
			fpage.word[variables[i]->indexOnROMPage] = *packStartAddr;
		}

		else if (variables[i]->byteSize == 2)
		{
			fpage.word[variables[i]->indexOnROMPage] = *packStartAddr++;
			fpage.word[variables[i]->indexOnROMPage] |= *packStartAddr << 8;
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
	if (GetKeyStatus(keyIndex) == KEY_STATUS_FREE) return UINT32_MAX;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	fpage.byte[keyIndex] = operationType;

	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	return 0;
}

uint32_t GetKeyStatus(uint16_t keyIndex)
{
	if (keyIndex > IAP_PAGE_SIZE) return UINT32_MAX;
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
	uint8_t keyPos = (keyIndex % KEYS_COUNT_ON_PAGE) * KEY_ENCRYPTED_SIZE; // позиция ключа на странице флеша (номер байта)
	
	CopyFlashPageToRAM(keyPageNum);
	
	for (uint8_t i = 0; i < KEY_ENCRYPTED_SIZE; i++) // memcpy
		fpage.byte[keyPos] = *keyStartAddr++;

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


