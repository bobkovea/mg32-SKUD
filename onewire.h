#ifndef ONEWIRE_H
#define ONEWIRE_H
#include "stdint.h" 
#include "timers.h" 
#include "gpio.h" 
void OneWire_SetDirection(PINX_Mode_TypeDef dir);
uint8_t OneWire_Start (void); 
uint8_t OneWire_Read (void);
void OneWire_Write (uint8_t data);

#define ONEWIRE_SKIPROM 0xCC // игнорирование адресации
#define ONEWIRE_READROM 0x33 // чтение ПЗУ
#define ONEWIRE_MATCHROM 0x55 // совпадение ПЗУ (выбор конкретного устройства на линии)
#define ONEWIRE_SEARCHROM 0xF0 // поиск ПЗУ (для определения устройств на линии)

#endif // ONEWIRE_H