#include "packages.h"
#include "prsm3.h"
#include "flash_static.h"

void PRSM3ParseWriteRequest9(void)
{
	if (CommandSize != 9)
	{
		ReturnReply(ECODE_WRONG_LEN | FCODE_WRITE4);
		return;
	}

// Проверка контрольной суммы
//	if (CRCisWrong(RecBytes, CommandSize))
//	{
//		ReturnReply(ECODE_WRONG_CRC | FCODE_WRITE4);
//		return;
//	}
	
	switch (RecBytes[SCODE_POS])
	{
		uint32_t operStatus;
		
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
			ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE4);
			return;
		
		CommandSize = 4;
		if (operStatus == UINT32_MAX)
			ReturnReply(ECODE_READ_WRITE | FCODE_WRITE4);
		else 
			ReturnReply(FCODE_WRITE4);
		return;
    }
}


void PRSM3ParseWriteRequest24(void)
{
	if (CommandSize != 24)
	{
		ReturnReply(ECODE_WRONG_LEN | FCODE_WRITE4);
		return;
	}

// Проверка контрольной суммы
//	if (CRCisWrong(RecBytes, CommandSize))
//	{
//		ReturnReply(ECODE_WRONG_CRC | FCODE_WRITE4);
//		return;
//	}
	
	switch (RecBytes[SCODE_POS])
	{
		case SCODE_ADDKEY:
			AddKey(RecBytes[ADDKEY_ACT_STAT_POS], 
				   RecBytes[ADDKEY_INDEX_LSB_POS], 
				   RecBytes[ADDKEY_INDEX_MSB_POS], 
				   &RecBytes[ADDKEY_KEY_MSB_POS]);
			break;
		
		case SCODE_WRITEVARM:
			SetVariablePack(&RecBytes[WRITEVARM_VALUE_1ST_POS]);
			break;

		default:
			CommandSize = 4;
			ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE4);
			return;
	}
			
	CommandSize = 4;
	ReturnReply(FCODE_WRITE4);
}

void PRSM3ParseReadRequest(uint8_t fcode)
{
	if (CommandSize != 6)
	{
		ReturnReply(ECODE_WRONG_LEN | FCODE_READ9);
		return;
	}

// Проверка контрольной суммы
//	if (CRCisWrong(RecBytes, CommandSize))
//	{
//		ReturnReply(ECODE_WRONG_CRC | FCODE_READ9);
//		return;
//	}
	
	switch (RecBytes[SCODE_POS])
	{
		uint32_t var;
		
		case SCODE_READVAR1:
			var = GetVariable(RecBytes[READVAR1_NUM_POS])
		
			if (var == UINT32_MAX)
			{
				ReturnReply(ECODE_WRONG_PARAM | FCODE_READ9);
				return;
			}
		
			RecBytes[READVAR1_VALUE_LSB_POS] = (uint8_t) var;
			RecBytes[READVAR1_VALUE_MSB_POS] = (uint8_t) (var >> 8);
		
			CommandSize = 9;
			ReturnReply(FCODE_READ9);
			break;
		
		case SCODE_READVARM:
			for (uint8_t i = 0, j = READVARM_VALUE_1ST_POS; i < sizeof(VarsLenMas); i++, j++)
			{
				var = GetVariable(i);
				if (var == UINT32_MAX)
				{
					ReturnReply(ECODE_WRONG_PARAM | FCODE_READ9);
					return;
				}
				if (VarsLenMas[i] == 1) {
					RecBytes[j] = (uint8_t) var;
				}
				
				else if (VarsLenMas[i] == 2)
				{
					RecBytes[j++] = (uint8_t) var;
					RecBytes[j] = (uint8_t) (var >> 8);
				}
				
				CommandSize = 24;
				ReturnReply(FCODE_READ24);
				break;
			}
		
		default:
			CommandSize = 9;
			ReturnReply(ECODE_WRONG_FUNC | FCODE_READ9);
			return;
    }
}




void PRSM3ReceiveLineComplete(void)
{
		
	uint8_t FunctionCode;
	
	// Отключаем таймер
	TM_Timer_Cmd(TM01, DISABLE); 

	// Сколько было фактически принято байт
	CommandSize = iptr;

    // обнуляем всё
    MessLen = 0;
    iptr = 0;
	usUsart = 0;
	
	// Задержка до отправки ответа
    delay_ms(2);
	
	// Проверка адреса 
	if ((RecBytes[ADDRMSB_POS] != DEVICE_ADDRESS_H) || (RecBytes[ADDRLSB_POS] != DEVICE_ADDRESS_L)) 
	{
		ReturnReply(ECODE_WRONG_ADDR | FCODE_WRITE4);
		return;
	}
	
	// Расшифровываем код функции
	FunctionCode = RecBytes[2] & 0x1F;
	
	switch (FunctionCode)
	{
		case FCODE_WRITE9:
			PRSM3ParseWriteRequest9();
			break;
		
		case FCODE_WRITE24:
			PRSM3ParseWriteRequest24();
			break;
		
		case FCODE_READ6:
			PRSM3ParseReadRequest();
			break;
		
		default:
			ReturnReply(ECODE_WRONG_FUNC | FCODE_WRITE9);
	}

}