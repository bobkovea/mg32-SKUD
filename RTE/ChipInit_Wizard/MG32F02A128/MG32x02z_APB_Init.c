/**
 *******************************************************************************
 *
 * @file        MG32x02z_APB_Init.c
 *
 * @brief       The APX APB initial code C file 
 *              Apply device : MG32F02A128/U128/A064/U064
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2021/09/08
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


/* Includes ------------------------------------------------------------------*/
#include "MG32x02z.h"
#include "MG32x02z_APB.h"
#include "MG32x02z_APB_Init.h"

/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/


/**
 *******************************************************************************
 * @brief  	    Initialized APB module.
 * @param[in]   None
 * @return      None
 *******************************************************************************
 */
void APB_Init(void)
{

    /* APB CR0 (IR) initial wizard */
    #if (CONF_APB_CR0 != 0)
        APB->CR0.W  = APB->CR0.W | (CONF_APB_CR0 & 0x00FF0000);
    #endif
    
    /* APB CR2 (ITR6/7) initial wizard */
    #if (CONF_APB_CR2 != 0)
        APB->CR2.W  = CONF_APB_CR2;
    #endif
    
    /* APB OBM0 initial wizard */
    #if ((CONF_APB_OBM00 != 0x00000020) || (CONF_APB_OBM01 != 0x00000000))
        APB->OBM00.W  = CONF_APB_OBM00;
        APB->OBM01.W  = CONF_APB_OBM01;
    #endif

    /* APB OBM1 initial wizard */
    #if ((CONF_APB_OBM10 != 0x00000020) || (CONF_APB_OBM11 != 0x00000000))
        APB->OBM10.W  = CONF_APB_OBM10;
        APB->OBM11.W  = CONF_APB_OBM11;
    #endif

    /* APB NCO initial wizard */
    #if ((CONF_APB_NCO00 & 0x01000000 )!= 0x00000000)
        APB->NCO01.W  = CONF_APB_NCO01;
        APB->NCO00.W  = (CONF_APB_NCO00 & 0xFFF00000) | (CONF_APB_NCO01 & 0x000FFFFF);
    #endif

}


