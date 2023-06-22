#ifndef API_H
#define API_H

#define FAILURE UINT32_MAX
#define SUCCESS 0

#include "stdint.h"
#include "variables.h"
#include "skud_algo.h"
#include "flash.h"

uint32_t ActivateKey(uint8_t operationType, uint8_t keyIndexLSB, uint8_t keyIndexMSB);
uint32_t SetVariable(uint8_t varNumber, uint8_t varValueLSB, uint8_t varValueMSB);
uint32_t DoCommand(uint8_t commNum, uint8_t commArg);

uint32_t AddKey(uint8_t newStatus, uint8_t keyIndexLSB, uint8_t keyIndexMSB, uint8_t *keyMSB);
uint32_t SetVariablePack(uint8_t *packStartAddr);

uint32_t GetVariable(uint8_t varNumber);
uint32_t CopyVariable(uint8_t varNumber, void *dest);
uint32_t CopyVariablePack(void *dest);

uint32_t GetKeyStatus(uint16_t keyIndex);
uint32_t CopyKeyByIndex(uint16_t keyIndex, void *dest);

uint32_t GetMaxFlashResource(void);
uint32_t UpdateFlashResource(uint8_t curPageNumber);

#endif // API_H