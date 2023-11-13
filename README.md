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
	[sNoAccessSleep][eDoorOpened] 				= { sNoAccessWaitingKey, hSleepToWaiting },
	[sNoAccessSleep][eDoorClosed] 				= { sNoAccessSleep, NULL },
 ...
	[sAccessGiven][eIndicationEnded] 			= { sAccessGiven, hIndicationStop },
	[sAccessGiven][eBusMessage] 			        = { sAccessGiven, hParseBusMessage },
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
Печатная плата устройства

![плата_top](https://github.com/bobkovea/mg32-SKUD/assets/52193810/e7921a8e-56d3-485b-8935-77139d90294c)
![плата_bot](https://github.com/bobkovea/mg32-SKUD/assets/52193810/da3d5485-feb0-40c6-93dd-cbba72628bb1)

Ключи контактные и бесконтактный считыватель
![считыватель](https://github.com/bobkovea/mg32-SKUD/assets/52193810/ceaace7d-561b-4039-a0f7-7998bfedb36b)




