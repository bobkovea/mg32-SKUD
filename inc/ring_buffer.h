#ifndef BUFFER_H
#define BUFFER_H
#include "stdint.h"
#include "skud_algo.h"

#define BUFFER_SIZE 5

typedef struct 
{
	uint8_t writeOffset;
    uint8_t readOffset;
    const uint8_t size;
    uint8_t buf[BUFFER_SIZE];
} RingBuffer_t;

extern RingBuffer_t eBuf;

void putEvent(uint8_t event);
uint8_t getEvent();


#endif // BUFFER_H