#ifndef KEYS_H
#define KEYS_H
#include "MG32x02z_DRV.h"

#define IAP_SIZE IAP_SIZE_2048
#define IAP_PAGE_COUNT IAP_SIZE / IAP_PAGE_SIZE
#define IAP_FIRST_PAGE 0
#define IAP_LAST_PAGE (IAP_PAGE_COUNT - 1)
#define MAX_KEYS_COUNT (IAP_SIZE / 8 - 2)


#define KEYCNT_BYTE_POS 4
#define KEYCNT_WORD_POS KEYCNT_BYTE_POS / 4
#define NWRITE_WORD_POS (IAP_PAGE_SIZE / 4 - 2)
#define CRC_WORD_POS (IAP_PAGE_SIZE / 4 - 1)


uint8_t DS1990A_GetID (void);

void FillFlash(void);
uint8_t AddKey(uint8_t* newKey);
uint8_t RemoveKey(uint8_t *key);
uint32_t CheckTruth(uint8_t* key);

extern uint8_t keyCurrent[8];
extern boolean AlarmManual;
extern boolean SendEventPackages;
extern boolean AnyKeyAccess;
extern boolean ManualAddMode;
extern boolean NoNetworkPackages;


#endif // KEYS_H