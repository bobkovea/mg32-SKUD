#ifndef GPIO_H
#define GPIO_H
#include "MG32x02z_DRV.h"
#include "timers.h"

#define REDE_PIN PB10 
#define PIN_ZUMER PB2

// настроить на push-pull

//#define BACKL_PIN PB1
//#define INDLED_PIN PB2
//#define DO_PIN PB8
//#define STALED_PIN PB9
//#define BUZZER_PIN PB10
//#define REDE_PIN PB11 

// настроить на DI
//#define ONEWIRE_PIN  PB0
//#define GERKON_PIN PB3






extern uint8_t ModInpVar[16];
extern uint8_t mn;
extern uint8_t ThrHigh;
extern uint8_t ThrLow;
extern uint8_t MaxValue;
extern uint16_t ModInp;
extern uint8_t InpWasChange;

extern uint8_t pisk_cnt;
extern uint8_t pisk_max;

uint8_t InputRead(uint8_t i);

#endif // GPIO_H