#ifndef USART_DRV_H
#define USART_DRV_H
#include "MG32x02z_DRV.h"

// настроить пины RX TX визардом!!

typedef enum {
	TxBusy = 0,
	TxReady = 1
} URT_Status;

void URT_Rx_Callback(void);
void URT_Tx_Callback(void);
void URT0_Init(void);


void URT_Write(uint8_t c);
void URT_WriteWord(uint32_t w);
void URT_Print(const char* str);

URT_Status URT_IsTxReady();
URT_Status URT_IsTxEndTransmission();
#endif // USART_DRV_H