#include "main.h"

uint8_t varPackage[11] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};

int main()
{
	__disable_irq();
	
    ChipInit(); // настраиваем тактирование
	FlashFirstInit(); // первичная проверка конфиг. данных во флеше
	GPIO_Config(); 
	TIM_Config();
	USART_Config();
	WDT_Config();

	URT_Cmd(URT0, ENABLE); // включаем UART0
	
	__enable_irq();

	RS485_CONFIG_TRANSMIT();

	FlashTestFill();
	
	
	currentEvent = eDoorOpened;
	
	
	
	
	
	
	
//////////////////////////////////////////////////////////////
// ТЕСТ ЧТЕНИЯ И ЗАПИСИ ПЕРЕМЕННОЙ
	
//	URT_WriteWord(GetVariable(0));
//	URT_WriteWord(GetVariable(1));
//		
//	URT_WriteWord(SetVariable(0, 0xAA, 0xBB));
//	URT_WriteWord(SetVariable(1, 0xCC, 0xDD));

//	URT_WriteWord(GetVariable(0));
//	URT_WriteWord(GetVariable(1));
	
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

//	for (uint32_t i = 0; i < 20; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}


//	URT_WriteWord(ActivateKey(0, 0, 0));
//	URT_WriteWord(ActivateKey(1, 0, 0));
//	URT_WriteWord(ActivateKey(1, 10, 0));
//	URT_WriteWord(ActivateKey(0, 10, 0));

	//	for (uint32_t i = 0; i < 20; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ МАССОВАЯ АКТИВАЦИЯ КЛЮЧЕЙ

//	for (uint32_t i = 0; i < 20; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}

//	DoCommand(0, 1);

//	for (uint32_t i = 0; i < 20; i++)
//	{
//		URT_WriteWord(IAP_ReadByte(PAGE_NUMBER_KEYSTATUS, i)); 
//	}

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ ЗАВОДСКИЕ ЗНАЧЕНИЯ

//	SetVariablePack(varPackage);
//	
//	for (uint32_t i = 0; i < VAR_COUNT_WRITABLE; i++)
//		URT_WriteWord(GetVariable(i));

//	DoCommand(1, 123);
	
//	for (uint32_t i = 0; i < VAR_COUNT_WRITABLE; i++)
//		URT_WriteWord(GetVariable(i));

//////////////////////////////////////////////////////////////

// ТЕСТ КОМАНДЫ ДОБАВЛЕНИЕ/ИЗМЕНЕНИЕ КЛЮЧЕЙ

//	for (uint32_t i = 0; i < 255; i++)
//		URT_WriteWord(IAP_ReadWord(PAGE_NUMBER_KEYS_0, i));

//	AddKey(ACTKEY_DEACTIVATE, 0, 0, key_test);
//	AddKey(ACTKEY_DEACTIVATE, 1, 0, keys[0]);
//	AddKey(ACTKEY_NOACTION, 2, 0, key_test);
//	AddKey(ACTKEY_NOACTION, 3, 0, keys[1]);
//	
//	AddKey(ACTKEY_DEACTIVATE, 10, 0, key_test);
//	AddKey(ACTKEY_ACTIVATE, 20, 0, keys[2]);
//	AddKey(ACTKEY_NOACTION, 30, 0, key_test);
//	AddKey(ACTKEY_NOACTION, 40, 0, keys[3]);
//	
//	for (uint32_t i = 0; i < 255; i++)
//		URT_WriteWord(IAP_ReadWord(PAGE_NUMBER_KEYS_0, i));

//	for (uint32_t i = 0; i < 255; i++)
//		URT_WriteWord(IAP_ReadWord(PAGE_NUMBER_KEYSTATUS, i));

//	for (uint32_t i = 0; i < 255; i++)
//		URT_WriteWord(IAP_ReadWord(PAGE_NUMBER_VARS, i));

//////////////////////////////////////////////////////////////


		
//	delay_ms(5000);

	
	
//	uint8_t mas[13] = { 0x43, 0x10, 0x0A,  };
//	uint8_t crc = Do_CRC(mas, 12);
//	URT_Write(crc);

//	URT_Write(CRCisWrong(mas, 13));

	
//	BUZZER_PIN = 0;
//	DO_PIN = 0;
	

//	URT_Write(CurState);

//	TM_Timer_Cmd(TM16, ENABLE);  
//	TM_Timer_Cmd(TM36, ENABLE);  



    while(1) 
	{ 
		HandleEvent();
		wdt_reset();
    }
}
	
		
		
		
//	MonitorKey();

//	uint32_t *kdp = (uint32_t *)&KeysData;
//	
//	for (uint8_t i = 0; i < 15; i++)
//    {
//		URT_WriteWord(*kdp++);
//    }

//	delay_ms(1000);
		
//		if (DS1990A_GetID())
//		{
//			STALED_PIN = !STALED_PIN;

////		URT_WriteWord(CheckTruth(keyCurrent)); // удалить ключ 
////		URT_WriteWord(RemoveKey(keyCurrent)); // удалить ключ 
////		URT_WriteWord(AddKey(keyCurrent)); // добавить ключ  
//			
////		for (uint32_t i = 0; i < 2048; i += 4)
////		{
////			URT_WriteWord(*(uint32_t *)(IAP_START_ADDRESS + i));
////		}
//			
////		while(1);
//			
//			delay_ms(2000);
//			
//		}





















