#ifndef GPIO_H
#define GPIO_H
#include "MG32x02z_DRV.h"
#include "timers.h"

#define REDE_PIN PB10 

// пины адреса мультиплексора
#define ADR0 PB1 
#define ADR1 PB11 
#define ADR2 PB9
#define ADR3 PB8 

// канал выхода мультиплексора
#define CHx PB10 

// пины "SPI"
#define PIN_SDI PB3
#define PIN_LE PB0
#define PIN_CLK PB2

// соответствие входов адресам на мультиплексоре
#define S1 6
#define S2 7
#define S3 5
#define S4 4
#define S5 2
#define S6 3
#define S7 1
#define S8 0
#define S9 14
#define S10 15
#define S11 13
#define S12 12
#define S13 10
#define S14 11
#define S15 9
#define S16 8

// соответствие выходов сдвигового регистра номерам светодиодов (с нуля)
#define OUT15 8
#define OUT14 9
#define OUT13 10
#define OUT12 11
#define OUT11 12
#define OUT10 13
#define OUT9 14
#define OUT8 15
#define OUT7 0
#define OUT6 1
#define OUT5 2
#define OUT4 3
#define OUT3 4
#define OUT2 5
#define OUT1 6
#define OUT0 7

//#define LED_AMOUNT 16
//#define LAST_BYTE_NUMBER ((LED_AMOUNT - 1) / 8)
//#define LAST_BIT_NUMBER ((LED_AMOUNT - 1) % 8)


#define PIN_ZUMER PD2

extern uint8_t ModInpVar[16];
extern uint8_t mn;
extern uint8_t ThrHigh;
extern uint8_t ThrLow;
extern uint8_t MaxValue;
extern uint16_t ModInp;
extern uint8_t InpWasChange;

extern uint8_t pisk_cnt;
extern uint8_t pisk_max;

void SetAddress(uint8_t adr);
uint8_t InputRead(uint8_t i);
void LatchTest(void);
	
void UpdateLED(void);
void UpdateLED_SPI(void);
#endif // GPIO_H