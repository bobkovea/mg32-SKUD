#include "prsm3.h"


// текущий номер байта
uint8_t iptr = 0;
// совместный буфер для принимаемой посылки и посылки-ответа
uint8_t RecBytes[RX_BUFFER_SIZE];
// длина посылки (полученная при приеме и расшифрованная)
uint8_t	MessLen = 0;
// массив с длинами посылок
uint8_t PosylkaLen[4] = { 4, 13, 9, 22 };
// длина посылки (фактическая)
uint8_t	CommandSize;
// счетчик ожидания очистки буфера после приема последнего байта посылки
uint16_t usUsart = 0; 

//----------------------------------------------------------------------------------------
// Функция вызывается при приеме каждого нового байта
//----------------------------------------------------------------------------------------
void PRSM3AddNewByte(void) // вызывается когда пришел очередной байт
{
	// после конца посылки вычитываем приходящие "лишние байты"
    if (MessLen == TIMERWAITING) { 
		URT_GetRXData(URT0);
        return;
    }
	// пока массив-буфер не переполнен, кладем туда по байту
    if (iptr < RX_BUFFER_SIZE) {
        RecBytes[iptr] = URT_GetRXData(URT0);
        iptr++;
    } else
        URT_GetRXData(URT0);

	// в третьем байте зашифрована длина посылки
    if (iptr == 3) {
		MessLen = 13 /*PosylkaLen[(RecBytes[iptr - 1] >> 3) & 3]*/; //  т.е. PosylkaLen[1] == 13;
    }

	// дошли по конца посылки, переходим к её парсингу
    if (MessLen != 0) {
        if (iptr == MessLen) {
            MessLen = TIMERWAITING;
			TM_Timer_Cmd(TM01, ENABLE); // запускаем таймер на 1ms
        }
    }
}  

//----------------------------------------------------------------------------------------
// Функция парсит пришедшую посылку,
// На основе принятой посылки формирует основную часть посылки-ответа
// Посылка-ответ записывается в тот же массив RecBytes
//----------------------------------------------------------------------------------------
void PRSM3ReceiveLineComplete(void)
{
		
	uint8_t FunctionCode;
	
	// Отключаем таймер
	TM_Timer_Cmd(TM01, DISABLE); 

	// Сколько было фактически принято байт
	CommandSize = iptr;

    // öбнуляем всё
    MessLen = 0;
    iptr = 0;
	usUsart = 0;
	
	// Задержка до отправки ответа
    delay_ms(2);
	
	// Проверка адреса 
	if ((RecBytes[0] != DEVICE_ADDRESS_H)|| (RecBytes[1] != DEVICE_ADDRESS_L)) {
		return;
	}
	
	// Расшифровываем код функции
	FunctionCode = RecBytes[2] & 0x1F; // == RecBytes[2]

	// Если код функции 0x0A
	if (FunctionCode == 0x0A)
		{
		// Если длина команды вдруг не 13, то все пропало
		if (CommandSize != 13)
			return;
		
		// Если контрольная посылки неверна, то все пропало
		if (CRCisWrong(RecBytes, 13))
		{
			ReturnReply(LOAD_SNERR | 0x13); // == ReturnReply(0xF3)
            return;
		}
		
		RecBytes[0] = DEVICE_ADDRESS_H;
        RecBytes[1] = DEVICE_ADDRESS_L;
		
		// Отправляем параметр, соответствующий типу пришедшего запроса
		switch (RecBytes[3])
		{
		#ifdef DEBUG 
			uint16_t blocksLeft; 
		#endif
			
		case 0x00: 
            RecBytes[5] = (uint8_t) ModInp;
			RecBytes[6] = (uint8_t) (ModInp >> 8);
			break;
		case 0x01: 
			RecBytes[5] = InpWasChange; 
			break;
		
		#ifdef DEBUG
		case 0x04:
			RecBytes[5] = (uint8_t) (cfg.NWrite >> 8);
            RecBytes[6] = (uint8_t) cfg.NWrite;
            break;
		case 0x05:
			blocksLeft = GetBlocksLeft(CurLastBlockPos, sizeof(cfg));
			RecBytes[5] = (uint8_t) (blocksLeft >> 8);
            RecBytes[6] = (uint8_t) blocksLeft;
            break;
		#endif
		
		default: 
			RecBytes[5] = 0; break;
        }
		

        CommandSize = 9;
        ReturnReply(0x13);
        return;
    }
	
    if (FunctionCode == 0x14) // Установка значения переменной
    {
//		for (uint32_t i = 0; i < 13; i++)
//       {
//			URT_Write(RecBytes[i]);
//       }
		
        // Проверка контрольной суммы
        if (CRCisWrong(RecBytes, 13))
		{
            ReturnReply(LOAD_SNERR | 0x05); // == ReturnReply(0xE5)
            return;
        }
		
		for (uint8_t i = 0; i < 8; i++)
		{
				keyCurrent[i] = RecBytes[i + 4]; // и можно без этого
//				URT_Write(keyCurrent[i]);
		}
        switch (RecBytes[3])
		{
        case 0: // 
			RecBytes[3] = AddKey(keyCurrent); // 0 - ключ успешно добавлен; 1 - ключ уже есть; 2 - место закончилось
            break;
		case 1:
			RecBytes[3] = RemoveKey(keyCurrent); // 3 - ключ успешно удален; 4 - такого ключа нет
			break;
        default:
			for (uint8_t i = 3; i < 13; i++) RecBytes[i] = 0;
            break;
        }
        CommandSize = 13;
			
        ReturnReply(0x05);
        return;
    }
	
	// Если код функции неправильный, то такой ответ
	ReturnReply(0xA0);
}


//----------------------------------------------------------------------------------------
// Функция вычисляет CRC и возвращает посылку-ответ
// Посылка хранится в массиве RecBytes
// |Байт адреса1|Байт адреса2|Код команды с ошибкой| Команда | CRC |
// CommandSize должна содержать полное число байт посылки
//----------------------------------------------------------------------------------------
void ReturnReply(uint8_t RetCode)
{
	// Если какая либо ошибка приема
    REDE_PIN = 1; // ADM485 на передачу
	
	// Кладем код ответа в посылку-ответ 
	RecBytes[2] = RetCode;
	
	// Считаем и добавляем CRC в посылку-ответ
    RecBytes[CommandSize - 1] = Do_CRC(RecBytes, CommandSize - 1);

	// Запускаем wdt на ~1с (на случай, если отправка зависнет)
    wdt_enable(WDTO_1S);
	
	// Отправляем посылку-ответ
    for (uint8_t i = 0; i < CommandSize; i++) {
		URT_Write(RecBytes[i]);
    };
	// Дожидаемся завершения передачи
	while(URT_IsTxEndTransmission() == TxBusy)	
		;
	
	REDE_PIN = 0; // ADM485 на прием
}

void clearBuffer() // что-то непонятное
{
    iptr = 0;
    MessLen = 0;
    usUsart = 0;

    REDE_PIN = 0;
}