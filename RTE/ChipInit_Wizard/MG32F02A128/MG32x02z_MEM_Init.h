
/**
 ******************************************************************************
 *
 * @file        MG32x02z_MEM_Init.h
 *
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



#ifndef __MG32x02z_MEM_INIT_H
#define __MG32x02z_MEM_INIT_H
#define __MG32x02z_MEM_INIT_H_VER                          0.01     /*!< File Version */

#ifdef __cplusplus
 extern "C" {
#endif

#include "MG32x02z_DRV.h"
#include "MG32x02z_MEM.h"

//*** <<< Use Configuration Wizard in Context Menu >>> ***
//  <O0> FCLK Frequnce(unit:HZ).<1-50000000>
//  <o4.8..15> IAP memory size(unit:KByte).
//    <i> Default value is loaded from CFG OR after Warm reset.
//  <q5> Lock IAP memory size MEM_IAP_SIZE register access.
//    <i>  Default value is loaded from CFG OR only after Cold reset.
//  <q2.2> CPU hold control under flash memory access
//    <i> Only using on Boot from SRAM Mode.
//  <q7> Disable Flash data access error HardFault.
//    <i> Default: 0 Enable
//  <e1.0> Memory controller interrupt all.
//    <q1.1> Flash end of processing interrupt.
//    <q1.4> code execution illegal address error detection interrupt.
//    <q1.5> Flash write protect error detection interrupt.
//    <q1.6> Flash read protect error detection interrupt.
//  </e>
//  <q1.20> Code execution illegal address detection reset.
//  <q1.21> Flash write protect error detection reset.
//  <q1.22> Flash read protect error detection reset.
//*** <<< end of configuration section >>> ***
#define     MEM_Config0_FCLK         24000000
#define     MEM_Config0_INT          0x00000000
#define     MEM_Config0_CR0          0x00000002
#define     MEM_Config0_CR1          0x00000000
#define     MEM_Config0_IAPSZ        0x00001000
#define     MEM_Config0_LSFAPD       0
#define     MEM_Config0_IAPSZ_Lock   0
#define     MEM_Config0_HardFault    0



void MEM_Init(void);



#ifdef __cplusplus
}
#endif

#endif

