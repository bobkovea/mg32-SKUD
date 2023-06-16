#ifndef USART_H
#define USART_H
#include "MG32x02z_URT_DRV.h"
#include "MG32x02z_CSC_Init.h"
#include "bus.h"
#include "device_config.h"

#define URTX URT0

typedef enum {
	TxBusy = 0,
	TxReady = 1
} URT_Status;


void URT0_IRQHandler(void);
void URT_Rx_Callback(void);
void URT_Tx_Callback(void);

void URT_Write(uint8_t c);
void URT_WriteWord(uint32_t w);
void URT_PrintString(const char *str);
void URT_Print(uint8_t *arr, uint8_t size);
void USART_Config();
URT_Status URT_IsTxReady();
URT_Status URT_IsTxEndTransmission();
#endif // USART_H