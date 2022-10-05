#include "main.h"
#include "onewire.h"
#include "keys.h"
#include "skud.h"

	

int main()
{
	__disable_irq();

    ChipInit();
//	wdt_disable();
	IAP_Init(IAP_SIZE);
	
//	TM_Timer_Cmd(TM01, DISABLE); // выключаем таймер 1 (не даем включиться ранее положенного)
//	TM_IT_Config(TM01, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 1 по переполнению
//	TM_ITEA_Cmd(TM01, ENABLE); // включаем общие прерывания таймера 1
//	TM_ClearFlag(TM01, TMx_TOF); // очищаем флаг прерывания таймера 1
//	
//	TM_Timer_Cmd(TM10, DISABLE); // выключаем таймер 10 (не даем включиться ранее положенного)
//	TM_IT_Config(TM10, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 10 по переполнению
//	TM_ITEA_Cmd(TM10, ENABLE); // включаем общие прерывания таймера 10
//	TM_ClearFlag(TM10, TMx_TOF); // очищаем флаг прерывания таймера 10
//	
	
	TM_Timer_Cmd(TM36, DISABLE); // выключаем таймер 36 (не даем включиться ранее положенного)
	TM_IT_Config(TM36, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 36 по переполнению
	TM_ITEA_Cmd(TM36, ENABLE); // включаем общие прерывания таймера 36
	TM_ClearFlag(TM36, TMx_TOF); // очищаем флаг прерывания таймера 36

	TM_Timer_Cmd(TM16, DISABLE); // выключаем таймер 16 (не даем включиться ранее положенного)
	TM_IT_Config(TM16, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 16 по переполнению
	TM_ITEA_Cmd(TM16, ENABLE); // включаем общие прерывания таймера 16
	TM_ClearFlag(TM16, TMx_TOF); // очищаем флаг прерывания таймера 16
//	
	URT_Cmd(URT0, DISABLE); // выключаем UART0
	URT_IT_Config(URT0, URT_IT_RX, ENABLE); // включаем прерывание UART0 по приему
    URT_ITEA_Cmd(URT0, ENABLE); // включаем общие прерывания UART0

//	TM_Timer_Cmd(TM10, ENABLE); // включаем таймер, опрашивающий входы


//	TM_Timer_Cmd(TM36, ENABLE);
	
	URT_Cmd(URT0, ENABLE); // включаем UART0

	__enable_irq();
//	
	TM_ClearFlag(TM00, TMx_TOF); 

	REDE_PIN = 1;
	
	
//	if (*(uint32_t *)IAP_START_ADDRESS == UINT32_MAX)  
//		FillFlash();

//	uint8_t mas[13] = { 0x43, 0x10, 0x14, 0x00, 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5, 0x71 };
//	uint8_t crc = Do_CRC(mas, 12);
//	URT_Write(crc);

//	URT_Write(CRCisWrong(mas, 13));
	

	
//	for (uint32_t i = 0; i < 2048; i += 4)
//	{
//		URT_WriteWord(*(uint32_t *)(IAP_START_ADDRESS + i));
//	}
	
//	BUZZER_PIN = 0;
//	DO_PIN = 0;
	


	URT_Write(CurState);
    while(1) 
	{ 

		MonitorKey();

//	uint32_t *kdp = (uint32_t *)&KeysData;
//	
//	for (uint8_t i = 0; i < 15; i++)
//    {
//		URT_WriteWord(*kdp++);
//    }

//	delay_ms(1000);
	
//		1) дверь закрыта (gerkon = 0)
//		2) дверь открывается (gerkon = 1)
//		3) сняли сигналку, но дверь открыта (gerkon = 1)
//		4) сняли сигналку и закрыли дверь (gerkon = 0)
//		5) просрочили сигналку и дверь открыта (gerkon = 1)
//		6) просрочили сигналку и дверь закрыли (gerkon = 0)
		
		
		
		
//		if (DS1990A_GetID())
//		{
//			STALED_PIN = !STALED_PIN;

////			URT_WriteWord(CheckTruth(keyCurrent)); // удалить ключ 
////			URT_WriteWord(RemoveKey(keyCurrent)); // удалить ключ 
////			URT_WriteWord(AddKey(keyCurrent)); // добавить ключ  
//			
////			for (uint32_t i = 0; i < 2048; i += 4)
////			{
////				URT_WriteWord(*(uint32_t *)(IAP_START_ADDRESS + i));
////			}
//			
////			while(1);
//			
//			delay_ms(2000);
//			
//		}
		
		
		
		

//		wdt_reset();
    }
}




















