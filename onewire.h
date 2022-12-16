#ifndef ONEWIRE_H
#define ONEWIRE_H
#include "stdint.h" 
#include "timers.h" 
#include "gpio.h" 
uint8_t OneWire_Start (void); 
uint8_t OneWire_Read (void);
void OneWire_Write (uint8_t data);


#endif // ONEWIRE_H