#ifndef IBUTTON_H
#define IBUTTON_H
#include "timers.h"
#include "onewire.h"
#include "keys.h"
#include "crc.h"

uint8_t DS1990A_GetKeyID (void);

#define NO_KEY 0
#define KEY_ON_LINE 1


#endif // IBUTTON_H