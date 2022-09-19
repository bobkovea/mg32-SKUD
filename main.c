#include "main.h"
#include "onewire.h"
#include "keys.h"

extern uint8_t koncevik;
extern uint8_t alarm;
	
	
uint32_t key_count = 5;
//uint8_t arr[PAGE_SIZE];
	
	
typedef union  
{
	uint8_t arrByte[PAGE_SIZE];
	uint32_t arrWord[PAGE_SIZE / 4];
	uint8_t arr2DByte[PAGE_SIZE / 8][8];
} u_t;
	
u_t flashBlock;
	
uint32_t CheckTruthEco(uint8_t *key)
{
	uint8_t truth = 0;
		
	for (uint32_t i = 0; i < key_count; i++)
	{
		truth = 1;
		for (uint8_t j = 0; j < 8; j++)
        {
			if (key[j] != IAP_ReadByte(8 + 8 * i + j)) // переделать на ReadWord 
			{
				truth = 0;
				break;
			}
        }
		
		if (truth) return i;
	}
	return UINT32_MAX;

}


	// if >= 62
		
	
uint8_t RemoveKeyEco(uint8_t *newKey)
{
	uint32_t keyNumber = CheckTruthEco(newKey);
	
	if (keyNumber == UINT32_MAX) // если ключа нет в базе
		return 4;  // то ничего не делаем
	
	if (IAP_ReadWord(1) <= 62)
	{
		
	}
	for (uint32_t i = 1 + keyNumber; i < IAP_ReadWord(1); i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			flashBlock.arr2DByte[i][j] = IAP_ReadByte(8 * i + j);
		}
	}
	
	

	if (IAP_GetNumberOfPages() - IAP_GetPageNumberOfByte(8 + 8 * keyNumber))
	{
		IAP_CopyIAPInRAM(i * PAGE_SIZE, arr, sizeof(arr));
		IAP_Erase_OnePage(0);
		
		for (uint32_t i = 8 + 8 * keyNumber; i < flashBlock.arrWord[1]; i++)
        {
			flashBlock.arrWord[i] = flashBlock.arrWord[i + 8];
        }
		
		flashBlock.arrWord[1]--; // --cntkeys
	}
	
	for (uint32_t i = 0; i < MEM_GetIAPSize() / PAGE_SIZE; i++)
    {
		IAP_CopyIAPInRAM(i * PAGE_SIZE, arr, sizeof(arr));
		IAP_Erase_OnePage(0);
    }
	
	
	

	
	for (uint32_t i = 0; i < MEM_GetIAPSize() / PAGE_SIZE; i++)
    {
		IAP_CopyIAPInRAM(0, arr, sizeof(arr));
		IAP_Erase_OnePage(0);
    }
	
	
	KeysData.keysCount--;
	KeysData.nWrite++;
	KeysData.checksum = Do_CRC((uint8_t *)&KeysData, sizeof(KeysData) - 4); // считаем CRC;
	IAP_FullErase(); // полностью очищаем выделенную IAP
	IAP_CopyRAMInIAP(0, &KeysData, sizeof(KeysData));
	
	return 3;
}
	
	
int main()
{
	__disable_irq();

    ChipInit();
	wdt_disable();
	IAP_Init(IAP_SIZE_4096 /*MIN_IAP_SIZE*/);
//	FlashStartupHandle();  
	
	TM_Timer_Cmd(TM01, DISABLE); // выключаем таймер 1 (не даем включиться ранее положенного)
	TM_IT_Config(TM01, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 1 по переполнению
	TM_ITEA_Cmd(TM01, ENABLE); // включаем общие прерывания таймера 1
	TM_ClearFlag(TM01, TMx_TOF); // очищаем флаг прерывания таймера 1
//	
	TM_Timer_Cmd(TM10, DISABLE); // выключаем таймер 10 (не даем включиться ранее положенного)
	TM_IT_Config(TM10, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 10 по переполнению
	TM_ITEA_Cmd(TM10, ENABLE); // включаем общие прерывания таймера 10
	TM_ClearFlag(TM10, TMx_TOF); // очищаем флаг прерывания таймера 10
	
	TM_Timer_Cmd(TM16, DISABLE); // выключаем таймер 16 (не даем включиться ранее положенного)
	TM_IT_Config(TM16, TMx_TIE_IE, ENABLE); // включаем прерывание таймера 16 по переполнению
	TM_ITEA_Cmd(TM16, ENABLE); // включаем общие прерывания таймера 16
	TM_ClearFlag(TM16, TMx_TOF); // очищаем флаг прерывания таймера 16
//	
	URT_Cmd(URT0, DISABLE); // выключаем UART0
	URT_IT_Config(URT0, URT_IT_RX, ENABLE); // включаем прерывание UART0 по приему
    URT_ITEA_Cmd(URT0, ENABLE); // включаем общие прерывания UART0

	TM_Timer_Cmd(TM10, ENABLE); // включаем таймер, опрашивающий входы

	URT_Cmd(URT0, ENABLE); // включаем UART0

	__enable_irq();
//	
	TM_ClearFlag(TM00, TMx_TOF); 

	

	PIN_ZUMER = 0;
//	uint8_t alarm = 1;
	uint8_t start_signal = 0;
	uint8_t IsRead = 0;
	
	if (*(uint32_t *)IAP_START_ADDRESS == UINT32_MAX)  
		FillFlash();
	else
		CopyFlash();
//	
//	uint32_t *kdp = (uint32_t *)&KeysData;
//	
//	for (uint8_t i = 0; i < 45; i++)
//    {
//		URT_WriteWord(*kdp++);
//    }
	

//	uint8_t mas[13] = { 0x43, 0x10, 0x14, 0x00, 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5, 0x71 };
//	uint8_t crc = Do_CRC(mas, 12);
//	URT_Write(crc);

//	URT_Write(CRCisWrong(mas, 13));
	
	
	
	
	
	
	
    while(1) 
	{ 
		
	uint32_t *kdp = (uint32_t *)&KeysData;
	
	for (uint8_t i = 0; i < 15; i++)
    {
		URT_WriteWord(*kdp++);
    }
	delay_ms(10000);
	
//		if (DS1990_GetID())
//		{
//			uint8_t s = AddKey(keyCurrent);
//			URT_Write(s);
//			if (s)
//				PE13 = 0;
			

//			RemoveKey(keyCurrent); // удалить ключ

			
//			delay_ms(100);

			
//			for (uint32_t i = 0; i < 255; i += 4)
//			{
//				URT_WriteWord(*(uint32_t *)(IAP_START_ADDRESS + i));
//			}
//			while(1);
			
			
			
//		}
		
//		if (DS1990_GetID())
//		{
//			
////				for (uint32_t i = 0; i < 8; i++)
////                {
////					URT_Write(keyCurrent[i]);
////                }
//		}
		
//			IsKeyTrue(); 
		
//		if (koncevik)
//		{
//			delay_ms(2000);
//			if (koncevik) {
//				alarm = 1;
//				start_signal = 0;
//			}
//		}
//	
//		if (alarm) // если сигнализация горит
//		{
//			if (!start_signal)
//			{
//				start_signal = 1;

//				TM_Timer_Cmd(TM16, DISABLE);
//				TM_Prescaler_Config(TM16, 0, 999);
//				TM_Counter_Config(TM16, 0, 3999);
//				TM_Timer_Cmd(TM16, ENABLE);
//			}
//			
//			pisk_cnt = 0; // сбрасываем для постоянных 
//			
//			
//		// 
//	//	TM_Timer_Cmd(TM16, DISABLE);

//			if (DS1990_GetID()) // если ключ поднесли, то считываем его id
//			{
//				
//				for (uint8_t i = 0; i < 8; i++)
//				{
//					URT_Write(keyCurrent[i]);
//				}
//					
//				if (!IsRead) // если до этого ключ не был считан
//				{
//					IsRead = 1; // отметка об однократном считывании
//					
//					if (IsKeyTrue()) // если ключ подошел, короткий сигнал и выключаем сигнализацию
//					{
//						
//						TM_Timer_Cmd(TM16, DISABLE); 
//						TM_Prescaler_Config(TM16, 0, 999);
//						TM_Counter_Config(TM16, 0, 999);
//						TM_Timer_Cmd(TM16, ENABLE);
//						pisk_cnt = 0;
//						while(pisk_cnt < pisk_max)
//							delay_ms(100);
//						TM_Timer_Cmd(TM16, DISABLE); 
//						alarm = 0;
//						PIN_ZUMER = 0;
//						PE13 = 1;
//					}
//					
//					else // если ключ не подошел, то иной короткий сигнал, сигнализация работает
//					{
//						TM_Timer_Cmd(TM16, DISABLE);
//						TM_Prescaler_Config(TM16, 0, 999);
//						TM_Counter_Config(TM16, 0, 399);
//						TM_Timer_Cmd(TM16, ENABLE);
//						pisk_cnt = 0;
//						while(pisk_cnt < pisk_max)
//							delay_ms(100);
//						start_signal = 0;
//					}
//				}
//			}

//			else  // если ключа нет
//				if (IsRead) 
//					IsRead = 0; // можно считывать опять	
//				
//			delay_ms(100);
//				
//		}

//			delay_ms(1000);





//		wdt_reset();
    }
}




















