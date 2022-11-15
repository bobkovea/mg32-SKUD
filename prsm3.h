#ifndef PRSM3_H
#define PRSM3_H

#include "timers.h"
#include "crc.h"
#include "usart.h"
#include "wdt.h"
#include "gpio.h"
#include "flash.h"
#include "keys.h"
#include "variables.h"

#define RX_BUFFER_SIZE 30

#define DEVICE_ADDRESS_H 0x43
#define DEVICE_ADDRESS_L 0x10

#define STATUS_COLLECTING_BYTES 0x00
#define STATUS_PARSE_WAITING 0x01


uint8_t RecBytes[RX_BUFFER_SIZE];
uint8_t MessageLen[4];
uint8_t	iptr, DecryptedMessLen, CommandSize, usUsart, parsingStatus;

void PRSM3_AddNewByte(void);
void PRSM3_ParseMessage(void);
void PRSM3_ReturnReply(uint8_t RetCode);
void PRSM3_clearBuffer(void); 

void PRSM3_ParseWriteRequest9(void);
void PRSM3_ParseWriteRequest24(void);
void PRSM3_ParseReadRequest(void);
#endif // PRSM3_H

