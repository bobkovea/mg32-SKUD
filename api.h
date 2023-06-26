#ifndef API_H
#define API_H

#define FAILURE UINT32_MAX
#define SUCCESS 0

#include "stdint.h"
#include "variables.h"
#include "skud_algo.h"
#include "flash.h"

uint32_t API_ActivateKey(uint8_t operationType, uint8_t keyIndexMSB, uint8_t keyIndexLSB);
uint32_t API_SetVariable(uint8_t varNumber, uint8_t varValueMSB, uint8_t varValueLSB);
uint32_t API_DoCommand(uint8_t commNum, uint8_t commArg);

uint32_t API_AddKey(uint8_t newStatus, uint8_t keyIndexMSB, uint8_t keyIndexLSB, uint8_t *keyMSB);
uint32_t API_SetVariablePack(void *packStartAddr);

uint32_t API_GetVariable(uint8_t varNumber);
uint32_t API_CopyVariable(uint8_t varNumber, void *dest);
uint32_t API_CopyVariablePack(void *dest);

uint32_t API_GetKeyStatus(uint16_t keyIndex);
uint32_t API_CopyKeyByIndex(uint16_t keyIndex, void *dest);

uint32_t GetMaxFlashResource(void);
uint32_t UpdateFlashResource(uint8_t curPageNumber);

uint8_t API_IsRawKeyValid();

#endif // API_H