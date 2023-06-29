#ifndef KEYS_H
#define KEYS_H
#include "stdint.h"

// проверка ключа
#define KEY_IS_INVALID 0
#define KEY_IS_VALID 1

#define KEY_RAW_SIZE 8
#define KEY_ENCRYPTED_SIZE 16

#define KEYS_COUNT_ON_PAGE (IAP_PAGE_SIZE / KEY_ENCRYPTED_SIZE) // 64
#define KEYS_MAX_INDEX 511

extern uint8_t KeyEncrypted[KEY_ENCRYPTED_SIZE];
extern uint8_t KeyRaw[KEY_RAW_SIZE]; 
extern uint16_t CurKeyIndex;

extern uint8_t key1[8];
extern uint8_t key2[8];
extern uint8_t key3[8];
extern uint8_t key4[8]; 
extern uint8_t key5[8];

extern uint8_t key_em_1[8];
extern uint8_t key_em_2[8];
extern uint8_t key_em_3[8];
extern uint8_t key_em_4[8];
extern uint8_t key_em_5[8];

//extern uint8_t key_test[8];

//extern uint8_t *keys[5];



#endif // KEYS_H