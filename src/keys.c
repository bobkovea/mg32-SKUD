#include "keys.h"

/* для справки: те же ключи, только в зашифрованном виде (md5)

key1_encoded = { 0x62, 0xAB, 0x7A, 0xDF, 0x2A, 0xE1, 0x79, 0x1C, 0x46, 0x1A, 0x73, 0x6F, 0xEF, 0x59, 0x97, 0x4B }
key2_encoded = { 0x78, 0x1E, 0xBD, 0x77, 0x89, 0x6C, 0xD, 0x1D, 0xD, 0x1F, 0x19, 0x4C, 0x76, 0x7, 0xDD, 0x33 }
key3_encoded = { 0x5F, 0x18, 0xE0, 0xB4, 0x5F, 0x20, 0x51, 0xDF, 0x93, 0x97, 0x32, 0xD4, 0x22, 0xD8, 0xE, 0xEA }
key4_encoded = { 0xE2, 0xD0, 0x8D, 0xCF, 0xE8, 0xD4, 0x76, 0x53, 0x9B, 0xEE, 0x89, 0x95, 0x97, 0x95, 0x83, 0x4F }
key5_encoded = { 0x15, 0xAB, 0xD1, 0x1, 0x2B, 0xD2, 0xEB, 0xB5, 0x2, 0xB3, 0xEE, 0xED, 0x6F, 0xE, 0x80, 0x93 }

key_em_1_encoded = { 0x92, 0xBC, 0x62, 0xE4, 0x8C, 0x3C, 0xBC, 0xFE, 0x22, 0xE1, 0x9B, 0x56, 0x6E, 0xA4, 0x92, 0x9F }
key_em_2_encoded = { 0xAE, 0xAD, 0x3F, 0xF1, 0xA7, 0x6E, 0x7A, 0x6C, 0x58, 0xF7, 0x6F, 0x2, 0xD5, 0x4C, 0x48, 0x18 }
key_em_3_encoded = { 0xC9, 0x1C, 0xE7, 0x29, 0xAC, 0x7E, 0xEE, 0x2D, 0x73, 0x27, 0x4, 0x82, 0x5A, 0xF5, 0x1D, 0x9F }
key_em_4_encoded = { 0x81, 0xD3, 0x36, 0x1C, 0xA8, 0xB4, 0xF5, 0xEF, 0xFE, 0xAA, 0xA3, 0xEA, 0xC1, 0x35, 0x2C, 0xB1 } 
key_em_5_encoded = { 0x4E, 0x0, 0x2F, 0xEA, 0x27, 0x2F, 0xF7, 0xD5, 0xE6, 0x14, 0xCA, 0x5F, 0x21, 0xEE, 0x43, 0xA5 }
*/

uint8_t key1[8] = { 0x01, 0x14, 0xE6, 0x81, 0x0F, 0x00, 0x00, 0xF5 }; // черный без задней крышки
uint8_t key2[8] = { 0x01, 0xD8, 0xD3, 0x73, 0x01, 0x00, 0x00, 0xC3 }; // синий
uint8_t key3[8] = { 0x01, 0x3A, 0x6F, 0x14, 0x09, 0x00, 0x00, 0xD9 }; // черный с наклейкой
uint8_t key4[8] = { 0x01, 0x37, 0x47, 0x6E, 0x09, 0x00, 0x00, 0xE6 }; // черный 1
uint8_t key5[8] = { 0x01, 0x37, 0x69, 0xC9, 0x09, 0x00, 0x00, 0x93 }; // черный 2

uint8_t key_em_1[8] = { 0x01, 0xC6, 0xC1, 0xD2, 0x00, 0x4C, 0x00, 0x2F }; // мастер-ключ
uint8_t key_em_2[8] = { 0x01, 0xCB, 0xEC, 0xD2, 0x00, 0x4C, 0x00, 0x71 };
uint8_t key_em_3[8] = { 0x01, 0x0F, 0xDE, 0xD2, 0x00, 0x4C, 0x00, 0x35 };
uint8_t key_em_4[8] = { 0x01, 0xDD, 0xE0, 0xD2, 0x00, 0x4C, 0x00, 0xB9 };
uint8_t key_em_5[8] = { 0x01, 0xD9, 0xC1, 0xD2, 0x00, 0x4C, 0x00, 0x50 };

uint8_t *keys[5] = { key1, key2, key3, key4, key5 };

uint8_t KeyEncrypted[KEY_ENCRYPTED_SIZE];
uint8_t KeyRaw[KEY_RAW_SIZE]; 
uint16_t CurKeyIndex = 0;
