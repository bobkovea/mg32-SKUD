//#ifndef KEYS_OLD
//#define KEYS_OLD
//#include "MG32x02z_DRV.h"


//#define MAX_KEYS_COUNT 100


//#pragma pack(push)
//#pragma pack(4)
//// структура 
//typedef struct {
//	uint32_t startWord; // индикатор заполненности flash
//	uint32_t keysCount; // текущее количество ключей
//	uint8_t keys[MAX_KEYS_COUNT][8]; 
//	uint32_t nWrite; // количество стираний страницы
//	uint32_t checksum; // контрольная сумма
//} flash_t;
//#pragma pack(pop)

//uint8_t DS1990_GetID (void);
//uint8_t IsKeyTrue(void);

//void FillFlash(void);
//void CopyFlash(void);
//uint8_t AddKey(uint8_t* newKey);
//uint8_t RemoveKey(uint8_t *key);
//uint32_t CheckTruth(uint8_t* key);

//extern uint8_t keyCurrent[8];
//extern flash_t KeysData;


//#endif // KEYS_OLD