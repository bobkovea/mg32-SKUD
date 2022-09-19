#include "spi.h"

#define PIN_NSS PB0

void SPI_Init(void) {
	
	SPI_DeInit(SPI0);
  
	// настройка частоты SPI (сейчас 1 МГц для F_CPU = 12 МГц)
    SPI_Clock_Select(SPI0, SPI_CK_SPIx_PR);                     // CK_SPIx = CK_SPIx_PR
    SPI_PreDivider_Select(SPI0, SPI_PDIV_2);                    // PDIV outpu = CK_SPIx /2
    SPI_Prescaler_Select(SPI0, SPI_PSC_3);                      // Prescaler outpu = PDIV outpu /3
    SPI_Divider_Select(SPI0, SPI_DIV_2);                        // DIV outpu = PDIV outpu /2

	// настройка параметров передачи
    SPI_DataLine_Select(SPI0, SPI_Standard);                    // SPI data line standard SPI
    SPI_ModeAndNss_Select(SPI0, SPI_Master);                    // Master
    SPI_ClockPhase_Select(SPI0, SPI_LeadingEdge);               // CPHA = 0
    SPI_ClockPolarity_Select(SPI0, SPI_Low);                    // CPOL = 0
    SPI_FirstBit_Select(SPI0, SPI_MSB);                         // MSB first
    SPI_DataSize_Select(SPI0, SPI_8bits);                       // Data size 8bits
    
	PIN_InitTypeDef PINX_InitStruct;

	// настройка IO
    PINX_InitStruct.PINX_Mode               = PINX_Mode_PushPull_O;     // Pin select push pull mode
    PINX_InitStruct.PINX_PUResistant        = PINX_PUResistant_Enable;  // Enable pull up resistor
    PINX_InitStruct.PINX_Speed              = PINX_Speed_Low;           
    PINX_InitStruct.PINX_OUTDrive           = PINX_OUTDrive_Level0;     // Pin output driver full strength.
    PINX_InitStruct.PINX_FilterDivider      = PINX_FilterDivider_Bypass;// Pin input deglitch filter clock divider bypass
    PINX_InitStruct.PINX_Inverse            = PINX_Inverse_Disable;     // Pin input data not inverse
    PINX_InitStruct.PINX_Alternate_Function = 2;                        // Pin AFS = 2
    GPIO_PinMode_Config(PINB(2),&PINX_InitStruct);                      // CLK setup at PB2
    
    PINX_InitStruct.PINX_OUTDrive           = PINX_OUTDrive_Level2;     // Pin output drive strength 1/4
    GPIO_PinMode_Config(PINB(3),&PINX_InitStruct);                      // MOSI setup at PB3
    
    PINX_InitStruct.PINX_Alternate_Function = 0;                        // Pin AFS = 0
    GPIO_PinMode_Config(PINB(0),&PINX_InitStruct);                      // NSS setup at PB0
    
//    PINX_InitStruct.PINX_Mode               = PINX_Mode_Digital_I;      // Setting digital  mode
//    PINX_InitStruct.PINX_Alternate_Function = 2;                        // Pin AFS = 2
//    GPIO_PinMode_Config(PINB(1),&PINX_InitStruct);                      // MISO setup at PB1

    SPI_Cmd(SPI0, ENABLE);                                              // Enable SPI
}


void SPI_Write(uint8_t c) {
	PIN_NSS = 0;
	while(SPI_GetSingleFlagStatus(SPI0, SPI_BUSYF))
		;
    SPI_SetTxData(SPI0, SPI_1Byte, c); // записываем байт в регистр данных
	while(!SPI_GetSingleFlagStatus(SPI0, SPI_TCF)) // передача полностью окончена
		;
	for(uint8_t dly_cnt = 5; dly_cnt > 0; dly_cnt--) // задержка нужная, из библиотеки
		__NOP();
	PIN_NSS = 1;
}
