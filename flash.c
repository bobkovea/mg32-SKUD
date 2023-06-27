#include "flash.h"

FlashPage_t fpage; // копия страницы флеша, размер равен странице

void FlashTestFill(void)
{
	MD5_MakeHash(key1, KEY_RAW_SIZE, KeyEncrypted);
	API_AddKey(ACTKEY_ACTIVATE, 0, 0, KeyEncrypted); 
//	
//	MD5_MakeHash(key2, KEY_RAW_SIZE, KeyEncrypted);
//	API_AddKey(ACTKEY_ACTIVATE, 0, 1, KeyEncrypted);
//	
//	MD5_MakeHash(key_em_1, KEY_RAW_SIZE, KeyEncrypted);
//	API_AddKey(ACTKEY_ACTIVATE, 0, 2, KeyEncrypted);
//	
//	MD5_MakeHash(key_em_2, KEY_RAW_SIZE, KeyEncrypted);
//	API_AddKey(ACTKEY_ACTIVATE, 0, 3, KeyEncrypted);
}

/*----------------------------------------------------------------------------------------
// Функция вызывается сразу после старта микроконтроллера
// Если включение первое, копируем значения переменных по умолчанию во флеш
// Если включение не первое, то наиборот копируем значения переменных из флеша в ОЗУ
----------------------------------------------------------------------------------------*/

void PowerOnHandle(void)
{
	// если включение НЕ ПЕРВОЕ
	uint32_t magicWord = IAP_ReadWord(PAGE_NUMBER_VARS, FIRST_WRITE_VALUE_POS);
	
	if (magicWord == __FIRST_WRITE_VALUE)
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
			API_CopyKeyByIndex(ValidKeyIndex.value, KeyEncrypted);
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
	muteTimeoutMax = BuzzerOffTime.value * 60000 / 100; // т.к. период таймера = 100 мс и ед.изм. - мин
	
	// определяем начальное состояние системы
	DefineInitialState();
}


//----------------------------------------------------------------------------------------
// Функция определяет максимальное значение количества перезаписей среди всех страниц IAP
// Returns: максимальное количество перезаписей среди всех страниц IAP
//----------------------------------------------------------------------------------------

uint32_t GetMaxFlashResource(void)
{
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

void API_CopyVariablesPage0ToFlash(void)
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