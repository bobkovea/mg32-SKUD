#include "main.h"
#include "skud_algo.h"

uint8_t varPackage[11] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };

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
	
	FlashTestFill();
	
	TM_Timer_Cmd(TM_INPUT, ENABLE);  
	__enable_irq();

//	RS485_CONFIG_TRANSMIT();
	

	
//	currentEvent = eDoorOpened;

//	TM_Timer_Cmd(TM_PRSM_RESET, ENABLE);  
	
//	IndicationStart(AlarmCommon);
	
	
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





















