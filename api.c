#include "api.h"

//----------------------------------------------------------------------------------------
// Функция возвращает значение переменной по её порядковому номеру в протоколе
// Args: 	varNumber - порядковый номер переменной по протоколу
// Returns: значение переменной (успех); 
//			UINT32_MAX (ошибка, нет такой переменной)
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
//			UINT32_MAX (ошибка, нет такой переменной)
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
//			UINT32_MAX (ошибка, нет такой переменной для изменения)
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
	IAP_CopyFlashPageToRAM(PAGE_NUMBER_VARS);
	fpage.word[variables[varNumber]->indexOnPage] = variables[varNumber]->value = varNew; // -->ram & iap
	fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_VARS);
	
	IAP_Erase_OnePage(PAGE_NUMBER_VARS);
	IAP_CopyRAMToFlashPage(PAGE_NUMBER_VARS);
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
	IAP_CopyFlashPageToRAM(PAGE_NUMBER_VARS, &fpage);
				
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
	IAP_CopyRAMToFlashPage(PAGE_NUMBER_VARS, &fpage);
	
	return SUCCESS;
}

//----------------------------------------------------------------------------------------
// Функция устанавливает статус ключа в IAP
// Args:	operationType - тип операции (деактивация или активация)
// 			keyIndexLSB - младший байт индекса ключа; 
// 			keyIndexMSB - старший байт индекса ключа
// Returns: 0 (успех); 
//			UINT32_MAX (ошибка, см. в коде)
//----------------------------------------------------------------------------------------

uint32_t ActivateKey(uint8_t activationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB)
{
	// если неверный аргумент, то ошибка
	if (activationType > 0x01) return FAILURE;
	
	// если не записано ни одного ключа (нечего активировать), то ошибка
	if (TotalKeys.value == 0) return FAILURE;
	
	uint16_t keyIndex = keyIndexLSB | keyIndexMSB << 8;
	
	// если индекс выходит за пределы, то ошибка
	if (keyIndex > KEYS_MAX_INDEX) return FAILURE;
	
	// получаем текущий статус (де)активируемого ключа
	uint8_t curKeyIndexStatus = GetKeyStatus(keyIndex);
	
	// если ключа нет под данным индексом, то ошибка
	if (curKeyIndexStatus == KEY_STATUS_FREE)
		return FAILURE;
	
	// если нужный статус активации ключа уже выставлен, то ничего не делаем
	if (curKeyIndexStatus == activationType)
		return SUCCESS;
	
	// меняем статус активации ключа
	
	IAP_CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS, &fpage);
	
	if (activationType == ACTKEY_ACTIVATE)
	{
		fpage.byte[keyIndex] = KEY_STATUS_ACTIVATED;
		fpage.word[ActiveKeys.indexOnPage] = ++ActiveKeys.value; // инкрементируем счетчик активных ключей
	}
	else
	{
		fpage.byte[keyIndex] = KEY_STATUS_DEACTIVATED;
		fpage.word[ActiveKeys.indexOnPage] = --ActiveKeys.value; // декрементируем счетчик активных ключей
	}
	
	fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_KEYSTATUS);

	IAP_Erase_OnePage(PAGE_NUMBER_KEYSTATUS);
	IAP_CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS, &fpage);
	
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
			
			// если передан недопустимый аргумент, то ошибка
			if (commArg > 0x01) return FAILURE;
			// если ключей нет (нечего активировать), то ошибка
			if (TotalKeys.value == 0)
				return FAILURE;
			// если мы активируем ключи, а они все уже активированы то ничего не делаем
			if (ActiveKeys.value == TotalKeys.value && commArg == ACTKEY_ACTIVATE)
				return SUCCESS;
			// если мы деактивируем ключи, а они все уже деактивированы то ничего не делаем
			if (ActiveKeys.value == 0 && commArg == ACTKEY_DEACTIVATE)
				return SUCCESS;
			
			// обновляем статусы всех ключей во флеше
			IAP_CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS, &fpage);
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
			IAP_CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS, &fpage);
			
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
			
			IAP_CopyFlashPageToRAM(PAGE_NUMBER_VARS, &fpage);
			
			for(uint8_t i = 0; i < VAR_WRITABLE_COUNT; i++)
				fpage.word[variables[i]->indexOnPage] = variables[i]->value = variables[i]->factoryValue; // --> ram & iap
			
			fpage.word[FlashResourse.indexOnPage] = UpdateFlashResource(PAGE_NUMBER_VARS);
				
			IAP_Erase_OnePage(PAGE_NUMBER_VARS);
			IAP_CopyRAMToFlashPage(PAGE_NUMBER_VARS, &fpage);
		
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

	IAP_CopyFlashPageToRAM(keyPageNum, &fpage); 
	memcpy(&fpage.byte[keyPosOnPage], keyStartAddr, KEY_ENCRYPTED_SIZE);
	IAP_Erase_OnePage(keyPageNum);
	IAP_CopyRAMToFlashPage(keyPageNum, &fpage);
	
	/* изменяем статус активности ключа и переменные-счетчики */
	
	uint8_t oldKeyStatus = GetKeyStatus(keyIndex);
	
	if (activationType == oldKeyStatus)
		return SUCCESS;
	
	IAP_CopyFlashPageToRAM(PAGE_NUMBER_KEYSTATUS, &fpage);
	
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
	IAP_CopyRAMToFlashPage(PAGE_NUMBER_KEYSTATUS, &fpage);
	
	return SUCCESS;
}


//----------------------------------------------------------------------------------------
// Функция получает из IAP статус ключа по его индексу
// Args: 	keyIndex - индекс ключа
// Returns: статус активации ключа по протоколу (0 / 1)
//----------------------------------------------------------------------------------------

uint32_t GetKeyStatus(uint16_t keyIndex)
{
	//	if (keyIndex > TotalKeys.value) return FAILURE;
	
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