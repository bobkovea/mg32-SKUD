#include "flash.h"
#include "keys.h"
#include "variables.h"
#include "usart.h"
#include "events.h"
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

//----------------------------------------------------------------------------------------
// Функция единократно вызывается после первого старта микроконтроллера
// Если включение первое, копируем значения переменных по умолчанию во флеш
// Если включение не первое, то копируем значения переменных из флеша в ОЗУ
//----------------------------------------------------------------------------------------

void FlashFirstInit(void)
{
	// если включение не первое
	if (IAP_ReadWord(FIRST_WRITE_VALUE_POS) == __FIRST_WRITE_VALUE)
	{
		// копируем переменные из флеша в ОЗУ
		for (uint8_t i = 0; i < VAR_COUNT; i++)
			variables[i]->value = IAP_ReadWord(PAGE_NUMBER_VARS * IAP_PAGE_SIZE / 4 
												+ variables[i]->indexOnPage); 
	
		FlashResourse.value = GetMaxFlashResource();
		
		// копируем события из флеша в ОЗУ
		for (uint32_t i = 0; i < EVENT_COUNT; i++)
		{

			events[i]->time = IAP_ReadWord(PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 
												+ events[i]->eventNum * 10 + 0); 
			events[i]->status = IAP_ReadWord(PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 
												+ events[i]->eventNum * 10 + 1); 
			events[i]->repetitionCount = IAP_ReadWord(PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 
												+ events[i]->eventNum * 10 + 2); 
		}
		//+дефолтные ключи (мб мастер)
	}
	
	
	else // если включение первое
	{
		
	// количество перезаписей на всех страницах кроме ключей = 1
	IAP_WriteSingleWord(FLASH_RESOURCE_POS + PAGE_NUMBER_VARS * IAP_PAGE_SIZE / 4, __FLASH_RESOURCE);
	IAP_WriteSingleWord(FLASH_RESOURCE_POS + PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 , __FLASH_RESOURCE);
	IAP_WriteSingleWord(FLASH_RESOURCE_POS + PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE / 4, __FLASH_RESOURCE);
	
		// копируем значения переменных из ОЗУ во флеш
	for (uint8_t i = 0; i < VAR_COUNT; i++)
		IAP_WriteSingleWord(PAGE_NUMBER_VARS * IAP_PAGE_SIZE / 4 + variables[i]->indexOnPage,
							variables[i]->factoryValue);

	
		// копируем значения событий из ОЗУ во флеш
		for (uint32_t i = 0; i < EVENT_COUNT; i++)
		{

			IAP_WriteSingleWord(PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 + events[i]->eventNum * 10 + 0 ,
								events[i]->time); 
			IAP_WriteSingleWord(PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 + events[i]->eventNum * 10 + 1 ,
								events[i]->status); 
			IAP_WriteSingleWord(PAGE_NUMBER_EVENTS * IAP_PAGE_SIZE / 4 + events[i]->eventNum * 10 + 2 ,
								events[i]->repetitionCount); 
		}
	
	// флаг записи флеша
	IAP_WriteSingleWord(FIRST_WRITE_VALUE_POS + PAGE_NUMBER_VARS * IAP_PAGE_SIZE / 4, __FIRST_WRITE_VALUE);
	}

} 

//----------------------------------------------------------------------------------------
// Функция извлекает из IAP значение переменной по её порядковому номеру в протоколе
// Args: 	varNumber - порядковый номер переменной по протоколу
// Returns: значение переменной (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t GetVariable(uint8_t varNumber)
{
	if (varNumber > VAR_COUNT) return FAILURE;
	return IAP_ReadWord(PAGE_NUMBER_VARS * IAP_PAGE_SIZE + variables[varNumber]->indexOnPage * 4);
}

//----------------------------------------------------------------------------------------
// Функция устанавливает значение одной переменной в IAP по её порядковому номеру в протоколе
// Args: 	varNumber - порядковый номер переменной по протоколу
// 			varValueLSB - младший байт значения переменной; 
// 			varValueMSB - старший байт значения переменной
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB)
{
	if (varNumber > VAR_COUNT_WRITABLE) return FAILURE;
	
	uint16_t var = varValueLSB | (varValueMSB << 8);
	
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	fpage.word[variables[varNumber]->indexOnPage] = var;
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	
	return SUCCESS;
}


//----------------------------------------------------------------------------------------
// Функция устанавливает значение всех переменных в IAP по протоколу 
// Args: 	packStartAddr - указатель на начало массива с переменными
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

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
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция устанавливает статус ключа в IAP
// Args:	operationType - тип операции (деактивация или активация)
// 			keyIndexLSB - младший байт индекса ключа; 
// 			keyIndexMSB - старший байт индекса ключа
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t ActivateKey(uint8_t operationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB)
{
	if (operationType > 0x01) return FAILURE;
	
	uint16_t keyIndex = keyIndexLSB | (keyIndexMSB << 8);
	
	if (keyIndex >= IAP_PAGE_SIZE) return FAILURE;
	
	if (GetKeyStatus(keyIndex) == KEY_STATUS_FREE) return FAILURE;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	fpage.byte[keyIndex] = operationType;

	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция реализует выполнение общих команд по протоколу
// Args:	commNum - порядковый номер команды по протоколу
// 			commArg - аргумент команды по протоколу; 
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t DoCommand(uint8_t commNum, uint8_t commArg)
{
	if (commArg > 0x02) return FAILURE;

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
			
			if (СheckFlashResource(PAGE_NUMBER_KEYSTATUS) != FAILURE)
				fpage.word[FLASH_RESOURCE_POS]++;
						
			IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
			CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
			
			break;
		
		case COMM_FACTORY_NUM: // к дефолтным значениям
			
			CopyFlashPageToRAM(PAGE_NUMBER_VARS);
		
			for(uint8_t i = 0; i < VAR_COUNT_WRITABLE; i++)
				fpage.word[variables[i]->indexOnPage] = variables[i]->factoryValue;
			
			if (СheckFlashResource(PAGE_NUMBER_VARS) == SUCCESS)
				fpage.word[FLASH_RESOURCE_POS]++;
				
		
			IAP_Erase_OnePage(PAGE_NUMBER_VARS);
			CopyRAMToFlashPage(PAGE_NUMBER_VARS);
		
			break;
		
		default:
			return FAILURE;
	}	
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция реализует операцию добавления/изменения ключей доступа по индексу
// Args:	activationType - новый статус активации ключа после выполнения операции
// 			keyIndexLSB - младший байт индекса ключа; 
// 			keyIndexMSB - старший байт индекса ключа;
//			keyStartAddr - указатель на первый байт ключа в массиве
//			
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t AddKey(uint8_t activationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB, uint8_t *keyStartAddr)
{
	
	if (activationType > 0x02) return FAILURE;
	
	uint16_t keyIndex = keyIndexLSB | (keyIndexMSB << 8);
	
	if (keyIndex >= IAP_PAGE_SIZE) return FAILURE;
	
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
		return SUCCESS;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	
	if ((activationType == ACTKEY_NOACTION) && (oldKeyStatus == KEY_STATUS_FREE))
		fpage.byte[keyIndex] = KEY_STATUS_DEACTIVATED;
	else 
		fpage.byte[keyIndex] = activationType;
	
	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
	
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция извлекает из IAP статус ключа по его индексу
// Args: 	keyIndex - индекс ключа
// Returns: статус активации ключа по протоколу
//----------------------------------------------------------------------------------------

uint32_t GetKeyStatus(uint16_t keyIndex)
{
	return IAP_ReadByte (PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE + keyIndex);
}


//----------------------------------------------------------------------------------------
// Функция определяет максимальное значение количества перезаписей среди всех страниц IAP
// Args: 	pageNumber - порядковый номер страницы в IAP
// Returns: максимальное количество перезаписей среди всех страниц IAP
//----------------------------------------------------------------------------------------

uint32_t GetMaxFlashResource(void)
{
	uint32_t curFlashResource = 0;
	uint32_t maxFlashResource = 0;
	
	for (uint8_t i = 0; i < 3; i++)
    {
		curFlashResource = IAP_ReadWord (i * IAP_PAGE_SIZE / 4 + FLASH_RESOURCE_POS);
		
		if (curFlashResource > maxFlashResource)
			maxFlashResource = curFlashResource;
    }
	return maxFlashResource;
}

//----------------------------------------------------------------------------------------
// Функция увеличивает общий счетчик перезаписей IAP после перезаписи страницы (если это требуется)
// Args: 	pageNumber - порядковый номер страницы в IAP
// Returns: 0 - увеличили значение
//			UINT32_MAX - не увеличили значение	
//----------------------------------------------------------------------------------------
uint32_t IncreaseFlashResource(uint8_t curPageNumber)
{

	uint8_t curPageResource = IAP_ReadWord (curPageNumber * IAP_PAGE_SIZE / 4 + FLASH_RESOURCE_POS);

	if (curPageResource > GetMaxFlashResource())
		return FAILURE;
	fpage.word[FLASH_RESOURCE_POS]++;
	return SUCCESS;
}



//----------------------------------------------------------------------------------------
// Функция копирует информацию со страницы IAP в "буфер-копию" страницы в ОЗУ
// Args:	pageNumber - порядковый номер страницы в IAP
// Returns: 0 (успех)
//----------------------------------------------------------------------------------------

uint32_t CopyFlashPageToRAM(uint8_t pageNumber)
{
	IAP_CopyIAPInRAM(pageNumber * IAP_PAGE_SIZE, &fpage, IAP_PAGE_SIZE);
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция копирует информацию из "буфера-копии" в ОЗУ на страницу IAP
// Args:	pageNumber - порядковый номер страницы в IAP
// Returns: 0 (успех)
// 			1 (ошибка)
//----------------------------------------------------------------------------------------

uint32_t CopyRAMToFlashPage(uint8_t pageNumber)
{
	return IAP_CopyRAMInIAP(pageNumber * IAP_PAGE_SIZE, &fpage, IAP_PAGE_SIZE);
}


