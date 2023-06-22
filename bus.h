#ifndef BUS_H
#define BUS_H

#include "timers.h"
#include "crc.h"
#include "usart.h"
#include "wdt.h"
#include "gpio.h"
#include "flash.h"
#include "keys.h"
#include "variables.h"
#include "ring_buffer.h"


#define RS485_CONFIG_RECEIVE() REDE_PIN = 0 // настроить ADM485 на прием
#define RS485_CONFIG_TRANSMIT() REDE_PIN = 1 // настроить ADM485 на передачу

#define RX_BUFFER_SIZE 30 // Размер буфера приема/передачи

#define STATUS_COLLECTING_BYTES 0x00
#define STATUS_PARSE_WAITING 0x01

// вроде extern не нужны
extern uint8_t RecBytes[RX_BUFFER_SIZE];
extern uint8_t MessageLen[4];
extern volatile uint8_t iptr;
extern volatile uint8_t CommandSize;
extern volatile uint8_t usUsart;
extern volatile uint8_t parsingStatus;

void Bus_AddNewByte(void);
void Bus_ParseMessage(void);
void Bus_ReturnReply(uint8_t RetCode);
void Bus_ClearBuffer(void); 

void Bus_ParseWriteRequest9(void);
void Bus_ParseWriteRequest24(void);
void Bus_ParseReadRequest(void);
#endif // BUS_H

