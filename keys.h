#ifndef KEYS_H
#define KEYS_H
#include "MG32x02z_DRV.h"


#define MAX_KEYS_COUNT (IAP_SIZE / 8 - 2)




uint8_t DS1990_GetID (void);
uint8_t IsKeyTrue(void);

void FillFlash(void);
void CopyFlash(void);
uint8_t AddKey(uint8_t* newKey);
uint8_t RemoveKey(uint8_t *key);
uint32_t CheckTruth(uint8_t* key);

extern uint8_t keyCurrent[8];



#endif // KEYS_H