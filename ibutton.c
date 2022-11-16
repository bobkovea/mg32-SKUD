#include "ibutton.h"
#include "usart.h"

uint8_t DS1990A_GetKeyID (void)	
{	
	uint8_t Presence = OneWire_Start();
	delay_ms(1);
	if (Presence) 
	{
		OneWire_Write (0x33); 
		for (uint8_t i = 0; i < KEY_RAW_SIZE; i++)
		{
			KeyRaw[i] = OneWire_Read();
//			URT_Write(keyCurrent[i]);
		}
		if (KeyRaw[KEY_RAW_SIZE - 1] == Do_CRC(KeyRaw, KEY_RAW_SIZE - 1))
			return KEY_ON_LINE;
		// несколько считываний подряд (?)
	}
	return NO_KEY;

}