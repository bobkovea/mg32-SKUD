#ifndef CRC_H
#define CRC_H

#include "stdint.h"

uint8_t Do_CRC(uint8_t* Array, uint32_t Amount);
uint8_t CRCisWrong(uint8_t* Array, uint8_t CRCNumber);
#endif // CRC_H 