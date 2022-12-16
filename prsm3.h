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
#include "events.h"

// настроить ADM485 на прием
#define RS485_CONFIG_RECEIVE() REDE_PIN = 0;
// настроить ADM485 на передачу
#define RS485_CONFIG_TRANSMIT() REDE_PIN = 1;

#define RX_BUFFER_SIZE 30

#define DEVICE_ADDRESS_MSB 0x43
#define DEVICE_ADDRESS_LSB 0x10

#define STATUS_COLLECTING_BYTES 0x00
#define STATUS_PARSE_WAITING 0x01

extern uint8_t RecBytes[RX_BUFFER_SIZE];
extern uint8_t MessageLen[4];
extern uint8_t iptr;
extern uint8_t DecryptedMessageLen;
extern uint8_t CommandSize;
extern uint8_t usUsart;
extern uint8_t parsingStatus;

void PRSM3_AddNewByte(void);
void PRSM3_ParseMessage(void);
void PRSM3_ReturnReply(uint8_t RetCode);
void PRSM3_clearBuffer(void); 

void PRSM3_ParseWriteRequest9(void);
void PRSM3_ParseWriteRequest24(void);
void PRSM3_ParseReadRequest(void);
#endif // PRSM3_H

