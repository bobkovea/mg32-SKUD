#include "buffer.h"

RingBuffer_t eBuffer =
{
	.size = BUFFER_SIZE,
	.writeOffset = 0,
	.readOffset = 0
};

uint8_t getNextWrite()
{
	return (eBuffer.writeOffset == (eBuffer.size - 1) ? 0 : eBuffer.writeOffset + 1);
}

uint8_t getNextRead()
{
	return (eBuffer.readOffset == (eBuffer.size - 1) ? 0 : eBuffer.readOffset + 1);
}

uint8_t isFull()
{
	return (eBuffer.readOffset == getNextRead());
}

uint8_t isEmpty()
{
	return (eBuffer.readOffset == eBuffer.writeOffset);
}

Events_t getEvent()
{
	if (!isEmpty())
	{
		Events_t data = eBuffer.buf[eBuffer.readOffset];
		eBuffer.readOffset = getNextRead();
		return data;
	}
	else
	{
		return 0;
	}
}

void putEvent(uint8_t data)
{
	if (!isFull())
	{
		eBuffer.buf[eBuffer.writeOffset] = data;
		eBuffer.writeOffset = getNextWrite();
	}
}