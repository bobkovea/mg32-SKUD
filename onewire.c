#include "onewire.h" 

//----------------------------------------------------------------------------------------
// Функция инициирует обмен данными с устройством 1-wire
//----------------------------------------------------------------------------------------
uint8_t OneWire_Start (void)
{
	uint8_t Response = 0;
	GPIO_PinMode_Select(PINB(0), PINX_Mode_OpenDrain_O); // настройка на выход
	ONEWIRE_PIN = 0;  // установка "LOW"
	delay_us(480);   // задержка в соответствии с даташитом

	GPIO_PinMode_Select(PINB(0), PINX_Mode_Digital_I);    // настройка на вход
	delay_us(80);    // задержка в соответствии с даташитом
	
	if (ONEWIRE_PIN == 0) 
	{
		Response = 1;    // если устройство подтянуло шину к земле, то оно на линии (presence)
	}

	delay_us(400);  // всего задержка в соответствии с даташитом 400 + 80 = 480мкс

	return Response;
}

//----------------------------------------------------------------------------------------
// Функция инициирует запись 
//----------------------------------------------------------------------------------------
void OneWire_Write (uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (data & 1 << i)  // если бит == 1
		{
			// записываем 1
			GPIO_PinMode_Select(PINB(0), PINX_Mode_OpenDrain_O);   // настройка на выход
			ONEWIRE_PIN = 0; // установка "LOW"
			delay_us(10);  // длина 

			GPIO_PinMode_Select(PINB(0), PINX_Mode_Digital_I);  // настройка на вход
			delay_us(70);  // по протоколу
		}

		else  // если бит == 0
		{
			// записываем 0
			GPIO_PinMode_Select(PINB(0), PINX_Mode_OpenDrain_O); // настройка на выход
			ONEWIRE_PIN = 0; // 
			delay_us (80); // по даташиту

			GPIO_PinMode_Select(PINB(0), PINX_Mode_Digital_I); // настройка на вход
		}
	}
}

uint8_t OneWire_Read (void)
{
	uint8_t value = 0;
	
	for (uint8_t i = 0; i < 8; i++)
	{
		GPIO_PinMode_Select(PINB(0), PINX_Mode_OpenDrain_O);   // настройка на выход
		ONEWIRE_PIN = 0; 
		delay_us(10);  

		GPIO_PinMode_Select(PINB(0), PINX_Mode_Digital_I);  // настройка на вход
		if (ONEWIRE_PIN)  // если бит = 1
		{
			value |= 1 << i;  // прочитанный бит = 1
		}
		delay_us(70);  // по даташиту
	}
	
	return value;
}