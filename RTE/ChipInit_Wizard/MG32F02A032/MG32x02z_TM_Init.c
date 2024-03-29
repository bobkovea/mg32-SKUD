/**
 *******************************************************************************
 *
 * @file        MG32x02z_TM_Init.c
 *
 * @brief       The TM initial code C file
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2020/08/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 *******************************************************************************
 * @par         Disclaimer
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
#include "MG32x02z_TM_Init.h"


/**
 *******************************************************************************
 * @brief  	    Initialized TM module.
 * @param[in]   None
 * @return      None
 *******************************************************************************
 */
void TM_Init (void)
{

    /* TM00 initial wizard */
    #if CONF_TM00_ENABLE_OPTION!=0
        TM00->CLK.W = CONF_TM00_CLK;
        TM00->CKO.W = CONF_TM00_CKO;
        TM00->ARR.W = CONF_TM00_ARR;
        TM00->PSARR.W = CONF_TM00_PSARR;
        TM00->TRG.W = (CONF_TM00_TRG | TM_TRG_RST_SW_enable_w | TM_TRG_RST2_SW_enable_w);    // reset TM00
        TM00->CR0.W = (CONF_TM00_CR0 | TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w);
        TM00->TRG.W = CONF_TM00_TRG;
    #endif
    
    /* TM01 initial wizard */
    #if CONF_TM01_ENABLE_OPTION!=0
        TM01->CLK.W = CONF_TM01_CLK;
        TM01->CKO.W = CONF_TM01_CKO;
        TM01->ARR.W = CONF_TM01_ARR;
        TM01->PSARR.W = CONF_TM01_PSARR;
        TM01->TRG.W = (CONF_TM01_TRG | TM_TRG_RST_SW_enable_w | TM_TRG_RST2_SW_enable_w);    // reset TM01
        TM01->CR0.W = (CONF_TM01_CR0 | TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w);
        TM01->TRG.W = CONF_TM01_TRG;
    #endif
    
    /* TM10 initial wizard */
    #if CONF_TM10_ENABLE_OPTION!=0
        TM10->CLK.W = CONF_TM10_CLK;
        TM10->CKO.W = CONF_TM10_CKO;
        TM10->ARR.W = CONF_TM10_ARR;
        TM10->PSARR.W = CONF_TM10_PSARR;
        TM10->TRG.W = (CONF_TM10_TRG | TM_TRG_RST_SW_enable_w | TM_TRG_RST2_SW_enable_w);    // reset TM10
        TM10->CR0.W = (CONF_TM10_CR0 | TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w);
        TM10->TRG.W = CONF_TM10_TRG;
    #endif
    
    /* TM16 initial wizard */
    #if CONF_TM16_ENABLE_OPTION!=0
        TM16->CLK.W = CONF_TM16_CLK;
        TM16->CKO.W = CONF_TM16_CKO;
        TM16->ARR.W = CONF_TM16_ARR;
        TM16->PSARR.W = CONF_TM16_PSARR;
        TM16->TRG.W = (CONF_TM16_TRG | TM_TRG_RST_SW_enable_w | TM_TRG_RST2_SW_enable_w);    // reset TM16
        TM16->CR0.W = (CONF_TM16_CR0 | TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w);
        TM16->TRG.W = CONF_TM16_TRG;
    #endif
    
    /* TM36 initial wizard */
    #if CONF_TM36_ENABLE_OPTION!=0
        TM36->CLK.W = CONF_TM36_CLK;
        TM36->CKO.W = CONF_TM36_CKO;
        TM36->ARR.W = CONF_TM36_ARR;
        TM36->PSARR.W = CONF_TM36_PSARR;
        TM36->TRG.W = (CONF_TM36_TRG | TM_TRG_RST_SW_enable_w | TM_TRG_RST2_SW_enable_w);    // reset TM36
        TM36->CCMDS.W = CONF_TM36_CCMDS;
        TM36->ICCR.W = CONF_TM36_ICCR;
        TM36->OSCR.W = (CONF_TM36_OSCR | 0x0000F0F0);        // unlock 0CxH OCx initial state       
        TM36->OCCR0.W = CONF_TM36_OCCR0;
        TM36->OCCR1.W = CONF_TM36_OCCR1;
        TM36->PWM.W = CONF_TM36_PWM;
        TM36->BS.W = CONF_TM36_BS;
        TM36->CC0A.W = TM36->CC0B.W = CONF_TM36_CC0A;
        TM36->CC1A.W = TM36->CC1B.W = CONF_TM36_CC1A;
        TM36->CC2A.W = TM36->CC2B.W = CONF_TM36_CC2A;
        TM36->CC3A.W = TM36->CC3B.W = CONF_TM36_CC3A;
        TM36->CR0.W = (CONF_TM36_CR0 | TM_CR0_EN_enable_w | TM_CR0_EN2_enable_w);
        TM36->TRG.W = CONF_TM36_TRG;
    #endif
}






