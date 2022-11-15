#include "flash.h"
#include "crc.h"


// создаем структуру, повторяющую flash
Config_t cfg = {0};

// текущая позиция начала актуального блока
uint32_t CurLastBlockPos = 0;

//----------------------------------------------------------------------------------------
// Функция возвращает начальный индекс  последнего записанного блока в IAP
// Поиск происходит начиная с индекса StartIndex по индекс EndIndex, Step - размер блока
// Возвращает UINT32_MAX, если память далее затерта
// ex: FindLastBlockPos(0, MEM_GetIAPSize(), sizeof(cfg));
//----------------------------------------------------------------------------------------
uint32_t FindLastBlockPos(uint32_t StartIndex, uint32_t EndIndex, uint32_t BlockSize) {
	uint32_t i;
	for (i = StartIndex; i <= EndIndex - BlockSize; i += BlockSize) {
		if (IAP_ReadByte(i) == 0xFF) {
			return i - BlockSize;
			// Если вся следующая после этого блока память тоже чистая
			if (IAP_IsAreaEmpty (i, MEM_GetIAPSize() - 1)) {
				return i - BlockSize; // возвращаем адрес начала актуального блока (все ОК)
			}
			return UINT32_MAX; // где-то после этого блока память испорчена
		}
	}
	return i; // возвращаем адрес начала актуального блока (все ОК, но память уже заполнена)
}

//----------------------------------------------------------------------------------------
// Функция заполняет структуру конфигурационных данных значениями по умолчанию
// ex: FillStructureDefault();
//----------------------------------------------------------------------------------------
void FillStructureDefault(void) {
	// Вносим значения по умолчанию в структуру в RAM
	cfg.FlashKey = FlashKeyValue;
	cfg.ThrHigh = ThrHighDefault;
	
	cfg.NWrite = 1; // количество записей во flash
	cfg.CheckSum = Do_CRC((uint8_t *)&cfg, sizeof(cfg) - 4); // считаем CRC
	
}
	
//----------------------------------------------------------------------------------------
// Начальная инициализация флеш-памяти (IAP)
// 1) Если память полностью чиста, вносим в начало значения по умолчанию
// 2) Если в памяти что-то есть, то проверяем данные на корректность
// 3) Если данные некорректны, то очищаем память и записываем значения по умолчанию; если да - принимаем их как актуальные
// ex: FlashtStartupHandle()
//----------------------------------------------------------------------------------------
FlashStatus FlashStartupHandle(void) {
	
	// Если IAP полностью пуста, то запишем значения по умолчанию
	if (IAP_IsFullEmpty()) {
		FillStructureDefault();
		CurLastBlockPos = 0;
		IAP_CopyRAMInIAP(CurLastBlockPos, &cfg, sizeof(cfg)); // запишем структуру по умолчанию из RAM в начало IAP
		return OK_EMPTY;
	}
	// Если же в IAP уже что-то есть, то ищем последний записанный (актуальный) блок и проверяем его CRC
	else {
		CurLastBlockPos = FindLastBlockPos(0, MEM_GetIAPSize(), sizeof(cfg)); // Получаем индекс начала актуального блока
		
		// если память где-то далее затерта
		if (CurLastBlockPos == UINT32_MAX) {
			IAP_FullErase(); // полностью очищаем выделенную IAP
			FillStructureDefault();
			CurLastBlockPos = 0; // обнулим текущую позицию актуального блока
			IAP_CopyRAMInIAP(CurLastBlockPos, &cfg, sizeof(cfg)); // запишем структуру по умолчанию из RAM в начало IAP
			
			return ERROR_BAD_MEMORY;
		}
		// если же память далее чистая и оно цельное
		else {
			// Если CRC актуального блока не корректная, то очистим IAP и заполним значениями по умолчанию
			if (CRCisWrong((uint8_t *)(IAP_START_ADDRESS + CurLastBlockPos), sizeof(cfg) - 3)) { 
				IAP_FullErase(); // полностью очищаем выделенную IAP
				FillStructureDefault();
				CurLastBlockPos = 0; // обнулим текущую позицию актуального блока
				IAP_CopyRAMInIAP(CurLastBlockPos, &cfg, sizeof(cfg)); // запишем структуру по умолчанию из RAM в начало IAP
				return ERROR_CRC;
			}
			// Если CRC корректна, то примем этот блок как актуальный
			else {
				IAP_CopyIAPInRAM(CurLastBlockPos, &cfg, sizeof(cfg)); // запишем последний блок из IAP в структуру RAM
				return OK_NOT_EMPTY;
			}
		}

	}
}

//----------------------------------------------------------------------------------------
// Функция возвращает количество оставшихся блоков до конца IAP
// ex: GetBlocksLeft(CurLastBlockPos, sizeof(cfg));
//----------------------------------------------------------------------------------------
uint16_t GetBlocksLeft(uint32_t CurLastBlockPos, uint32_t BlockSize) {
	// предположим, общий размер выделенной IAP <= 64 Кбайт
	uint16_t totalBlocks = MEM_GetIAPSize() / sizeof(cfg); // максимальное число блоков
	return totalBlocks - (CurLastBlockPos / BlockSize + 1);
};


//----------------------------------------------------------------------------------------
// Функция проверяет, есть ли свободное место в IAP для записи нового блока
// ex: IsEnoughSpace(476, sizeof(cfg));
//----------------------------------------------------------------------------------------
uint8_t IsEnoughSpace(uint32_t CurIndex, uint32_t BlockSize) {
	return CurIndex + BlockSize <= MEM_GetIAPSize();
}

//----------------------------------------------------------------------------------------
// Функция записывает новый блок данных в IAP
//----------------------------------------------------------------------------------------
void FlashUpdate(void) {
	
	cfg.CheckSum = Do_CRC((uint8_t *)&cfg, sizeof(cfg) - 4); // считаем CRC
	CurLastBlockPos += sizeof(cfg);
	
	// проверим наличие свободного места в памяти для структуры
	if (!IsEnoughSpace(CurLastBlockPos, sizeof(cfg))) {
	
		IAP_FullErase(); // полностью очищаем выделенную IAP
		cfg.NWrite++; // инкрементируем количество записей во flash
		CurLastBlockPos = 0; // обнулим текущую позицию актуального блока
	}
	IAP_CopyRAMInIAP(CurLastBlockPos, &cfg, sizeof(cfg)); // запишем структуру из RAM в свободную область IAP	

}