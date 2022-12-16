#ifndef USART_H
#define USART_H
#include "MG32x02z_URT_DRV.h"
#include "prsm3.h"
#include "device_config.h"

#define URTX URT0

typedef enum {
	TxBusy = 0,
	TxReady = 1
} URT_Status;

void URT0_IRQ(void);
void URT0_IRQHandler(void);
void URT_Rx_Callback(void);
void URT_Tx_Callback(void);

void URT_Write(uint8_t c);
void URT_WriteWord(uint32_t w);
void URT_Print(const char* str);
void USART_Config();

URT_Status URT_IsTxReady();
URT_Status URT_IsTxEndTransmission();
#endif // USART_H