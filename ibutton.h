#ifndef IBUTTON_H
#define IBUTTON_H
#include "onewire.h"
#include "crc.h"

#define NO_KEY 0
#define KEY_ON_LINE 1

uint8_t DS1990A_GetKeyID (void);


#endif // IBUTTON_H