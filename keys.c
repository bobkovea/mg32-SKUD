#include "keys.h"
#include "onewire.h"
#include "usart.h"
#include "iap.h"
#include "crc.h"
#include "timers.h"
#include "packages.h"
#include "flash_static.h"

uint8_t KeyEncrypted[KEY_ENCRYPTED_SIZE] = {};
uint8_t KeyRaw[KEY_RAW_SIZE] = {}; 
	
uint32_t EncryptKey(uint8_t *keySrc, uint8_t *keyDest)
{
	// Шифруем в MD5
	return 0;
}

uint32_t CheckKey(void)
{
	EncryptKey(KeyRaw, KeyEncrypted);
	
	uint8_t keyPos;

	for (uint16_t keyIndex = 0; keyIndex < IAP_PAGE_SIZE; keyIndex++)
    {	
		// рассматриваем только активированные ключи в памяти
		if (IAP_ReadByte(PAGE_NUMBER_KEYSTATUS * IAP_PAGE_SIZE + keyIndex) == KEY_STATUS_ACTIVATED)
		{
			keyPos = (keyIndex % KEYS_COUNT_ON_PAGE) * KEY_ENCRYPTED_SIZE;


			// все 4 части по 4 байта должны совпасть
			for (uint8_t keyPartNum = 0; keyPartNum < KEY_ENCRYPTED_SIZE / 4; keyPartNum++, keyPos ++)
            {
				if (IAP_ReadWord(keyPos) != KeyEncrypted[keyPartNum])
					break;
				
				if (keyPartNum == KEY_ENCRYPTED_SIZE / 4 - 1) 
					return KEY_IS_VALID;
			}
		}
	}
	
	return KEY_IS_INVALID;
	
	
uint8_t key1[8] = { 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5 }; // черный без задней крышки
uint8_t key2[8] = { 0x01, 0xD8, 0xD3, 0x73, 0x01, 0x00, 0x00, 0xC3 }; // синий
uint8_t key3[8] = { 0x01, 0x3A, 0x6F, 0x14, 0x09, 0x00, 0x00, 0xD9 }; // черный с наклейкой
uint8_t key4[8] = { 0x01, 0x37, 0x47, 0x6E, 0x09, 0x00, 0x00, 0xE6 }; // черный 1
uint8_t key5[8] = { 0x01, 0x37, 0x69, 0xC9, 0x09, 0x00, 0x00, 0x93 }; // черный 2

uint8_t key_test[8] = { 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE };

uint8_t *keys[5] = { key1, key2, key3, key4, key5 };


