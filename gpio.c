#include "gpio.h"


uint8_t pisk_cnt = 0;

uint8_t pisk_max = 20;

// счетчик антидребезга для входов
uint8_t ModInpVar[16];

// Счетчик числа измерений входов
uint8_t mn = 0;

// Максимальный и минимальный порог изменения скользящего среднего
uint8_t ThrHigh = 50;
uint8_t ThrLow = 10;

// Максимальное значение скользящего окна
uint8_t MaxValue = 60;

// Переменная состояний входов
uint16_t ModInp;

// Переменная определяющая, что состояние входов было прочитано
uint8_t InpWasChange = 0;



// массив соответстия входов их адресам мультиплексора
uint8_t InputsAddr[16] = { S1, S2, S3, S4, S5, S6, S7, S8,
S9, S10, S11, S12, S13, S14, S15, S16 };

// устанавливаем адрес канала мультиплексора (от 0 до 15)
void SetAddress(uint8_t address) {
	ADR0 = address & 0b0001;
	ADR1 = address & 0b0010;
	ADR2 = address & 0b0100;
	ADR3 = address & 0b1000;
}

uint8_t InputRead(uint8_t i) {
	SetAddress(InputsAddr[i]);
	return CHx ? 0 : 1; //	return !CHx;
}


// массив соответствия выходов сдвигового регистра номерам светодиодов
uint8_t LEDOrder[16] = { OUT15, OUT14, OUT13, OUT12, 
						 OUT11, OUT10, OUT9, OUT8,
						 OUT7, OUT6, OUT5, OUT4, 
						 OUT3, OUT2, OUT1, OUT0 };

// для теста сдвигового регистра
void LatchTest(void) {
	uint16_t var = 0b0101010101010101;
//	uint16_t var = 0xFFFF;
//	uint16_t var = 0x0000;
	for (uint8_t i = 0; i < 16; i++)
	{
	if(var & 1) 
		PIN_SDI = 0;
    else 
		PIN_SDI = 1;
	
		var >>= 1;
        delay_us(1);
	
        PIN_CLK = 1;
        delay_us(1);
        PIN_CLK = 0;
        delay_us(1);
    }
    
    PIN_LE = 1;
    delay_us(1);
    PIN_LE = 0;
}	
						 
void UpdateLED(void) {
//	uint8_t screen[2];
// 	выводим значения индикации в порты
//    uint8_t byteNumber = LAST_BYTE_NUMBER;
//    uint8_t bitNumber = LAST_BIT_NUMBER;

    for(uint8_t i = 0; i < 16; i++)
    {
//        if(screen[byteNumber] & (1 << bitNumber)) PIN_SDI = 0;
		
		if(ModInp & (1 << LEDOrder[i]))
			PIN_SDI = 0;
        else 
			PIN_SDI = 1;
		
        delay_us(1);
		
        PIN_CLK = 1;
        delay_us(1);
        PIN_CLK = 0;
        delay_us(1);
//		
//        if (bitNumber == 0)
//		{
//			byteNumber--;
//			bitNumber = 7; 
//		}

//		else bitNumber--;
    }
    
    PIN_LE = 1;
    delay_us(1);
    PIN_LE = 0;
}
	