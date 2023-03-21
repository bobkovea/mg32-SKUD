#include "prsm3.h"

// текущий номер байта
uint8_t iptr = 0;
// совместный буфер для принимаемой посылки и посылки-ответа
uint8_t RecBytes[RX_BUFFER_SIZE];
// длина посылки (полученная при приеме и расшифрованная)
uint8_t	DecryptedMessageLen = 0;
// массив с длинами посылок
uint8_t MessageLenArr[4] = { 4, 6, 9, 24 };
// длина посылки (фактическая)
uint8_t	CommandSize = 0;
// счетчик ожидания очистки буфера после приема последнего байта посылки
uint8_t usUsart = 0; 
// приняли все байты (а посылки) или еще нет
uint8_t parsingStatus = STATUS_COLLECTING_BYTES; 
// статус успеха операции
uint32_t operStatus;

//----------------------------------------------------------------------------------------
// Функция вызывается при приеме каждого нового байта
//----------------------------------------------------------------------------------------
void PRSM3_AddNewByte(void) // вызывается когда пришел очередной байт
{
	// после конца посылки вычитываем приходящие "лишние байты"
    if ((parsingStatus == STATUS_PARSE_WAITING) || (iptr >= RX_BUFFER_SIZE))
	{
		URT_GetRXData(URT0); // проверить, можно ли обойтись без этого
		return;
    }
					
	// пока массив-буфер не переполнен, кладем туда по байту
	RecBytes[iptr] = URT_GetRXData(URT0);
	
	// в третьем байте зашифрована длина посылки
    if (iptr++ == FCODE_POS)
		DecryptedMessageLen = MessageLenArr[(RecBytes[FCODE_POS] >> 3) & 3];
	
	// дошли по конца посылки, переходим к её парсингу
    if (DecryptedMessageLen != 0)
	{
        if (iptr == DecryptedMessageLen)
		{
            parsingStatus = STATUS_PARSE_WAITING;
			TM_Timer_Cmd(TM01, ENABLE); // запускаем таймер на 1ms // start_parsing
        }
    }
}  

//----------------------------------------------------------------------------------------
// Функция парсит пришедшую посылку,
// На основе принятой посылки формирует посылку-ответ
// Посылка-ответ записывается в тот же массив RecBytes
//----------------------------------------------------------------------------------------
void PRSM3_ParseMessage(void)
{
	// Отключаем таймер
	TM_Timer_Cmd(TM01, DISABLE); 
	
	// Сколько было фактически принято байт
	CommandSize = iptr;

    // обнуляем всё
    DecryptedMessageLen = 0;
    iptr = 0;
	parsingStatus = STATUS_COLLECTING_BYTES;
	
	// Задержка до отправки ответа
	delay_ms(2);

	// Проверка адреса 
	if ((RecBytes[ADDRMSB_POS] != DEVICE_ADDRESS_MSB) ||
		(RecBytes[ADDRLSB_POS] != DEVICE_ADDRESS_LSB)) 
		return;
	
	// Расшифровываем код функции
	uint8_t FunctionCode = RecBytes[FCODE_POS] & 0x1F;
	
	switch (FunctionCode)
	{
		case FCODE_WRITE9:
			PRSM3_ParseWriteRequest9();
			break;
		
		case FCODE_WRITE24:
			PRSM3_ParseWriteRequest24();
			break;
		
		case FCODE_READ6:
			PRSM3_ParseReadRequest();
			break;
		
		default:
			PRSM3_ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE9);
	}
}

void PRSM3_ParseWriteRequest9(void)
{
	if (CommandSize != 9) // как это возможно исходя из логики?
	{
		PRSM3_ReturnReply(ECODE_WRONG_LEN | FCODE_WRITE4);
		return;
	}

	// Проверка контрольной суммы
	if (CRCisWrong(RecBytes, CommandSize))
	{
		PRSM3_ReturnReply(ECODE_WRONG_CRC | FCODE_WRITE4);
		return;
	}
	
	switch (RecBytes[SCODE_POS])
	{
		case SCODE_ACTKEY:
			operStatus = ActivateKey(RecBytes[ACTKEY_OPTYPE_POS], 
									 RecBytes[ACTKEY_KEYINDEX_LSB_POS], 
									 RecBytes[ACTKEY_KEYINDEX_MSB_POS]);
			break;
		
		case SCODE_WRITEVAR1:
			operStatus = SetVariable(RecBytes[WRITEVAR1_NUM_POS], 
									 RecBytes[WRITEVAR1_VALUE_LSB_POS], 
									 RecBytes[WRITEVAR1_VALUE_MSB_POS]);
			break;
		
		case SCODE_COMM:
			
			operStatus = DoCommand(RecBytes[COMM_NUM_POS], 
								   RecBytes[COMM_ARG_POS]);
			break;
		
		default:
			CommandSize = 4;
			PRSM3_ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE4);
			return;
    }
	CommandSize = 4;
	if (operStatus == FAILURE)
		PRSM3_ReturnReply(ECODE_READ_WRITE | FCODE_WRITE4);
	else 
		PRSM3_ReturnReply(FCODE_WRITE4);
	return;
}

void PRSM3_ParseWriteRequest24(void)
{
	if (CommandSize != 24)
	{
		PRSM3_ReturnReply(ECODE_WRONG_LEN | FCODE_WRITE4);
		return;
	}

	// Проверка контрольной суммы
	if (CRCisWrong(RecBytes, CommandSize))
	{
		PRSM3_ReturnReply(ECODE_WRONG_CRC | FCODE_WRITE4);
		return;
	}
	
	CommandSize = 4;
	
	switch (RecBytes[SCODE_POS])
	{
		case SCODE_ADDKEY:
			operStatus = AddKey(RecBytes[ADDKEY_ACT_STAT_POS], 
						 RecBytes[ADDKEY_INDEX_LSB_POS], 
						 RecBytes[ADDKEY_INDEX_MSB_POS], 
						 &RecBytes[ADDKEY_KEY_MSB_POS]);
			break;
		
		case SCODE_WRITEVARM:
			operStatus = SetVariablePack(&RecBytes[WRITEVARM_VALUE_1ST_POS]);
			break;

		default:
			PRSM3_ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE4);
			return;
	}

		if (operStatus == FAILURE)
			PRSM3_ReturnReply(ECODE_READ_WRITE | FCODE_WRITE4);
		else 
			PRSM3_ReturnReply(FCODE_WRITE4);
		return;
}

void PRSM3_ParseReadRequest(void)
{
	if (CommandSize != 6)
	{
		PRSM3_ReturnReply(ECODE_WRONG_LEN | FCODE_READ9);
		return;
	}

	// Проверка контрольной суммы
	if (CRCisWrong(RecBytes, CommandSize))
	{
		PRSM3_ReturnReply(ECODE_WRONG_CRC | FCODE_READ9);
		return;
	}
	
	switch (RecBytes[SCODE_POS])
	{
		uint32_t var;
		uint8_t *tmpAddr;
		
		case SCODE_READVAR1:
			
			var = GetVariable(RecBytes[READVAR1_NUM_POS]);
			if (var == FAILURE)
			{
				CommandSize = 9;
				PRSM3_ReturnReply(ECODE_WRONG_PARAM | FCODE_READ9);
				return;
			}
		
			RecBytes[READVAR1_VALUE_LSB_POS] = var;
			RecBytes[READVAR1_VALUE_MSB_POS] = var >> 8;
		
			CommandSize = 9;
			PRSM3_ReturnReply(FCODE_READ9);
			break;
		
		case SCODE_READVARM:
	
			tmpAddr = &RecBytes[READVARM_VALUE_1ST_POS];

			for (uint8_t varNum = 0; varNum < VAR_COUNT; varNum++)
			{
				var = variables[varNum]->value;
				
				// отделяем двухбайтные переменные от однобайтных
				
				for (uint8_t byteNum = 0; byteNum < variables[varNum]->byteSize; byteNum++)
				{
					*tmpAddr++ = var >> (8 * byteNum);
				}
			}
			
			CommandSize = 24;
			PRSM3_ReturnReply(FCODE_READ24);
			break;
	
		default:
			CommandSize = 9;
			PRSM3_ReturnReply(ECODE_WRONG_FUNC | FCODE_READ9);
			return;
    }
}

void PRSM3_EventResponse(MainEvent_t *event)
{
	RecBytes[SCODE_POS] 			 = event->eventNum;
	RecBytes[EVENT_STATUS_POS] 		 = event->status << 7 |
									   event->repetitionCount;
	RecBytes[EVENT_TIME_POS] 		 = event->time;
	RecBytes[EVENT_KEYINDEX_LSB_POS] = event->keyIndex;
	RecBytes[EVENT_KEYINDEX_MSB_POS] = event->keyIndex >> 8;
	
	CommandSize = 9;
	PRSM3_ReturnReply(FCODE_EVENT9);
	return;
}

//----------------------------------------------------------------------------------------
// Функция вычисляет CRC и возвращает посылку-ответ
// Посылка хранится в массиве RecBytes
// |Байт адреса1|Байт адреса2|Код команды с ошибкой| Команда | CRC |
// CommandSize должна содержать полное число байт посылки
//----------------------------------------------------------------------------------------
void PRSM3_ReturnReply(uint8_t RetCode) // можно минимизировать
{
	RS485_CONFIG_TRANSMIT(); // ADM485 на передачу
	
	// Кладем код ответа в посылку-ответ 
	RecBytes[2] = RetCode;
	
	// Считаем и добавляем CRC в посылку-ответ
    RecBytes[CommandSize - 1] = Do_CRC(RecBytes, CommandSize - 1);

	// Запускаем wdt на ~1с (на случай, если отправка зависнет)
    wdt_enable(WDTO_1S);
	
	// Отправляем посылку-ответ, дожидаемся завершения передачи
	URT_Print(RecBytes, CommandSize);
	
	RS485_CONFIG_RECEIVE(); // ADM485 на прием
}

void PRSM3_clearBuffer() // что-то непонятное
{
    iptr = 0;
    DecryptedMessageLen = 0;
    usUsart = 0;
	parsingStatus = STATUS_COLLECTING_BYTES;
	RS485_CONFIG_RECEIVE();
}