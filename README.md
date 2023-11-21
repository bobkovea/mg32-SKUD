*ВНИМАНИЕ: это не работающий вариант ПО, а демо-версия для резюме!*

# mg32-SKUD
+ Описание: ПО для платы контроллера СКУД TMC100.001 (система контроля и управления доступом)
+ Микроконтроллер: MG32F02A032AT20
+ Автор: Бобков Егор bobkovea@gmail.com
+ Версия: 1.00
+ Дата: 27.06.2023
+ Примечания:
  + настройка адреса в сети RS-485 и скорости обмена устройства по UART производится в файле "device_config.h";
  + настройка источника и частоты тактирования микроконтроллера производится в файле "MG32x02z_CSC_Init.h" на вкладке "Configuration Wizard" IDE Keil uVision.

## Назначение устройства
Защита шкафа управления от доступа к нему третьих лиц.

## Функционал устройства
+ идентификация электронных ключей, взаимодействующих со считывателем в шкафу управления
  + чтение идентификаторов с ключами TouchMemory (iButton) по интерфейсу 1-Wire
  + поддержка хеширования ID ключей по алгоритму MD5
  + база ключей хранится во внутренней флеш-памяти МК в зашифрованном виде
  + есть механизм активации/деактивации ключей.
+ реализация взаимодействия пользователя со шкафом на основе конечного автомата
  + Таблица состояний и переходов FSMTable (src\skud_algo.c):
```c++
Transition_t FSMTable[3][8] =
{
	[sNoAccessSleep][eDoorOpened] 		= { sNoAccessWaitingKey, hSleepToWaiting },
	[sNoAccessSleep][eDoorClosed] 		= { sNoAccessSleep, NULL },
 ...
	[sAccessGiven][eIndicationEnded] 	= { sAccessGiven, hIndicationStop },
	[sAccessGiven][eBusMessage] 		= { sAccessGiven, hParseBusMessage },
}
```
  + обработка состояния двери шкафа управления (сухой контакт)
  + звуковая и световая индикация событий (пьезопищалка и светодиоды).
+ прием и передача посылок посредством RS-485 (slave-устройство)
  + протокол обмена описан в документации \docs
  + детали реализации запросов и ответов описаны в api.c

api.h:
```c++
uint32_t API_ActivateKey(uint8_t operationType, uint8_t keyIndexMSB, uint8_t keyIndexLSB);
uint32_t API_SetVariable(uint8_t varNumber, uint8_t varValueMSB, uint8_t varValueLSB);
uint32_t API_DoCommand(uint8_t commNum, uint8_t commArg);
...
```

Также к устройству дополнительно прилагается симпатичный терминал для его тестирования. Можно изменять/считывать внутренние переменные и работать с ключами доступа. Написан на C#/WinForms, код смотреть в проекте STerminal, класс TMC.

![Безымянный333](https://github.com/bobkovea/mg32-SKUD/assets/52193810/f5e29e70-5787-4ea8-bf51-1b6fa2a28f68)
![image](https://github.com/bobkovea/mg32-SKUD/assets/52193810/595b2c50-e29f-42c7-9bf6-576420783a6b)

Печатная плата устройства

![Безымянный1](https://github.com/bobkovea/mg32-SKUD/assets/52193810/58d41889-ffa7-403e-9c5a-f72720ca7a7c)
![Безымянный](https://github.com/bobkovea/mg32-SKUD/assets/52193810/2f6be876-40dd-4d8d-b54e-74343aceaee2)

Ключи контактные и бесконтактный считыватель

![Безымянный3](https://github.com/bobkovea/mg32-SKUD/assets/52193810/1228b96b-bd96-402a-8cb1-0eb0a4c1ec83)




