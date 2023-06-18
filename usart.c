#include "usart.h"

//----------------------------------------------------------------------------------------
// Обработчик прерывания USART по приему
//----------------------------------------------------------------------------------------
void URT_Rx_Callback(void)
{
	Bus_AddNewByte();
}

//----------------------------------------------------------------------------------------
// Функция записывает 1 байт в USART
//----------------------------------------------------------------------------------------
void URT_Write(uint8_t c)
{
	while(URT_IsTxReady() == TxBusy);
	URT_SetTXData(URT0, 1, c);
		;
}

//----------------------------------------------------------------------------------------
// Функция записывает слово (4 байта) в USART
//----------------------------------------------------------------------------------------
void URT_WriteWord(uint32_t w)
{
	while(URT_IsTxReady() == TxBusy);
	URT_SetTXData(URT0, 4, w);
		;
}

//----------------------------------------------------------------------------------------
// Функция записывает строку с 0-символом в конце в USART
//----------------------------------------------------------------------------------------
void URT_PrintString(const char *sz)
{
	while (*sz)
		URT_Write(*sz++);
	while(URT_IsTxEndTransmission() == TxBusy);
}

//----------------------------------------------------------------------------------------
// Функция записывает массив произвольной длины в USART
//----------------------------------------------------------------------------------------
void URT_Print(uint8_t *arr, uint8_t size)
{
	for(uint32_t i = 0; i < size; i++)
		URT_Write(*arr++);

	while(URT_IsTxEndTransmission() == TxBusy);
}

//----------------------------------------------------------------------------------------
// Проверка флага TXF (готовность передачи USART)
//----------------------------------------------------------------------------------------
URT_Status URT_IsTxReady()
{
	return URT0->STA.MBIT.TXF;
}

//----------------------------------------------------------------------------------------
// Проверка флага TCF (окончание передачи USART)
//----------------------------------------------------------------------------------------
URT_Status URT_IsTxEndTransmission()
{
	return URT0->STA.MBIT.TCF;
}

void USART_Config()
{
	#if URT_BAUDRATE > 115200UL
	#error Too high USART baudrate!
	#endif
	
    uint32_t TRXOverSamplingSampleNumber = 8;
    uint32_t Tmp;
	
    uint8_t BST_SOL, OVSMP, REM;    
    //==========================================
    //URT_BAUDRATE
    Tmp = CONF_CK_APB_FREQ / URT_BAUDRATE;
    if(Tmp < 8)
    {
        return;
    }
	//================TX and RX oversamplig value===================
	BST_SOL = 0;
	for(OVSMP = 8; OVSMP < 32; OVSMP++)
	{
		REM = Tmp % OVSMP;
		if(REM == 0)
		{
            if( (Tmp / OVSMP) < 4096)
            {
			    TRXOverSamplingSampleNumber = OVSMP;
			    break;
            }
		}
		else
		{
			if((OVSMP-REM) > BST_SOL || (OVSMP-REM) == BST_SOL)
			{
				BST_SOL = OVSMP - REM;
				TRXOverSamplingSampleNumber = OVSMP;
			}
		}
	}
    
	URTX->CLK.W = URTX->CLK.W & (~(URT_CLK_TX_CKS_mask_w| URT_CLK_RX_CKS_mask_w | URT_CLK_CK_SEL_mask_w));
	Tmp = Tmp / (TRXOverSamplingSampleNumber);
    if(Tmp > 4096)
    {
        return;
    }
    URTX->RLR.H[0] = (uint16_t)(Tmp - 1);
     
    
    TRXOverSamplingSampleNumber = TRXOverSamplingSampleNumber - 1;
    URTX->CR1.B[3] = (uint8_t)TRXOverSamplingSampleNumber;
    URTX->CR1.B[1] = (uint8_t)TRXOverSamplingSampleNumber;
    
    URTX->CLK.W = URTX->CLK.W | (URT_CLK_BR_MDS_combined_w | URT_CLK_BR_EN_enable_w);
    
    //===========================
    //1. Data is 8bit , Data order is LSB , no parity bit , stop bit is 1bit 
    //2. Data bit no inverse
    URTX->CR1.B[2] = (URT_CR1_TXDSIZE_8bit_b2 | URT_CR1_TXMSB_EN_disable_b2 | URT_CR1_TXPAR_EN_disable_b2 | URT_CR1_TXSTP_LEN_1bit_b2);
    URTX->CR1.B[0] = (URT_CR1_RXDSIZE_8bit_b0 | URT_CR1_RXMSB_EN_disable_b0 | URT_CR1_RXPAR_EN_disable_b0 | URT_CR1_RXSTP_LEN_1bit_b0);
    
    URTX->CR4.B[0] = ((URT_CR4_RDAT_INV_disable_b0 | URT_CR4_TDAT_INV_disable_b0) | (URT_CR4_RDAT_CLR_enable_b0 | URT_CR4_TDAT_CLR_enable_b0));
    
    //=============================
    //1. Set URT mode
    //2. Data line is 2 line
    //3. RX shadow buffer level is 1byte.
    //4. RX oversampling majority vote set. (3 sample bits method)
    URTX->CR0.W = (URTX->CR0.W & (~ (URT_CR0_MDS_mask_w | URT_CR0_DAT_LINE_mask_w | URT_CR0_RX_TH_mask_w | URT_CR0_OS_MDS_mask_w)));
    
	//============================
    // Enable RX interrupts
	
	URT_IT_Config(URTX, URT_IT_RX, ENABLE); // включаем прерывание UART0 по приему
    URT_ITEA_Cmd(URTX, ENABLE); // включаем общие прерывания UART0
	NVIC_EnableIRQ(URT0_IRQn);  // включаем контроллер прерываний
	NVIC_SetPriority(URT0_IRQn, 0);
	 //============================
    // Enable RX & TX
	
    URTX->CR2.W = URTX->CR2.W | (URT_CR2_TX_EN_mask_w | URT_CR2_RX_EN_mask_w);                                                                                          
}

//----------------------------------------------------------------------------------------
// Обработчик прерываний
//----------------------------------------------------------------------------------------
void URT0_IRQHandler(void)
{

	URT_Rx_Callback();
	URT_ClearITFlag(URT0, URT_IT_RX);
}
