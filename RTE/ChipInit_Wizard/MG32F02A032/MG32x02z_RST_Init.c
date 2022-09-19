/**
 *******************************************************************************
 *
 * @file        MG32x02z_RST_Init.c
 *
 * @brief       The RST Init C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.10
 * @date        2018/01/31
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2018 Megawin Technology Co., Ltd.
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

#include "MG32x02z_RST_Init.h"



/**
 *******************************************************************************
 * @brief  	    initialized RST module.
 * @details  
 * @return	    None	
 * @note
 * @par         Example
 * @code
    RST_Init ();
 * @endcode
 *******************************************************************************
 */
void RST_Init (void)
{
    RST->KEY.MBIT.KEY = 0xA217;         // Unprotest RST module register
    RST->CR0.W = CONF_RST_InitConfig[3];
    RST->CE.W = CONF_RST_InitConfig[4];
    RST->WE.W = CONF_RST_InitConfig[5];
    RST->AHB.W = CONF_RST_InitConfig[6];
    RST->APB0.W = CONF_RST_InitConfig[7];
    RST->APB1.W = CONF_RST_InitConfig[8];
    RST->KEY.MBIT.KEY = 0x0000;         // Protest RST module register
}
