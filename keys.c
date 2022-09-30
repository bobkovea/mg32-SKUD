#include "keys.h"
#include "onewire.h"
#include "usart.h"
#include "iap.h"
#include "crc.h"
#include "timers.h"

uint8_t keyCurrent[8]; // буфер для считанного ключа

uint8_t key1[8] = { 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5 }; // черный без задней крышки
uint8_t key2[8] = { 0x01, 0xD8, 0xD3, 0x73, 0x01, 0x00, 0x00, 0xC3 }; // синий
uint8_t key3[8] = { 0x01, 0x3A, 0x6F, 0x14, 0x09, 0x00, 0x00, 0xD9 }; // черный с наклейкой
uint8_t key4[8] = { 0x01, 0x37, 0x47, 0x6E, 0x09, 0x00, 0x00, 0xE6 }; // черный 1
uint8_t key5[8] = { 0x01, 0x37, 0x69, 0xC9, 0x09, 0x00, 0x00, 0x93 }; // черный 2

uint8_t key_test[8] = { 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE };

uint8_t *keys[5] = { key1, key2, key3, key4, key5 };

#define IAP_PAGE_COUNT 2
#define IAP_FIRST_PAGE 0
#define IAP_LAST_PAGE IAP_PAGE_COUNT - 1
#define IAP_SIZE IAP_PAGE_COUNT * IAP_PAGE_SIZE
#define KEYS_COUNT (IAP_SIZE - 16) / 8


#define NWRITE_WORD_POS IAP_PAGE_SIZE / 4 - 2
#define CRC_WORD_POS IAP_PAGE_SIZE / 4 - 1
#define KEYSCNT_WORD_POS 1

void FillFlash(void)
{
	
	uint32_t sWord = 0xABABABAB;
	uint32_t kCnt = 0 /*(IAP_SIZE - 16) / 8*/;
	uint32_t nWrite = 0x01;
	uint32_t crc = 0xCCCCCCCC;
	
	
	

	
//	IAP_CopyRAMInIAP(8, key1, sizeof(key1));
//	IAP_CopyRAMInIAP(16, key2, sizeof(key2));
//	IAP_CopyRAMInIAP(24, key3, sizeof(key3));
//	IAP_CopyRAMInIAP(32, key4, sizeof(key4));
//	IAP_CopyRAMInIAP(40, key5, sizeof(key5));
	
	IAP_CopyRAMInIAP(IAP_SIZE - 8, &nWrite, sizeof(nWrite));
	IAP_CopyRAMInIAP(IAP_SIZE - 4, &crc, sizeof(crc));

//	
	for (uint32_t i = 8; i < 2048 - 24; i += 8)
    {
		kCnt++;
		IAP_CopyRAMInIAP(i, key1, sizeof(key1));
    }
	
	IAP_CopyRAMInIAP(2048 - 24, key2, sizeof(key2));
	kCnt++;
	
	IAP_CopyRAMInIAP(0, &sWord, sizeof(sWord));
	IAP_CopyRAMInIAP(4, &kCnt, sizeof(kCnt));
	

//	
//	IAP_CopyRAMInIAP(1024 - 24, key2, sizeof(key2));
//	IAP_CopyRAMInIAP(1024 - 16, key3, sizeof(key3));
//	IAP_CopyRAMInIAP(1024 - 8, key3, sizeof(key3));
}

void CopyFlash(void)
{
	return; 
}

uint32_t key_count = 5;
	
typedef union  
{
	uint8_t arrByte[IAP_PAGE_SIZE];
	uint32_t arrWord[IAP_PAGE_SIZE / 4];
	uint64_t arrDword[IAP_PAGE_SIZE / 8];
} u_t;


	
u_t flashBlock;

uint32_t CheckTruth(uint8_t *keyToCheck)
{
	uint8_t truth = 0;
		
	for (uint32_t i = 1; i <=  (256 - 2) /*IAP_ReadWord(4)*/; i++) // со смещением на служебные
	{
		truth = 1;
		for (uint8_t j = 0; j < 8; j++)
        {
			if (keyToCheck[j] != IAP_ReadByte(8 * i + j)) // переделать на ReadWord 
			{
				truth = 0;
				break;
			}
        }
		
		if (truth) return 8 * i;
	}
	
	return UINT32_MAX;
}


uint8_t AddKey(uint8_t *keyToAdd)
{
	if (CheckTruth(keyToAdd) != UINT32_MAX) // если ключ уже есть в базе
		return 1;  // не добавляем новый ключ (можно вернуть порядковый номер ключа в базе)
	
	uint32_t keyCount = IAP_ReadWord(4);
	if (keyCount >= MAX_KEYS_COUNT) // если память ключей заполнена
		return 2; // не добавляем новый ключ
	
	uint32_t newKeyBytePos =  8 + keyCount * 8;
	uint8_t pageNumberOfKey = IAP_GetPageNumberOfByte(newKeyBytePos);

	for (uint8_t i = IAP_FIRST_PAGE; i < IAP_PAGE_COUNT; i++)
    {
		if  (i != pageNumberOfKey && i != IAP_FIRST_PAGE && i != IAP_LAST_PAGE) // если страница не первая или последняя и на ней нет ключа
			continue; // то страница не изменяется

		IAP_CopyIAPInRAM(i * IAP_PAGE_SIZE, flashBlock.arrByte, sizeof(flashBlock.arrByte)); // копируем текущую страницу флеша в ОЗУ
		
		if (i == IAP_FIRST_PAGE) // если страница первая
			flashBlock.arrWord[KEYSCNT_WORD_POS]++; // увеличиваем счетчик ключей
		
		if (i == IAP_LAST_PAGE) // если страница последняя
		{	
			flashBlock.arrWord[NWRITE_WORD_POS]++; // увеличиваем количество стираний флеша
			flashBlock.arrWord[CRC_WORD_POS] = 0xAB /*Do_CRC((uint8_t *)flashBlock.arrByte, sizeof(flashBlock.arrByte) - 4)*/ ; // считаем CRC (мб всей памяти? но как?)
		}
	
		if (i == pageNumberOfKey) // если на текущей странице будет ключ
		{
			for (uint32_t j = 0, k = newKeyBytePos - pageNumberOfKey * IAP_PAGE_SIZE; j < 8; j++, k++)
				flashBlock.arrByte[k] = keyCurrent[j]; 
		}
		
		IAP_Erase_OnePage(i); // стираем текущую страницу флеша
		IAP_CopyRAMInIAP(i * IAP_PAGE_SIZE, flashBlock.arrByte, sizeof(flashBlock.arrByte)); // перезаписываем блок
	}
	
	return 0;
}

uint8_t RemoveKey(uint8_t *keyToRemove)
{
	uint32_t keyBytePos = CheckTruth(keyToRemove);

	if (keyBytePos == UINT32_MAX) // если ключа нет в базе
		return 4;  // то ничего не делаем

	uint32_t lastByteNumber = 0;
	
	uint8_t pageNumberOfKey = IAP_GetPageNumberOfByte(keyBytePos);

	for (uint8_t i = IAP_FIRST_PAGE; i < IAP_PAGE_COUNT; i++)
    {

		if  (i < pageNumberOfKey && i != IAP_FIRST_PAGE) // если на странице только ключи и только ДО удаляемого
			continue; // страница не изменяется
		
		IAP_CopyIAPInRAM(i * IAP_PAGE_SIZE, flashBlock.arrByte, sizeof(flashBlock.arrByte)); // копируем текущую страницу флеша в ОЗУ
		
		if (i == IAP_FIRST_PAGE) // если страница первая
			flashBlock.arrWord[KEYSCNT_WORD_POS]--; // уменьшаем счетчик ключей
		
		if (i == IAP_LAST_PAGE) // если страница последняя
		{
			lastByteNumber = IAP_PAGE_SIZE  + IAP_PAGE_SIZE * i - 16; // последний ключ и служебные не трогаем
			flashBlock.arrWord[NWRITE_WORD_POS]++; // увеличиваем количество стираний флеша
			flashBlock.arrWord[CRC_WORD_POS] = 0xAB /* Do_CRC((uint8_t *)flashBlock.arrByte, sizeof(flashBlock.arrByte) - 4)*/ ; // считаем CRC (мб всей памяти? но как?)
		}
		else // если страница не последняя
			lastByteNumber = IAP_PAGE_SIZE  + IAP_PAGE_SIZE * i; // меняем последний ключ на первый ключ следующей страницы
						

		if (i == pageNumberOfKey) // если на текущей странице находится удаляемый ключ
		{
			for (uint32_t j = keyBytePos /* +8 */; j < lastByteNumber; j++)
				flashBlock.arrByte[j - pageNumberOfKey * IAP_PAGE_SIZE] = IAP_ReadByte(j + 8 /* j */); 
				
		}
		
		else /* else if i > pageNumberOfKey */ // для страниц после страницы с ключом
		{
			for (uint32_t j = 0, k = IAP_PAGE_SIZE * i /* +8 */; k < lastByteNumber; j++, k++)
				flashBlock.arrByte[j] = IAP_ReadByte(k + 8 /* k */); 
		}
		
		
//		if (i == 3) {
//			
//			for (uint32_t j = 0; j < 512 / 4; j++)
//			{
//				URT_WriteWord(flashBlock.arrWord[j]);
//			}
//		
//		}
		IAP_Erase_OnePage(i); // стираем текущую страницу флеша
		IAP_CopyRAMInIAP(i * IAP_PAGE_SIZE, flashBlock.arrByte, sizeof(flashBlock.arrByte)); // перезаписываем блок
		

	}

	return 3;
}

void ChangeKey(uint8_t keyNumber)
{

	

}


uint8_t DS1990_GetID (void)	
{	
	uint8_t Presence = OneWire_Start();
	delay_ms(1);
	if (Presence) 
	{
		OneWire_Write (0x33); 
		for (uint8_t i = 0; i < 8; i++)
		{
			keyCurrent[i] = OneWire_Read();
			URT_Write(keyCurrent[i]);
		}
		if (keyCurrent[7] == Do_CRC(keyCurrent, 7))
			return 1;
		// несколько считываний подряд
		
	}
	return 0;

	
}