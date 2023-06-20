#include "ring_buffer.h"

RingBuffer_t eBuf =
{
	.size = BUFFER_SIZE,
	.writeOffset = 0,
	.readOffset = 0
};

uint8_t getNextWrite()
{
	return (eBuf.writeOffset == (eBuf.size - 1) ? 0 : eBuf.writeOffset + 1);
}

uint8_t getNextRead()
{
	return (eBuf.readOffset == (eBuf.size - 1) ? 0 : eBuf.readOffset + 1);
}

uint8_t isFull()
{
	return (eBuf.readOffset == getNextRead());
}

uint8_t isEmpty()
{
	return (eBuf.readOffset == eBuf.writeOffset);
}

uint8_t getEvent()
{
	if (!isEmpty())
	{
		uint8_t event = eBuf.buf[eBuf.readOffset];
		eBuf.readOffset = getNextRead();
		return event;
	}
	return eNoEvent;
}

void putEvent(uint8_t event)
{
	if (!isFull())
	{
		eBuf.buf[eBuf.writeOffset] = event;
		eBuf.writeOffset = getNextWrite();
	}
}