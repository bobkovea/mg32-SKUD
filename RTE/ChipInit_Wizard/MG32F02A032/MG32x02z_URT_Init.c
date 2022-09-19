



/**
 ******************************************************************************
 *
 * @file        MG32x02z_URT_Init.c
 * @brief       The URT Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.04
 * @date        2021/09/13
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *   
 ******************************************************************************* 
 * @par Disclaimer
 * The Demo software is provided "AS IS" without any warranty, either
 * expressed or implied, including, but not limited to, the implied warranties
 * of merchantability and fitness for a particular purpose. The author will
 * not be liable for any special, incidental, consequential or indirect
 * damages due to loss of data or any other reason.
 * These statements agree with the world wide and local dictated laws about
 * authorship and violence against these laws.
 *******************************************************************************
 *******************************************************************************
 */


#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_URT_Init.h"


/**
 *******************************************************************************
 * @brief	    URTx N-8-1 mode inital.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   BaudRate: The URTX baudrate value.
 * @return      URTx inital is whether pass or not.
 * @exception   No
 * @note        The URT initial is N-8-1.
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */

uint8_t URT_Config(URT_Struct* URTX , uint32_t URT_Freq, uint32_t BaudRate)
{
    uint32_t TRXOverSamplingSampleNumber = 8;
    uint32_t Tmp;
	
    uint8_t BST_SOL,OVSMP,REM;    
    //==========================================
    //Baudrate
    Tmp = URT_Freq / BaudRate;
    if(Tmp<8)
    {
        return(URT_INIT_WIZARD_FAILURE);
    }
	//================TX and RX oversamplig value===================
	BST_SOL = 0;
	for(OVSMP=8;OVSMP<32;OVSMP++)
	{
		REM = Tmp % OVSMP;
		if(REM==0)
		{
            if( (Tmp / OVSMP)<4096)
            {
			    TRXOverSamplingSampleNumber = OVSMP;
			    break;
            }
		}
		else
		{
			if((OVSMP-REM)>BST_SOL || (OVSMP-REM)==BST_SOL)
			{
				BST_SOL = OVSMP - REM;
				TRXOverSamplingSampleNumber = OVSMP;
			}
		}
	}
    
	URTX->CLK.W = URTX->CLK.W & (~(URT_CLK_TX_CKS_mask_w| URT_CLK_RX_CKS_mask_w | URT_CLK_CK_SEL_mask_w));
	Tmp = Tmp / (TRXOverSamplingSampleNumber);
    if(Tmp>4096)
    {
        return(URT_INIT_WIZARD_FAILURE);
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
    //1. Enable RX & TX
    //2. Enable URT 
    URTX->CR2.W = URTX->CR2.W | (URT_CR2_TX_EN_mask_w | URT_CR2_RX_EN_mask_w);                                   
    URTX->CR0.W = URTX->CR0.W | URT_CR0_EN_mask_w;                                                              
    
    return(URT_INIT_WIZARD_SUCCESS);
}

/**
 *******************************************************************************
 * @brief	    URTx N-8-1 mode inital.
 * @details     
 * @param[in]   URTX:
 *  @arg\b      URT0: URT0 relationship control.
 *  @arg\b      URT1: URT1 relationship control.
 *  @arg\b      URT2: URT2 relationship control.
 *  @arg\b      URT3: URT3 relationship control.
 * @param[in]   BaudRate: The URTX baudrate value.
 * @return      URTx inital is whether pass or not.
 * @exception   No
 * @note        The URT initial is N-8-1.
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
#if CONF_URT_INITBR_H_EN == 1

uint8_t URT_Config2(URT_Struct* URTX , uint32_t URT_BDMODE_SET , uint32_t URT_CR1_SET , uint32_t URT_RLR_SET) 
{
    //==========================================
    //Baud-Rate Generator Setting.
    
    URTX->RLR.H[0] = URT_RLR_SET;

    URTX->CLK.W = ( URT_CLK_CK_SEL_proc_w | URT_CLK_RX_CKS_internal_w | URT_CLK_TX_CKS_internal_w | URT_CLK_BR_EN_enable_w | URT_BDMODE_SET);

    
    //===========================
    //1. Set RX/TX oversampling.
    //2. Data is 8bit , Data order is LSB , no parity bit , stop bit is 1bit 
    //3. Data bit no inverse
    URTX->CR1.W = (URT_CR1_RXDSIZE_8bit_w | URT_CR1_RXMSB_EN_disable_w | URT_CR1_RXPAR_EN_disable_w | URT_CR1_RXSTP_LEN_1bit_w |
                   URT_CR1_TXDSIZE_8bit_w | URT_CR1_TXMSB_EN_disable_w | URT_CR1_TXPAR_EN_disable_w | URT_CR1_TXSTP_LEN_1bit_w |
                   URT_CR1_SET);                   
    

    URTX->CR4.B[0] = ((URT_CR4_RDAT_INV_disable_b0 | URT_CR4_TDAT_INV_disable_b0) | (URT_CR4_RDAT_CLR_enable_b0 | URT_CR4_TDAT_CLR_enable_b0));
    
    //=============================
    //1. Set URT mode
    //2. Data line is 2 line
    //3. RX shadow buffer level is 1byte.
    //4. RX oversampling majority vote set. (3 sample bits method)
    URTX->CR0.W = (URTX->CR0.W & (~ (URT_CR0_MDS_mask_w | URT_CR0_DAT_LINE_mask_w | URT_CR0_RX_TH_mask_w | URT_CR0_OS_MDS_mask_w)));
    
    
    //============================
    //1. Enable RX & TX
    //2. Enable URT 
    URTX->CR2.W = URTX->CR2.W | (URT_CR2_TX_EN_mask_w | URT_CR2_RX_EN_mask_w);                                   
    URTX->CR0.W = URTX->CR0.W | URT_CR0_EN_mask_w;                                                              
    

    return(URT_INIT_WIZARD_SUCCESS);
}


#endif

/**
 *******************************************************************************
 * @brief	    Control URTX N-8-1 mode inital.
 * @details     
 * @return      URTx inital is whether pass or not.
 * @exception   No
 * @note        The URT initial is N-8-1.
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
uint8_t URT_Init(void)
{
    #if CONF_URT_INITBR_H_EN == 1
    
        #if CONF_URT0_INITBR_EN == 1
            URT_Config2(URT0 , CONF_URT0_INITBR_BRM, CONF_URT0_INITBR_CR1, CONF_URT0_INITBR_RLR);     // Enable URT0 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT1_INITBR_EN == 1
            URT_Config2(URT1 , CONF_URT1_INITBR_BRM, CONF_URT1_INITBR_CR1, CONF_URT1_INITBR_RLR);     // Enable URT1 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT2_INITBR_EN == 1
            URT_Config2(URT2 , CONF_URT2_INITBR_BRM, CONF_URT2_INITBR_CR1, CONF_URT2_INITBR_RLR);     // Enable URT2 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT3_INITBR_EN == 1
            URT_Config2(URT3 , CONF_URT3_INITBR_BRM, CONF_URT3_INITBR_CR1, CONF_URT3_INITBR_RLR);     // Enable URT3 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT4_INITBR_EN == 1
            URT_Config2(URT4 , CONF_URT4_INITBR_BRM, CONF_URT4_INITBR_CR1, CONF_URT4_INITBR_RLR);     // Enable URT4 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT5_INITBR_EN == 1
            URT_Config2(URT5 , CONF_URT5_INITBR_BRM, CONF_URT5_INITBR_CR1, CONF_URT5_INITBR_RLR);     // Enable URT5 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT6_INITBR_EN == 1
            URT_Config2(URT6 , CONF_URT6_INITBR_BRM, CONF_URT6_INITBR_CR1, CONF_URT6_INITBR_RLR);     // Enable URT6 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        #if CONF_URT7_INITBR_EN == 1
            URT_Config2(URT7 , CONF_URT7_INITBR_BRM, CONF_URT7_INITBR_CR1, CONF_URT7_INITBR_RLR);     // Enable URT7 and baudrate calculation by MG32x02z_URT_InitBR.h
        #endif
        return(URT_INIT_WIZARD_SUCCESS);
    #else
        uint8_t Result = URT_INIT_WIZARD_SUCCESS;
        
        #if CONF_URT0_INIT_EN == 1
            if(URT_Config(URT0,CONF_URT0_Freq,CONF_URT0_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT0 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT1_INIT_EN == 1
            if(URT_Config(URT1,CONF_URT1_Freq,CONF_URT1_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT1 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT2_INIT_EN == 1
            if(URT_Config(URT2,CONF_URT2_Freq,CONF_URT2_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT2 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT3_INIT_EN == 1
            if(URT_Config(URT3,CONF_URT3_Freq,CONF_URT3_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT3 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT4_INIT_EN == 1
            if(URT_Config(URT4,CONF_URT4_Freq,CONF_URT4_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT4 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT5_INIT_EN == 1
            if(URT_Config(URT5,CONF_URT5_Freq,CONF_URT5_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT5 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT6_INIT_EN == 1
            if(URT_Config(URT6,CONF_URT6_Freq,CONF_URT6_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT6 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        #if CONF_URT7_INIT_EN == 1
            if(URT_Config(URT7,CONF_URT7_Freq,CONF_URT7_INIT_BD)!=URT_INIT_WIZARD_FAILURE)            // Enable URT7 and baudrate calculation middeware select ( In MG32x02z_URT_Init.h)
            {
                Result = URT_INIT_WIZARD_FAILURE;
            }
        #endif
        return(Result);
    #endif
}


//#endif






