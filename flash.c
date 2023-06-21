#include "flash.h"
#include "keys.h"
#include "variables.h"
#include "usart.h"
#include "md5.h"

// отделить запись и чтение из флеша от записи ответной посылки в массив RecBytes

flash_block_t fpage;

void FlashTestFill(void)
{
	MD5_MakeHash(key1, KEY_RAW_SIZE, KeyEncrypted);
	AddKey(ACTKEY_ACTIVATE, 0, 0, KeyEncrypted); 
//	
//	MD5_MakeHash(key2, KEY_RAW_SIZE, KeyEncrypted);
//	AddKey(ACTKEY_ACTIVATE, 1, 0, KeyEncrypted);
//	
//	MD5_MakeHash(key_em_1, KEY_RAW_SIZE, KeyEncrypted);
//	AddKey(ACTKEY_ACTIVATE, 2, 0, KeyEncrypted);
//	
//	MD5_MakeHash(key_em_2, KEY_RAW_SIZE, KeyEncrypted);
//	AddKey(ACTKEY_ACTIVATE, 3, 0, KeyEncrypted);
}

//----------------------------------------------------------------------------------------
// Функция вызывается сразу после старта микроконтроллера
// Если включение первое, копируем значения переменных по умолчанию во флеш
// Если включение не первое, то наиборот копируем значения переменных из флеша в ОЗУ
//----------------------------------------------------------------------------------------

void PowerOnHandle(void)
{
	// если включение НЕ ПЕРВОЕ
	if (IAP_ReadWord(PAGE_NUMBER_VARS, FIRST_WRITE_VALUE_POS) == __FIRST_WRITE_VALUE)
	{
		// копируем переменные из флеша в ОЗУ
		for (uint8_t i = 0; i < VAR_PAGE0_COUNT; i++)
			variables[i]->value = IAP_ReadWord(PAGE_NUMBER_VARS, variables[i]->indexOnPage); 
		
		TotalKeys.value = IAP_ReadWord(PAGE_NUMBER_KEYSTATUS, TotalKeys.indexOnPage); 
		ActiveKeys.value = IAP_ReadWord(PAGE_NUMBER_KEYSTATUS, ActiveKeys.indexOnPage);
		
		// кол-во перезаписей флеша = максимальное кол-во со всех страниц
		FlashResourse.value = GetMaxFlashResource();
		
		// если не успели отправить ключ до отключения питания (и если он вообще был, конечно же)
		if ( ValidKeyIndex.value != ValidKeyIndex.factoryValue)
			CopyKeyByIndex(ValidKeyIndex.value, KeyEncrypted);
	}
	
	else // если включение ПЕРВОЕ
	{
		// выставляем флаг первой записи флеша
		IAP_WriteSingleWord(PAGE_NUMBER_VARS, FIRST_WRITE_VALUE_POS, __FIRST_WRITE_VALUE);
		
		// количество перезаписей на всех страницах (кроме ключей) = 1
		IAP_WriteSingleWord(PAGE_NUMBER_VARS, FLASH_RESOURCE_POS, __FLASH_RESOURCE);
		IAP_WriteSingleWord(PAGE_NUMBER_KEYSTATUS, FLASH_RESOURCE_POS, __FLASH_RESOURCE);
		
		// копируем значения переменных по умолчанию из ОЗУ во флеш
		for (uint8_t i = 0; i < VAR_PAGE0_COUNT; i++)
			IAP_WriteSingleWord(PAGE_NUMBER_VARS, variables[i]->indexOnPage, variables[i]->factoryValue);
		
		IAP_WriteSingleWord(PAGE_NUMBER_KEYSTATUS, TotalKeys.indexOnPage, TotalKeys.factoryValue);
		IAP_WriteSingleWord(PAGE_NUMBER_KEYSTATUS, ActiveKeys.indexOnPage, ActiveKeys.factoryValue);
		
		// + добавим ключи по умолчанию и их статусы (мб т.н. мастер-ключ)
		FlashTestFill(); 
	}
	
	/* Перевод передаваемых величин во внутренние переменные таймеров */
	gerkonFilterMax = GerkonFiltTime.value / 5; // т.к. период таймера = 5 мс и ед.изм. - мс
	protectionDelayMax = ProtectionDelayTime.value * 60000 / 5; // т.к. период таймера = 5 мс и ед.изм. - мин
	alarmTimeoutMax = BuzzerOffTime.value * 60000 / 100; // т.к. период таймера = 100 мс и ед.изм. - мин
}



//----------------------------------------------------------------------------------------
// Функция извлекает из IAP значение переменной по её порядковому номеру в протоколе
// Args: 	varNumber - порядковый номер переменной по протоколу
// Returns: значение переменной (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t GetVariable(uint8_t varNumber)
{
	if (varNumber > VAR_TOTAL_COUNT - 1) return FAILURE;
	return variables[varNumber]->value;
}

//----------------------------------------------------------------------------------------
// Функция извлекает из IAP значение переменной по её порядковому номеру в протоколе
// И копирует его по переданному адресу
// Args: 	varNumber - порядковый номер переменной по протоколу
// 			dest - адрес, по какому будет лежать скопированная переменная
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка)
//----------------------------------------------------------------------------------------

uint32_t CopyVariable(uint8_t varNumber, void *dest)
{
	if (varNumber > VAR_TOTAL_COUNT - 1) return FAILURE;
	*(uint16_t *)dest = variables[varNumber]->value;
	return SUCCESS;
}

uint32_t CopyVariablePack(void *dest)
{
	uint8_t *tmpAddr = dest;
	uint16_t var;
	for (uint8_t varNum = 0; varNum < VAR_TOTAL_COUNT; varNum++)
	{
		var = variables[varNum]->value;
	
		// отделяем двухбайтные переменные от однобайтных
		for (uint8_t byteNum = 0; byteNum < variables[varNum]->byteSize; byteNum++)
		{
			*tmpAddr++ = var >> (8 * byteNum);
		}
	}
	return SUCCESS;
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
	if (varNumber > VAR_WRITABLE_COUNT) return FAILURE;
	
	uint16_t varNew = varValueLSB | varValueMSB << 8;
	
	if (varNew == variables[varNumber]->value)
		return SUCCESS;
	
	variables[varNumber]->value = varNew;
	
	CopyVariablesPage0ToFlash();
	
	/* Перевод передаваемых величин во внутренние переменные таймеров */
	gerkonFilterMax = GerkonFiltTime.value / 5; // т.к. период таймера = 5 мс и ед.изм. - мс
	protectionDelayMax = ProtectionDelayTime.value * 60000 / 5; // т.к. период таймера = 5 мс и ед.изм. - мин
	alarmTimeoutMax = BuzzerOffTime.value * 60000 / 100; // т.к. период таймера = 100 мс и ед.изм. - мин
	
	/*
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	fpage.word[variables[varNumber]->indexOnPage] = variables[varNumber]->value = varNew; // -->ram & iap
	fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_VARS);
	
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	CopyRAMToFlashPage(PAGE_NUMBER_VARS);
	*/
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
	uint16_t varNew;
	uint8_t *tmpAddr = packStartAddr;
	
	// если передаваемые значения идентичны существующим, то не нужно перезаписывать флеш
	for(uint8_t i = 0; i < VAR_WRITABLE_COUNT; i++)
	{
		varNew = 0;
			
		for (uint8_t byteNum = 0; byteNum < variables[i]->byteSize; byteNum++)
			varNew |= *tmpAddr++ << (8 * byteNum);
			
		if (variables[i]->value != varNew)
			break;
		else 
		{
			if (i == VAR_WRITABLE_COUNT - 1)
					return SUCCESS;
		}
	}
		
	// собственно функция
	CopyFlashPageToRAM(PAGE_NUMBER_VARS);
				
	tmpAddr = packStartAddr;
				
	for (uint8_t i = 0; i < VAR_WRITABLE_COUNT; i++)
	{
		// отделяем двухбайтные переменные от однобайтных
		varNew = 0;
		for (uint8_t byteNum = 0; byteNum < variables[i]->byteSize; byteNum++)
			varNew |= *tmpAddr++ << (8 * byteNum);
		
		fpage.word[variables[i]->indexOnPage] = variables[i]->value = varNew; // --> ram & iap
	}
	
	fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_VARS);

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

uint32_t ActivateKey(uint8_t activationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB)
{
	// если неверный аргумент
	if (activationType > 0x01) return FAILURE;
	
	// если не записано ни одного ключа (нечего активировать) 
	if (TotalKeys.value == 0) return FAILURE;
	
	uint16_t keyIndex = keyIndexLSB | keyIndexMSB << 8;
	
	// если индекс выходит за пределы
	if (keyIndex > KEYS_MAX_INDEX) return FAILURE;
	
	// получаем текущий статус ключа
	uint8_t curKeyIndexStatus = GetKeyStatus(keyIndex);
	
	// если ключа нет под данным индексом
	if (curKeyIndexStatus == KEY_STATUS_FREE)
		return FAILURE;
	
	// если статус активации ключа уже выставлен
	if (curKeyIndexStatus == activationType)
		return SUCCESS;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	
	if (activationType == ACTKEY_ACTIVATE)
	{
		fpage.byte[keyIndex] = KEY_STATUS_ACTIVATED;
		fpage.word[ActiveKeys.indexOnPage] = ++ActiveKeys.value;
	}
	else
	{
		fpage.byte[keyIndex] = KEY_STATUS_DEACTIVATED;
		fpage.word[ActiveKeys.indexOnPage] = --ActiveKeys.value;
	}
	
	fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_KEYSTATUS);

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
	switch (commNum)
	{		
		case COMM_ALLKEYACT: // (де)активация всех ключей
			
			if (commArg > 0x01) return FAILURE;

			if (TotalKeys.value == 0)
				return FAILURE;
			
			if (ActiveKeys.value == TotalKeys.value && commArg == ACTKEY_ACTIVATE)
				return SUCCESS;
			
			if (ActiveKeys.value == 0 && commArg == ACTKEY_DEACTIVATE)
				return SUCCESS;
			
			CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
			for(uint16_t keyIndex = 0; keyIndex < KEYS_MAX_INDEX; keyIndex++) // возможно, будет keyIndex < TotalKeys
			{
				if (fpage.byte[keyIndex] != KEY_STATUS_FREE) 
					fpage.byte[keyIndex] = commArg;
			}

			
			if (commArg == ACTKEY_DEACTIVATE)
				ActiveKeys.value = 0;
			else 
				ActiveKeys.value = TotalKeys.value;
			
			fpage.word[ActiveKeys.indexOnPage] = ActiveKeys.value;
			fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_KEYSTATUS);
						
			IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
			CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS);
			
			break;
		
		case COMM_FACTORY_NUM: // к дефолтным значениям
			
			// если уже и так значения дефолтные, то сброс не нужен
			for(uint8_t i = 0; i < VAR_WRITABLE_COUNT; i++)
            {
                if (variables[i]->value != variables[i]->factoryValue)
				{
					break;
				}

				else 
				{
					if (i == VAR_WRITABLE_COUNT - 1)
						return SUCCESS;
				}
            }
			
			CopyFlashPageToRAM(PAGE_NUMBER_VARS);
			
			for(uint8_t i = 0; i < VAR_WRITABLE_COUNT; i++)
				fpage.word[variables[i]->indexOnPage] = variables[i]->value = variables[i]->factoryValue; // --> ram & iap
			
			fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_VARS);
				
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
	// если неверный аргумент
	if (activationType > 0x02) return FAILURE;
	
	uint16_t keyIndex = keyIndexLSB | keyIndexMSB << 8;

	// если слишком большой индекс ключа
	if (keyIndex > KEYS_MAX_INDEX) return FAILURE;
	
	/* добавляем/меняем сам ключ */
	
	// номер страницы, на которой находится целевой ключ
	uint8_t keyPageNum = PAGE_NUMBER_KEYS_0 + keyIndex / KEYS_COUNT_ON_PAGE; 
	
	// позиция ключа на странице флеша (номер байта)
	uint16_t keyPosOnPage = (keyIndex % KEYS_COUNT_ON_PAGE) * KEY_ENCRYPTED_SIZE; 

	CopyFlashPageToRAM(keyPageNum); 
	memcpy(&fpage.byte[keyPosOnPage], keyStartAddr, KEY_ENCRYPTED_SIZE);
	IAP_Erase_OnePage(keyPageNum);
	CopyRAMToFlashPage(keyPageNum);
	
	/* изменяем статус активности ключа и переменные-счетчики */
	
	uint8_t oldKeyStatus = GetKeyStatus(keyIndex);
	
	if (activationType == oldKeyStatus)
		return SUCCESS;
	
	CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS);
	
	switch (oldKeyStatus)
	{
		case KEY_STATUS_FREE:
			
			if (activationType == ACTKEY_ACTIVATE)
			{
				fpage.byte[keyIndex] = KEY_STATUS_ACTIVATED;
				fpage.word[ActiveKeys.indexOnPage] = ++ActiveKeys.value;
			}
			else // activationType == ACTKEY_DEACTIVATE или ACTKEY_NOACTION
			{
				fpage.byte[keyIndex] = KEY_STATUS_DEACTIVATED;
			}
			
			fpage.word[TotalKeys.indexOnPage] = ++TotalKeys.value;

			break;
		
		case KEY_STATUS_DEACTIVATED:

			if (activationType == ACTKEY_ACTIVATE)
			{
				fpage.byte[keyIndex] = KEY_STATUS_ACTIVATED;
				fpage.word[ActiveKeys.indexOnPage] = ++ActiveKeys.value;
			}
			break;
		
		case KEY_STATUS_ACTIVATED:

			if (activationType == ACTKEY_DEACTIVATE)
			{
				fpage.byte[keyIndex] = KEY_STATUS_DEACTIVATED;
				fpage.word[ActiveKeys.indexOnPage] = --ActiveKeys.value;
			}
			break;
		
		default:
			break;
	}
	
	fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_KEYSTATUS);
	
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
	return IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, keyIndex);
}

//----------------------------------------------------------------------------------------
// Функция копирует ключ из IAP в указанное место в ОЗУ
// Args: keyIndex - индекс ключа в IAP
// Returns: SUCCESS / FAILURE
//----------------------------------------------------------------------------------------

uint32_t CopyKeyByIndex(uint16_t keyIndex, void *dest)
{
//	if (keyIndex > TotalKeys.value) return FAILURE;
	
	memcpy(dest,
		   (void *)(IAP_START_ADDRESS + PAGE_NUMBER_KEYS_0 * IAP_PAGE_SIZE + KEY_ENCRYPTED_SIZE * keyIndex), 
		   KEY_ENCRYPTED_SIZE);
		
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция определяет максимальное значение количества перезаписей среди всех страниц IAP
// Args: 	pageNumber - порядковый номер страницы в IAP
// Returns: максимальное количество перезаписей среди всех страниц IAP
//----------------------------------------------------------------------------------------

uint32_t GetMaxFlashResource(void)
{
//	/* для произвольного кол-ва страниц */
//	uint32_t curFlashResource = 0;
//	uint32_t maxFlashResource = 0;
//	
//	for (uint8_t pageNum = 0; pageNum < 2; pageNum++)
//    {
//		curFlashResource = IAP_ReadWord(pageNum, FLASH_RESOURCE_POS);
//		
//		if (curFlashResource > maxFlashResource)
//			maxFlashResource = curFlashResource;
//    }
//	return maxFlashResource;
	
	/* для первых двух страниц */
	
	uint32_t flashResourcePage0 = IAP_ReadWord(PAGE_NUMBER_VARS, FLASH_RESOURCE_POS);
	uint32_t flashResourcePage1 = IAP_ReadWord(PAGE_NUMBER_KEYSTATUS, FLASH_RESOURCE_POS);
	return flashResourcePage0 > flashResourcePage1 ? flashResourcePage0 : flashResourcePage1;
}

//----------------------------------------------------------------------------------------
// Функция увеличивает общий счетчик перезаписей IAP после перезаписи страницы (если это требуется)
// Args: 	pageNumber - порядковый номер страницы в IAP
// Returns: увеличенное значение счетчика со страницы с номером pageNumber
//----------------------------------------------------------------------------------------
uint32_t UpdateFlashResource(uint8_t pageNumber)
{
	// получаем значение перезаписей страницы, которую планируем обновлять
	uint16_t curPageResource = IAP_ReadWord(pageNumber, FlashResourse.indexOnPage);
	
	// предположим, мы перезаписали страницу
	++curPageResource;
	
	// если значение получилось больше максимального количества перезаписей по всем страницам
	if (curPageResource > FlashResourse.value)
	{
		FlashResourse.value = curPageResource;
	}
	
	return curPageResource;

}

//----------------------------------------------------------------------------------------
// Функция копирует информацию со страницы IAP в "буфер-копию" страницы в ОЗУ
// Args:	pageNumber - порядковый номер страницы в IAP
// Returns: 0 (успех)
//----------------------------------------------------------------------------------------

uint32_t CopyFlashPageToRAM(uint8_t pageNumber)
{
	IAP_CopyFromIAPToRAM(pageNumber, 0, &fpage, IAP_PAGE_SIZE);
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
	return IAP_WriteMultipleWord(pageNumber, 0, &fpage, IAP_PAGE_SIZE / 4);
}

void CopyVariablesPage0ToFlash(void)
{
	// увеличиваем количество перезаписей, записываем это временное значение во FlashResourse (ну да, такой костыль)
	FlashResourse.value = IAP_ReadWord(PAGE_NUMBER_VARS, FLASH_RESOURCE_POS);
	FlashResourse.value++;
	
	// стираем страницу
	IAP_Erase_OnePage(PAGE_NUMBER_VARS); 
	
	// восстанавливаем все переменные во флеш
	IAP_WriteSingleWord(PAGE_NUMBER_VARS, FIRST_WRITE_VALUE_POS, __FIRST_WRITE_VALUE);
	IAP_WriteSingleWord(PAGE_NUMBER_VARS, FLASH_RESOURCE_POS, FlashResourse.value);
	
	for (uint8_t i = 0; i < VAR_PAGE0_COUNT; i++)
		IAP_WriteSingleWord(PAGE_NUMBER_VARS, variables[i]->indexOnPage, variables[i]->value);
	
	// возвращаем значение FlashResourse к максимальному из двух страниц (ну да, такой костыль)
	FlashResourse.value = GetMaxFlashResource();
}