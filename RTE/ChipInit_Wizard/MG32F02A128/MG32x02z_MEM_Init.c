
/**
 ******************************************************************************
 *
 * @file        MG32x02z_MEM_Init.c
 * @brief       The MEM Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2017/07/07
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
#include "MG32x02z_MEM_Init.h"


void MEM_Init(void)
{
    //UnProtect
    MEM->KEY.H[0] = 0xA217;

    MEM->CR0.B[0] |= MEM_CR0_EN_mask_b0;

    MEM->IAPSZ.W = (MEM_Config0_IAPSZ_Lock << 8);

    MEM->CR0.W &= MEM_Config0_HardFault | MEM_CR0_FWAIT_mask_w | ((!MEM_Config0_LSFAPD) << 20) | ((!MEM_Config0_IAPSZ_Lock) << 21) | ((!MEM_Config0_HardFault) << 1);

  #if defined(MG32_3RD) || defined(MG32_4TH)
    MEM->CR0.W |= (MEM_Config0_CR0 | MEM_CR0_FWAIT_one_w | MEM_CR0_EN_mask_w | ((!MEM_Config0_LSFAPD) << 20) | ((!MEM_Config0_IAPSZ_Lock) << 21) | ((!MEM_Config0_HardFault) << 1)) & (~MEM_CR0_HSP_EN_mask_w);
  #else
    MEM->CR0.W |= MEM_Config0_CR0 | MEM_CR0_EN_mask_w | ((!MEM_Config0_LSFAPD) << 20) | ((!MEM_Config0_IAPSZ_Lock) << 21) | ((!MEM_Config0_HardFault) << 1);
  #endif

    MEM->INT.W = MEM_Config0_INT;

    //Protect
    MEM->KEY.H[0] = 0;
}

//#endif


