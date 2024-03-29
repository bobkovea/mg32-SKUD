#ifndef GPIO_H
#define GPIO_H
#include "MG32x02z_GPIO_DRV.h"

#define ALTER_FUNC_PC0_TX0 10
#define ALTER_FUNC_PC0_RX0 10

#define BUZZER_ON() BACKL_PIN = 1 /*BUZZER_PIN = 1*/
#define BUZZER_OFF() BACKL_PIN = 0 /*BUZZER_PIN = 0*/

#define STALED_ON() STALED_PIN = 0
#define STALED_OFF() STALED_PIN = 1

typedef enum 
{
	INITIAL_RESET = 0,
	INITIAL_SET = 1
} InitialState_t;

typedef enum 
{
	PULLUP_DISABLE = 0,
	PULLUP_ENABLE = 1
} PullupState_t;

#define BACKL_PIN PB1 
#define INDLED_PIN PB2
#define DO_PIN 	PB8
#define STALED_PIN PB9
#define BUZZER_PIN PB10
#define REDE_PIN PB11 
#define ONEWIRE_PIN PB0
#define ONEWIRE_DIR_PIN PINB(0)
#define GERKON_PIN PB3

void GPIO_Config();

#endif // GPIO_H