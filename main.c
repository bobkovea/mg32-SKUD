#include "main.h"
#include "skud_algo.h"

//uint8_t varPackage[11] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };

/*-------------------------------------------------------------------------------------
* Описание: программа для платы контроллера СКУД TMC100.001
 * Микроконтроллер: MG32F02A032
 * Автор: Бобков Е.А. e.bobkov@ivelsy.ru
 * Версия: 1.00
 * Дата: 30.12.2022
 * Примечания:
	- Настройка типа, адреса  и скорости обмена устройства производится в файле "device_config.h";
	- Настройка источника и частоты тактирования микроконтролллера производится в файле
	"MG32x02z_CSC_Init.h" в разделе "Configuration Wizard";
 -------------------------------------------------------------------------------------*/
 
int main()
{
	__disable_irq();
	
    ChipInit(); // настраиваем тактирование
	FlashFirstInit(); // первичная проверка конфиг. данных во флеше
	GPIO_Config(); 
	TIM_Config();
	USART_Config();
	WDT_Config();
	
	URT_Cmd(URT0, ENABLE); // включаем UART0
 
	TM_Timer_Cmd(TM_PRSM_RESET, ENABLE);  
	
	__enable_irq();

//	RS485_CONFIG_TRANSMIT();

    while(1) 
	{ 
		HandleEvent();
		wdt_reset();
    }
}



















