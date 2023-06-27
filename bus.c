#include "bus.h"

// текущий номер байта
uint8_t volatile iptr = 0;
// совместный буфер для принимаемой посылки и посылки-ответа
uint8_t RecBytes[RX_BUFFER_SIZE];
// длина посылки (полученная при приеме и расшифрованная)
uint8_t	volatile MessLen = 0;
// массив с длинами посылок
uint8_t MessageLenArr[4] = { 4, 6, 9, 24 };
// длина посылки (фактическая)
uint8_t	volatile CommandSize = 0;
// счетчик ожидания очистки буфера после приема последнего байта посылки
uint8_t volatile usUsart = 0; 
// приняли все байты (а посылки) или еще нет
uint8_t volatile parsingStatus = STATUS_COLLECTING_BYTES; 


//----------------------------------------------------------------------------------------
// Функция вызывается при приеме каждого нового байта
//----------------------------------------------------------------------------------------
void Bus_AddNewByte(void) // вызывается когда пришел очередной байт
{
	usUsart = 1; // защита от случая, когда прием завис
	
	// после конца посылки вычитываем приходящие "лишние байты"
    if (parsingStatus == STATUS_PARSE_WAITING || iptr == RX_BUFFER_SIZE)
	{ 
		URT_GetRXData(URT0);
		return;
    }
	// пока массив-буфер не переполнен, кладем туда по байту
	RecBytes[iptr] = URT_GetRXData(URT0);

	// в третьем байте зашифрована длина посылки
    if (iptr++ == FCODE_POS)
		MessLen = MessageLenArr[(RecBytes[FCODE_POS] >> 3) & 3]; // & 0b11
	
	// дошли по конца посылки, переходим к её парсингу
	if (iptr == MessLen && MessLen != 0)
	{
		parsingStatus = STATUS_PARSE_WAITING; // переходим в состояние парсинга
		putEvent(eBusMessage);	
	}
}

//----------------------------------------------------------------------------------------
// Функция парсит пришедшую посылку,
// На основе принятой посылки формирует посылку-ответ
// Посылка-ответ записывается в тот же массив RecBytes
//----------------------------------------------------------------------------------------
void Bus_ParseMessage(void)
{
	// Сколько было фактически принято байт
	CommandSize = iptr;

	// Проверка адреса 
	if ((RecBytes[ADDRMSB_POS] != DEVICE_ADDRESS_MSB) ||
		(RecBytes[ADDRLSB_POS] != DEVICE_ADDRESS_LSB)) 
		return;
	
	// Расшифровываем код функции
	uint8_t FunctionCode = RecBytes[FCODE_POS] & 0x1F; // & 0b11111

	switch (FunctionCode)
	{
		case FCODE_WRITE9:
			Bus_ParseWriteRequest9();
			break;
		
		case FCODE_WRITE24:
			Bus_ParseWriteRequest24();
			break;
		
		case FCODE_READ6:
			Bus_ParseReadRequest();
			break;
		
		default:
			Bus_ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE9);
	}
}

void Bus_ParseWriteRequest9(void)
{
	uint32_t operStatus; // статус успеха операции
	
	if (CommandSize != 9) // как это возможно исходя из логики?
	{
		Bus_ReturnReply(ECODE_WRONG_LEN | FCODE_WRITE4);
		return;
	}

	// Проверка контрольной суммы
	if (CRCisWrong(RecBytes, CommandSize))
	{
		CommandSize = 9;
		Bus_ReturnReply(ECODE_WRONG_CRC | FCODE_WRITE4);
		return;
	}
	
	switch (RecBytes[SCODE_POS])
	{
		case SCODE_ACTKEY:
			operStatus = API_ActivateKey(RecBytes[ACTKEY_OPTYPE_POS], 
										 RecBytes[ACTKEY_KEYINDEX_MSB_POS], 
										 RecBytes[ACTKEY_KEYINDEX_LSB_POS]);
			break;
		
		case SCODE_WRITEVAR1:
			operStatus = API_SetVariable(RecBytes[WRITEVAR1_NUM_POS], 
										 RecBytes[WRITEVAR1_VALUE_MSB_POS], 
										 RecBytes[WRITEVAR1_VALUE_LSB_POS]);
			break;
		
		case SCODE_COMM:
			
			operStatus = API_DoCommand(RecBytes[COMM_NUM_POS], 
									   RecBytes[COMM_ARG_POS]);
			break;
		
		default:
			CommandSize = 4;
			Bus_ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE4);
			return;
    }
	CommandSize = 4;
	
	if (operStatus == FAILURE)
		Bus_ReturnReply(ECODE_READ_WRITE | FCODE_WRITE4);
	else 
		Bus_ReturnReply(FCODE_WRITE4);
	return;
}

void Bus_ParseWriteRequest24(void)
{
	uint32_t operStatus; // статус успеха операции
	
	if (CommandSize != 24)
	{
		Bus_ReturnReply(ECODE_WRONG_LEN | FCODE_WRITE4);
		return;
	}

	// Проверка контрольной суммы
	if (CRCisWrong(RecBytes, CommandSize))
	{
		CommandSize = 4;
		Bus_ReturnReply(ECODE_WRONG_CRC | FCODE_WRITE4);
		return;
	}

	CommandSize = 4;
	
	switch (RecBytes[SCODE_POS])
	{
		case SCODE_ADDKEY:
			if (RecBytes[ADDKEY_INDEX_MSB_POS] == 0xFF && RecBytes[ADDKEY_INDEX_LSB_POS] == 0xFF)
			{
				operStatus = API_AddKeySmart(RecBytes[ADDKEY_ACT_STAT_POS],
											 &RecBytes[ADDKEY_KEY_MSB_POS]);
			}
			else
			{
				operStatus = API_AddKey(RecBytes[ADDKEY_ACT_STAT_POS], 
										RecBytes[ADDKEY_INDEX_MSB_POS], 
										RecBytes[ADDKEY_INDEX_LSB_POS], 
										&RecBytes[ADDKEY_KEY_MSB_POS]);
			}
			break;
		
		case SCODE_WRITEVARM:
			operStatus = API_SetVariablePack(&RecBytes[WRITEVARM_VALUE_1ST_POS]);
			break;

		default:
			Bus_ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE4);
			return;
	}

		if (operStatus == FAILURE)
			Bus_ReturnReply(ECODE_READ_WRITE | FCODE_WRITE4);
		else 
			Bus_ReturnReply(FCODE_WRITE4);
		return;
}

void Bus_ParseReadRequest(void)
{
	if (CommandSize != 6)
	{
		Bus_ReturnReply(ECODE_WRONG_LEN | FCODE_READ9);
		return;
	}

	// Проверка контрольной суммы
	if (CRCisWrong(RecBytes, CommandSize))
	{
		CommandSize = 9;
		Bus_ReturnReply(ECODE_WRONG_CRC | FCODE_READ9);
		return;
	}
	
	uint32_t operStatus; // статус успеха операции
	
	switch (RecBytes[SCODE_POS])
	{
		case SCODE_READVAR1:
			
			operStatus = API_CopyVariable(RecBytes[READVAR1_NUM_POS],
										  &RecBytes[READVAR1_VALUE_MSB_POS]);
			if (operStatus == FAILURE)
			{
				CommandSize = 9;
				Bus_ReturnReply(ECODE_WRONG_PARAM | FCODE_READ9);
				return;
			}
		
			CommandSize = 9;
			Bus_ReturnReply(FCODE_READ9);
			break;
		
		case SCODE_READVARM:
			
			API_CopyVariablePack(&RecBytes[READVARM_VALUE_1ST_POS]);

			CommandSize = 24;
			Bus_ReturnReply(FCODE_READ24);
			break;
			
		case SCODE_READVALIDKEY:
			
			if (ValidKeyIndex.value != ValidKeyIndex.factoryValue)
			{	
				RecBytes[4] = 0x00;
				RecBytes[5] = (uint8_t) (ValidKeyIndex.value >> 8);
				RecBytes[6] = (uint8_t) ValidKeyIndex.value;
				memcpy(&RecBytes[7], KeyEncrypted, KEY_ENCRYPTED_SIZE);
				
				CommandSize = 24;
				Bus_ReturnReply(FCODE_READ24);

				ValidKeyIndex.value = ValidKeyIndex.factoryValue;
				API_CopyVariablesPage0ToFlash();
				return;
			}
			else 
			{
				RecBytes[4] = RecBytes[5] = RecBytes[6] = RecBytes[7] = 0x00;
				CommandSize = 9;
				Bus_ReturnReply(FCODE_READ9);
			}
			break;
	
		default:
			CommandSize = 9;
			Bus_ReturnReply(ECODE_WRONG_FUNC | FCODE_READ9);
			return;
    }
}

//----------------------------------------------------------------------------------------
// Функция вычисляет CRC и оправляет посылку-ответ
// Посылка хранится в массиве RecBytes
// |Байт адреса1|Байт адреса2|Код команды с ошибкой| Команда | CRC |
// CommandSize должна содержать полное число байт посылки
//----------------------------------------------------------------------------------------

//void Bus_ReturnReply(uint8_t RetCode, void *txBuffer, uint8_t commandSize)
void Bus_ReturnReply(uint8_t RetCode)
{
	RS485_CONFIG_TRANSMIT(); // ADM485 на передачу
	
	// Кладем код ответа в посылку-ответ 
	RecBytes[2] = RetCode;
	
	// Считаем и добавляем CRC в посылку-ответ
    RecBytes[CommandSize - 1] = Do_CRC(RecBytes, CommandSize - 1);
	
	// Отправляем посылку-ответ, дожидаемся окончания передачи
	URT_Print(RecBytes, CommandSize);
	
	RS485_CONFIG_RECEIVE(); // ADM485 на прием
}

void Bus_ClearBuffer()
{
    iptr = 0;
    MessLen = 0;
	parsingStatus = STATUS_COLLECTING_BYTES;
	usUsart = 0;
	RS485_CONFIG_RECEIVE();
}