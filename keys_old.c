//#include "keys_old.h"
//#include "onewire.h"
//#include "usart.h"
//#include "iap.h"
//#include "crc.h"
//#include "timers.h"

//uint8_t keyCurrent[8];

//uint8_t key1[8] = { 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5 }; // черный без задней крышки
//uint8_t key2[8] = { 0x01, 0xD8, 0xD3, 0x73, 0x01, 0x00, 0x00, 0xC3 }; // синий
//uint8_t key3[8] = { 0x01, 0x3A, 0x6F, 0x14, 0x09, 0x00, 0x00, 0xD9 }; // черный с наклейкой
//uint8_t key4[8] = { 0x01, 0x37, 0x47, 0x6E, 0x09, 0x00, 0x00, 0xE6 }; // черный 1
//uint8_t key5[8] = { 0x01, 0x37, 0x69, 0xC9, 0x09, 0x00, 0x00, 0x93 }; // черный 2

//uint8_t key_test[8] = { 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE };

//uint8_t *keys[5] = { key1, key2, key3, key4, key5 };

//flash_t KeysData = {0};


//void FillFlash(void)
//{
//	
//	KeysData.startWord = 0xABABABAB;
//	KeysData.keysCount = 5;
//	
//	for (uint8_t i = 0; i < KeysData.keysCount; i++)
//	{
//		for (uint8_t j = 0; j < 8; j++)
//        {
//			KeysData.keys[i][j] = keys[i][j];
//		}
//	}

//	KeysData.nWrite = 1;
//	KeysData.checksum = Do_CRC((uint8_t *)&KeysData, sizeof(KeysData) - 4); // считаем CRC;
//	
//	IAP_FullErase(); // полностью очищаем выделенную IAP
//	IAP_CopyRAMInIAP(0, &KeysData, sizeof(KeysData));
//}

//void CopyFlash(void)
//{
//	IAP_CopyIAPInRAM(0, &KeysData, sizeof(KeysData));
//}

//uint32_t CheckTruth(uint8_t* key)
//{
//	uint8_t truth = 0;
//	
//	for (uint32_t i = 0; i < KeysData.keysCount; i++)
//	{
//		truth = 1;
//		for (uint8_t j = 0; j < 8; j++)
//        {
//			if (key[j] != KeysData.keys[i][j])
//			{
//				truth = 0;
//				break;
//			}
//        }
//		
//		if (truth) return i;
//	}
//	return UINT32_MAX;
//}


//uint8_t AddKey(uint8_t* newKey)
//{
//	if (CheckTruth(newKey) != UINT32_MAX) // если ключ уже есть в базе
//		return 1;  // не добавляем новый ключ (можно вернуть порядковый номер ключа в базе)
//	if (KeysData.keysCount >= MAX_KEYS_COUNT) // если память ключей заполнена
//		return 2; // не добавляем новый ключ
//	
//	for (uint8_t i = 0; i < 8; i++) // копируем новый ключ в конец базы
//    {
//		KeysData.keys[KeysData.keysCount][i] = newKey[i];
//	}

//	KeysData.keysCount++;
//	KeysData.nWrite++;
//		
//	KeysData.checksum = Do_CRC((uint8_t *)&KeysData, sizeof(KeysData) - 4); // считаем CRC;
//		
//	IAP_FullErase(); // полностью очищаем выделенную IAP
//	IAP_CopyRAMInIAP(0, &KeysData, sizeof(KeysData));

//	return 0;
//}

//uint8_t RemoveKey(uint8_t *newKey)
//{
//	uint32_t keyNumber = CheckTruth(newKey);
//	
//	if (keyNumber == UINT32_MAX) // если ключа нет в базе
//		return 4;  // то ничего не делаем
//	
//	for (uint32_t i = keyNumber; i < KeysData.keysCount; i++)
//	{
//		for (uint8_t j = 0; j < 8; j++)
//		{
//			KeysData.keys[i][j] = KeysData.keys[i + 1][j];
//			
//		}
//	}
//	
//	KeysData.keysCount--;
//	KeysData.nWrite++;
//	KeysData.checksum = Do_CRC((uint8_t *)&KeysData, sizeof(KeysData) - 4); // считаем CRC;
//	IAP_FullErase(); // полностью очищаем выделенную IAP
//	IAP_CopyRAMInIAP(0, &KeysData, sizeof(KeysData));
//	
//	return 3;
//}

//void ChangeKey(uint8_t keyNumber)
//{

//	for (uint8_t i = 0; i < 8; i++)
//    {
//		KeysData.keys[keyNumber][i] = keyCurrent[i];
//	}

//}


//uint8_t DS1990_GetID (void)	
//{	
//	uint8_t Presence = OneWire_Start();
//	delay_ms(1);
//	if (Presence) 
//	{
//		OneWire_Write (0x33); 
//		for (uint8_t i = 0; i < 8; i++)
//		{
//			keyCurrent[i] = OneWire_Read();
////			URT_Write(keyCurrent[i]);
//		}
//		return 1;
//	}
//	return 0;

//	
//}