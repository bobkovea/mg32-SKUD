#include "ibutton.h"
#include "usart.h"

uint8_t DS1990A_GetKeyID (void)	
{	
	uint8_t Presence = OneWire_Start();
	if (Presence) 
	{
		OneWire_Write(ONEWIRE_READROM); 
		for (uint8_t i = 0; i < KEY_RAW_SIZE; i++)
			KeyRaw[i] = OneWire_Read();

		if (KeyRaw[0] != 0x01)
			return NO_KEY;

		if (KeyRaw[KEY_RAW_SIZE - 1] != Do_CRC(KeyRaw, KEY_RAW_SIZE - 1))
			return NO_KEY;
		// несколько считываний подряд ?
		// CRC мб корректна при нулевом ключе, когда полярность перепутана ?
//		URT_Print(KeyRaw, KEY_RAW_SIZE);
		
		return KEY_ON_LINE;
	}
	
	return NO_KEY;
}