#include "keys.h"

uint8_t key1[8] = { 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5 }; // черный без задней крышки
uint8_t key2[8] = { 0x01, 0xD8, 0xD3, 0x73, 0x01, 0x00, 0x00, 0xC3 }; // синий
uint8_t key3[8] = { 0x01, 0x3A, 0x6F, 0x14, 0x09, 0x00, 0x00, 0xD9 }; // черный с наклейкой
uint8_t key4[8] = { 0x01, 0x37, 0x47, 0x6E, 0x09, 0x00, 0x00, 0xE6 }; // черный 1
uint8_t key5[8] = { 0x01, 0x37, 0x69, 0xC9, 0x09, 0x00, 0x00, 0x93 }; // черный 2

uint8_t key_em_1[8] = { 0x01, 0xC6, 0xC1, 0xD2, 0x00, 0x4C, 0x00, 0x2F }; // мастер-ключ
uint8_t key_em_2[8] = { 0x01, 0xCB, 0xEC, 0xD2, 0x00, 0x4C, 0x00, 0x71 };
uint8_t key_em_3[8] = { 0x01, 0x0F, 0xDE, 0xD2, 0x00, 0x4C, 0x00, 0x35 };
uint8_t key_em_4[8] = { 0x01, 0xDD, 0xE0, 0xD2, 0x00, 0x4C, 0x00, 0xB9 };
uint8_t key_em_5[8] = { 0x01, 0xD9, 0xC1, 0xD2, 0x00, 0x4C, 0x00, 0x50 };

//uint8_t *keys[5] = { key1, key2, key3, key4, key5 };

//uint8_t key_test[8] = { 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE };

uint8_t KeyEncrypted[KEY_ENCRYPTED_SIZE];
uint8_t KeyRaw[KEY_RAW_SIZE]; 
uint16_t CurKeyIndex = 0;
	
//uint32_t EncryptKey(uint8_t *keySrc, uint8_t *keyDest)
//{
//	// Шифруем в MD5
//	// MD5_Encrypt();
//	return 0;
//}


//// Проверка ключа на присутствие и активацию
//uint32_t CheckKey(uint8_t *keyArr)
//{
//	
////	EncryptKey(KeyRaw, KeyEncrypted);
//	
//	// позиция первого байта ключа во флеше
//	uint8_t keyPosInFlash;

//	for (uint16_t keyIndex = 0; keyIndex < IAP_PAGE_SIZE; keyIndex++)
//    {
//		// рассматриваем только активированные ключи в памяти
//		if (GetKeyStatus(keyIndex) == KEY_STATUS_ACTIVATED)
//		{
//			// позиция, соответствующая ключу с рассматриваемым индексом
//			keyPosInFlash = (keyIndex % KEYS_COUNT_ON_PAGE) * KEY_ENCRYPTED_SIZE;
//			// собственно проверка на соответствие
//			if (IAP_IsEqualToRAM(keyPosInFlash, keyArr, KEY_ENCRYPTED_SIZE))
//				return KEY_IS_VALID;
//		}
//	}
//	return KEY_IS_INVALID;
//}

	



