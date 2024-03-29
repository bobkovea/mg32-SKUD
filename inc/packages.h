#ifndef PACKAGES_H
#define PACKAGES_H

/* макросы ниже не используются: код переменной определяются 
   как её индекс в массиве variables */

#define GERKON_FILT_TIME_CODE 0x00
#define PROTECTION_DELAY_TIME_CODE 0x01
#define BUZZER_OFF_TIME_CODE 0x02
#define CHECK_KEY_DISABLED_CODE  0x03
#define ACCESS_IS_GIVEN_CODE 0x04
#define VALID_KEY_INDEX_CODE 0x05
#define TOTAL_KEYS_CODE 0x06
#define ACTIVE_KEYS_CODE 0x07
#define FLASH_RESOURSE_CODE 0x08


// макросы для разных посылок

#define KEY_STATUS_DEACTIVATED 0x00
#define KEY_STATUS_ACTIVATED 0x01
#define KEY_STATUS_FREE 0xFF

#define ACTKEY_DEACTIVATE 0x00
#define ACTKEY_ACTIVATE 0x01
#define ACTKEY_NOACTION 0x02

#define COMM_ALLKEYACT 0x00
#define COMM_FACTORY_NUM 0x01


/* Коды функций (FCODE) */
#define FCODE_WRITE4 0x05
#define FCODE_WRITE9 0x14
#define FCODE_WRITE24 0x1E

#define FCODE_READ6 0x0A
#define FCODE_READ9 0x13
#define FCODE_READ24 0x1D

/* Коды подфункций (SCODE) */

#define SCODE_ACTKEY 0x00
#define SCODE_WRITEVAR1 0x01
#define SCODE_COMM 0x02

#define SCODE_ADDKEY 0x00
#define SCODE_WRITEVARM 0x01

#define SCODE_READVAR1 0x00
#define SCODE_READVARM 0x01
#define SCODE_READVALIDKEY 0x02

/* Коды ошибок (ECODE) */

#define ECODE_OK 0x00 // нет ошибки 
#define ECODE_READ_WRITE 0x20 // Ошибка установления / чтения параметра
#define ECODE_WRONG_ADDR 0x40 // Отсутствие физического устройства с таким параметром (Нет параметра с таким номером или параметра указанного типа)
#define ECODE_WRONG_PARAM 0x60 // Неверное значение параметра 
#define ECODE_WRONG_LEN 0x80 // Неверная длина посылки для данной функции
#define ECODE_WRONG_FUNC 0xA0 // Контроллер не поддерживает такой функции
#define ECODE_WRONG_CRC 0xE0 // Контроллер получил пакет с ошибкой (неверная CRC)


/* Позиций байтов посылок по протоколу */

// общие позиции для всех посылок
#define ADDRMSB_POS 0
#define ADDRLSB_POS 1
#define FCODE_POS 2
#define SCODE_POS 3
#define CRC4_POS 3
#define CRC6_POS 5
#define CRC9_POS 8
#define CRC24_POS 23


/* I Установка значения переменной */

/* 
1) Активация / деактивация ключа по индексу (ACTKEY) 
*/

#define ACTKEY_OPTYPE_POS 4
#define ACTKEY_KEYINDEX_MSB_POS 5
#define ACTKEY_KEYINDEX_LSB_POS 6

/* 
2) Установление значения одной переменной (WRITEVAR1)
*/

#define WRITEVAR1_NUM_POS 4
#define WRITEVAR1_VALUE_MSB_POS 5
#define WRITEVAR1_VALUE_LSB_POS 6

/* 
3) Общие команды (COMM)
*/
#define COMM_NUM_POS 4
#define COMM_ARG_POS 5


/* 
4) Добавление / изменения ключа в памяти считывателя по индексу (API_AddKey) 
*/

#define ADDKEY_ACT_STAT_POS 4
#define ADDKEY_INDEX_MSB_POS 5
#define ADDKEY_INDEX_LSB_POS 6
#define ADDKEY_KEY_MSB_POS 7

/* 
5) Установление значения пакета переменных (WRITEVARM)
*/
 
#define WRITEVARM_VALUE_1ST_POS 4
  
/* II Запрос значения переменной */
 

/* 
1) Запрос значения одной переменной (READVAR1)
*/

#define READVAR1_NUM_POS 4

// Ответ
#define READVAR1_VALUE_MSB_POS 5
#define READVAR1_VALUE_LSB_POS 6

/* 
2) Запрос значения пакета переменных (READVARM)
*/
// Ответ:
#define READVARM_VALUE_1ST_POS 4


#endif // PACKAGES_H
