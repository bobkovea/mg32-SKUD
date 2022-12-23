#include "main.h"

uint8_t varPackage[11] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };

int main()
{
	__disable_irq();
	
    ChipInit(); // настраиваем тактирование
	GPIO_Config(); 
	FlashFirstInit(); // первичная проверка конфиг. данных во флеше
	TIM_Config();
	USART_Config();
	WDT_Config();

	URT_Cmd(URT0, ENABLE); // включаем UART0
	
	__enable_irq();

//	RS485_CONFIG_TRANSMIT();
	
	FlashTestFill();
	
//	currentEvent = eDoorOpened;
	
//	BUZZER_PIN = 0;
//	DO_PIN = 0;
	

//	TM_Timer_Cmd(TM16, ENABLE);  
//	TM_Timer_Cmd(TM36, ENABLE);  

    while(1) 
	{ 
//		HandleEvent();
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
////		AddKey(keyCurrent)); // добавить ключ  
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





















