#ifndef PRSM3_H
#define PRSM3_H

#include "timers.h"
#include "crc.h"
#include "usart.h"
#include "wdt.h"
#include "gpio.h"
#include "flash.h"
#include "keys.h"

#define RX_BUFFER_SIZE 24

#define DEVICE_ADDRESS_H 0x43
#define DEVICE_ADDRESS_L 0x10

#define TIMERWAITING 0xFF
#define TYPE_SENS 0x07

#define LOAD_SNERR (7 << 5)

extern uint8_t iptr, MessLen;
extern uint8_t RecBytes[RX_BUFFER_SIZE], CommandSize;
extern uint8_t PosylkaLen[4];
extern uint16_t usUsart; 

extern void PRSM3AddNewByte(void);
extern void PRSM3ReceiveLineComplete(void);
extern void ReturnReply(uint8_t RetCode);
extern void clearBuffer(void); 
#endif // PRSM3_H

