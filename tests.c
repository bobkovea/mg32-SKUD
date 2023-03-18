
//uint8_t varPackage[11] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };

//////////////////////////////////////////////////////////////
// ТЕСТ ЧТЕНИЯ И ЗАПИСИ ПЕРЕМЕННОЙ
	
//	URT_WriteWord(GetVariable(0));
//	URT_WriteWord(GetVariable(1));
//		
//	URT_WriteWord(SetVariable(0, 0xAA, 0xBB));
//	URT_WriteWord(SetVariable(1, 0xCC, 0xDD));

//	URT_WriteWord(GetVariable(0));
//	URT_WriteWord(GetVariable(1));
//	
//////////////////////////////////////////////////////////////
// ТЕСТ ЗАПИСИ ПАКА

//	for (uint32_t i = 0; i < VAR_COUNT_WRITABLE; i++)
//		URT_WriteWord(GetVariable(i));

//	SetVariablePack(varPackage); 
//	
//	for (uint32_t i = 0; i < VAR_COUNT_WRITABLE; i++)
//		URT_WriteWord(GetVariable(i));

//////////////////////////////////////////////////////////////

// ТЕСТ АКТИВАЦИИ КЛЮЧА

//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}
//	delay_ms(2000);
//	
//	URT_WriteWord(ActivateKey(ACTKEY_DEACTIVATE, 0, 0));
//	URT_WriteWord(ActivateKey(ACTKEY_ACTIVATE, 1, 0));
//	URT_WriteWord(ActivateKey(ACTKEY_NOACTION, 2, 0)); // error
//	URT_WriteWord(ActivateKey(ACTKEY_NOACTION, 3, 0)); // error
//	URT_WriteWord(ActivateKey(ACTKEY_ACTIVATE, 4, 0));

//	delay_ms(2000);
//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}
//	
////	AddKey(ACTKEY_ACTIVATE, 0, 0, key1);
////	AddKey(ACTKEY_DEACTIVATE, 1, 0, key2);
////	AddKey(ACTKEY_NOACTION, 2, 0, key3);
////	AddKey(ACTKEY_DEACTIVATE, 3, 0, key4);
////	AddKey(ACTKEY_NOACTION, 4, 0, key5);

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ МАССОВАЯ АКТИВАЦИЯ КЛЮЧЕЙ

//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_Write(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}
//	
//	DoCommand(COMM_ALLKEYACT, ACTKEY_DEACTIVATE);

//	for (uint32_t i = 0; i < 5; i++)
//	{
//		URT_Write(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ ЗАВОДСКИЕ ЗНАЧЕНИЯ

//	SetVariablePack(varPackage);
//	
//	for (uint32_t i = 0; i < VAR_COUNT_WRITABLE; i++)
//		URT_WriteWord(GetVariable(i));

//	DoCommand(COMM_FACTORY_NUM, 0);
//	
//	delay_ms(1000);
//	for (uint32_t i = 0; i < VAR_COUNT_WRITABLE; i++)
//		URT_WriteWord(GetVariable(i));

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ ДОБАВЛЕНИЕ/ИЗМЕНЕНИЕ КЛЮЧЕЙ

//	AddKey(ACTKEY_DEACTIVATE, 0, 0, key_test);
//	AddKey(ACTKEY_DEACTIVATE, 1, 0, keys[0]);
//	AddKey(ACTKEY_NOACTION, 2, 0, key_test);
//	AddKey(ACTKEY_NOACTION, 3, 0, keys[1]);
//	AddKey(ACTKEY_DEACTIVATE, 10, 0, key_test);
//	AddKey(ACTKEY_ACTIVATE, 20, 0, keys[2]);
//	AddKey(ACTKEY_NOACTION, 30, 0, key_test);
//	AddKey(ACTKEY_NOACTION, 40, 0, keys[3]);

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
