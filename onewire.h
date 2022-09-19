#ifndef ONEWIRE_H
#define ONEWIRE_H
#include "MG32x02z_DRV.h"

// настроить пин визардом!!
#define ONEWIRE_PIN PD0
uint8_t OneWire_Start (void);
uint8_t OneWire_Read (void);
void OneWire_Write (uint8_t data);


#endif // ONEWIRE_H