#ifndef KEYS_H
#define KEYS_H
#include "MG32x02z_DRV.h"

// проверка ключа
#define KEY_IS_INVALID 0
#define KEY_IS_VALID 1

#define KEY_RAW_SIZE 8
#define KEY_ENCRYPTED_SIZE 16

#define KEYS_COUNT_ON_PAGE (IAP_PAGE_SIZE / KEY_ENCRYPTED_SIZE) 
#define KEYS_MAX IAP_PAGE_SIZE

extern uint8_t KeyEncrypted[KEY_ENCRYPTED_SIZE];
extern uint8_t KeyRaw[KEY_RAW_SIZE]; 

uint8_t DS1990A_GetKeyID (void);

extern uint8_t key1[16];
extern uint8_t key2[16];
extern uint8_t key3[16];
extern uint8_t key4[16];
extern uint8_t key5[16];

extern uint8_t key_test[16];

extern uint8_t *keys[5];



#endif // KEYS_H