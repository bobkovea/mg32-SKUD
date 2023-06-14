#include "main.h"

/*-------------------------------------------------------------------------------------
 * Описание: программа для платы контроллера СКУД TMC100.001
 * Микроконтроллер: MG32F02A032
 * Автор: Бобков Е.А. e.bobkov@ivelsy.ru
 * Версия: 1.01
 * Дата: 17.01.2023
 * Примечания:
	- настройка адреса в сети RS-485 и скорости обмена устройства по UART производится в файле "device_config.h";
	- настройка источника и частоты тактирования микроконтроллера производится в файле
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
	
	URT_Cmd(URTX, ENABLE); // включаем UART0
 
	TM_Timer_Cmd(TM_PRSM_RESET, ENABLE);  
	__enable_irq();

	RS485_CONFIG_RECEIVE();
	//RS485_CONFIG_TRANSMIT();
	
    while(1) 
	{
		HandleEvent();
		wdt_reset();
    }
}



















