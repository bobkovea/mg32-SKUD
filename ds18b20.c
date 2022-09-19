#include "timers.h"
#include "onewire.h"

void DS18B20_GetTemperature (void)	
{
	uint8_t Presence = OneWire_Start();
	delay_ms(1);
	if (Presence) 
	{
		OneWire_Write (0xCC);  // skip ROM
		OneWire_Write (0x44);  // convert t
		
		// при паразитном питании обязательно!!!
		GPIO_PinMode_Select(PIND(0), PINX_Mode_PushPull_O); 
		PD0 = 1; 
		//
		delay_ms(800); // ждем преобразование 750мс
		
		Presence = OneWire_Start();
		delay_ms(1);
		OneWire_Write (0xCC);  // skip ROM
		OneWire_Write (0xBE);  // Read Scratch-pad

		uint8_t Temp_byte1 = OneWire_Read();
		uint8_t Temp_byte2 = OneWire_Read();

		uint16_t temp = (Temp_byte2 << 8) | Temp_byte1;
		float temperature = (float)temp / 16;
		
		int int_part = (int)temperature;
		int float_part = (int) ((temperature - int_part) * 100);
		
		uint8_t out_mas[6];
		
		out_mas[0] = (uint8_t)(int_part / 10) + '0';
		out_mas[1] = (uint8_t)(int_part % 10) + '0';
		out_mas[2] = '.';
		out_mas[3] = (uint8_t)(float_part / 10) + '0';
		out_mas[4] = (uint8_t)(float_part % 10) + '0'; 
		out_mas[5] = '\n'; 
//		for (uint32_t i = 0; i < 6; i++)
//		{
//			URT_Write (out_mas[i]);
//			delay_ms(1);
//		}
	}
}