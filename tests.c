
//uint8_t varPackage[11] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };

//////////////////////////////////////////////////////////////
// ТЕСТ ЧТЕНИЯ И ЗАПИСИ ПЕРЕМЕННОЙ
	
//	URT_WriteWord(API_GetVariable(0));
//	URT_WriteWord(API_GetVariable(1));
//		
//	URT_WriteWord(API_SetVariable(0, 0xAA, 0xBB));
//	URT_WriteWord(API_SetVariable(1, 0xCC, 0xDD));

//	URT_WriteWord(API_GetVariable(0));
//	URT_WriteWord(API_GetVariable(1));
//	
//////////////////////////////////////////////////////////////
// ТЕСТ ЗАПИСИ ПАКА

//	for (uint32_t i = 0; i < VAR_WRITABLE_COUNT; i++)
//		URT_WriteWord(API_GetVariable(i));

//	API_SetVariablePack(varPackage); 
//	
//	for (uint32_t i = 0; i < VAR_WRITABLE_COUNT; i++)
//		URT_WriteWord(API_GetVariable(i));

//////////////////////////////////////////////////////////////

// ТЕСТ АКТИВАЦИИ КЛЮЧА

//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}
//	delay_ms(2000);
//	
//	URT_WriteWord(API_ActivateKey(ACTKEY_DEACTIVATE, 0, 0));
//	URT_WriteWord(API_ActivateKey(ACTKEY_ACTIVATE, 0, 1));
//	URT_WriteWord(API_ActivateKey(ACTKEY_NOACTION, 0, 2)); // error
//	URT_WriteWord(API_ActivateKey(ACTKEY_NOACTION, 0, 3)); // error
//	URT_WriteWord(API_ActivateKey(ACTKEY_ACTIVATE, 0, 4));

//	delay_ms(2000);
//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}
//	
////	API_AddKey(ACTKEY_ACTIVATE, 0, 0, key1);
////	API_AddKey(ACTKEY_DEACTIVATE, 0, 1, key2);
////	API_AddKey(ACTKEY_NOACTION, 0, 2, key3);
////	API_AddKey(ACTKEY_DEACTIVATE, 0, 3, key4);
////	API_AddKey(ACTKEY_NOACTION, 0, 4, key5);

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ МАССОВАЯ АКТИВАЦИЯ КЛЮЧЕЙ

//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_Write(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}
//	
//	API_DoCommand(COMM_ALLKEYACT, ACTKEY_DEACTIVATE);

//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_Write(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ ЗАВОДСКИЕ ЗНАЧЕНИЯ

//	API_SetVariablePack(varPackage);
//	
//	for (uint32_t i = 0; i < VAR_WRITABLE_COUNT; i++)
//		URT_WriteWord(API_GetVariable(i));

//	API_DoCommand(COMM_FACTORY_NUM, 0);
//	
//	delay_ms(1000);
//	for (uint32_t i = 0; i < VAR_WRITABLE_COUNT; i++)
//		URT_WriteWord(API_GetVariable(i));

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ ДОБАВЛЕНИЕ/ИЗМЕНЕНИЕ КЛЮЧЕЙ

//	API_AddKey(ACTKEY_DEACTIVATE, 0, 0, key_test);
//	API_AddKey(ACTKEY_DEACTIVATE, 0, 1, keys[0]);
//	API_AddKey(ACTKEY_NOACTION, 0, 2, key_test);
//	API_AddKey(ACTKEY_NOACTION, 0, 3, keys[1]);
//	API_AddKey(ACTKEY_DEACTIVATE, 0, 10, key_test);
//	API_AddKey(ACTKEY_ACTIVATE, 0, 20, keys[2]);
//	API_AddKey(ACTKEY_NOACTION, 0, 30, key_test);
//	API_AddKey(ACTKEY_NOACTION, 0, 40, keys[3]);

//	for (uint32_t i = 0; i < 180; i++)
//	{
//		URT_WriteWord(IAP_ReadWord(PAGE_NUMBER_KEYS_0, i));
//		delay_ms(10);
//	}
//	delay_ms(10000);
//	for (uint32_t i = 0; i < 50; i++)
//	{
//		URT_Write(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i));
//		delay_ms(100);
//	}
//	delay_ms(10000);
//	
//	URT_WriteWord(GetMaxFlashResource());
//	
//	for (uint32_t i = 250; i < 255; i++)
//	{
//		URT_WriteWord(IAP_ReadWord(PAGE_NUMBER_VARS, i));
//		delay_ms(100);
//	}

//////////////////////////////////////////////////////////////
