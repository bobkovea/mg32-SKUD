#include "main.h"

/*-------------------------------------------------------------------------------------
 * Описание: программа для платы контроллера СКУД TMC100.001
 * Микроконтроллер: MG32F02A032AT20
 * Автор: Бобков Е.А. e.bobkov@ivelsy.ru
 * Версия: 1.00
 * Дата: 21.06.2023
 * Примечания:
	- настройка адреса в сети RS-485 и скорости обмена устройства по UART производится в файле "device_config.h";
	- настройка источника и частоты тактирования микроконтроллера производится в файле
	"MG32x02z_CSC_Init.h" на вкладке "Configuration Wizard";
 -------------------------------------------------------------------------------------*/
 
int main()
{
	__disable_irq();
	
    ChipInit(); // настраиваем тактирование
	GPIO_Config(); 
	TIM_Config();
	USART_Config();
	WDT_Config(); 
	IAP_Init(IAP_PAGE_COUNT);
	
	PowerOnHandle(); // первичная проверка конфиг. данных во флеше 
	
	RS485_CONFIG_RECEIVE();	
//	RS485_CONFIG_TRANSMIT();

	URT_Cmd(URT0, ENABLE); // включаем UART0
	
	TM_Timer_Cmd(TM_READ_GERKON, ENABLE); // начинаем мониторить состояние двери
	
	wdt_enable(WDTO_1S); // включаем watchdog на 1с
	
	__enable_irq();

    while(1) 
	{
		HandleEvent(); 
		wdt_reset();
    }
}







