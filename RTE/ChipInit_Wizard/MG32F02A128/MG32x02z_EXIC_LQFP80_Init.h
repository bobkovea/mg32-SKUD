/**
 ******************************************************************************
 *
 * @file        MG32x02z_EXIC_LQFP80_Init.h
 *
 * @brief       This file is used to configure EXIC setting.
 *              Device : MG32F02A128
 *              Package: LQFP80
 *
 * @par         Project
 *              MG32x02z
 * @version     V0.32
 * @date        2022/02/16 17:30 (H File Generated Date)
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2020 Megawin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************
 * @par         Disclaimer
 *      The Demo software is provided "AS IS"  without any warranty, either
 *      expressed or implied, including, but not limited to, the implied warranties
 *      of merchantability and fitness for a particular purpose.  The author will
 *      not be liable for any special, incidental, consequential or indirect
 *      damages due to loss of data or any other reason.
 *      These statements agree with the world wide and local dictated laws about
 *      authorship and violence against these laws.
 ******************************************************************************
 @if HIDE
 *Modify History:
 *>>
 *--
 *--
 *>>
 *>>
 *
 @endif
 ******************************************************************************
 */

#ifndef _MG32x02z_EXIC_Init_H
#define _MG32x02z_EXIC_Init_H

#include "MG32x02z_EXIC.h"
#include "MG32x02z__ExtraStruct.h"

// <<< Use Configuration Wizard in Context Menu >>>


/**
 ******************************************************************************
 *
 * @brief       EXIC Initial Configure - MG32F02A128 (LQFP80-Package)
 *
 ******************************************************************************
 */
//<h> EXIC Initial Configure - MG32F02A128 (LQFP80-Package)

//
//=============================  PA EXIC Setting  ==============================
//
//<e0> Enable EXIC PA initial
//<i> Port PA external interrupt configuration enable.
    //<h> AND (KBI)
    //<i> Port PA AND mask setting for External KBI input.
        //<o1.16..31>AND Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PA AND mask bits. Each bit is used to disable(mask) or enable the related PAx input line.
        //<q5> AND unmatch enable
        //<i> External interrupt PA AND path signal inverse enable.
    //</h>
    //<h> OR (Interrupt)
    //<i> Port PA OR mask setting for External interrupt input.
        //<o1.0..15> OR  Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PA OR mask bits. Each bit is used to disable(mask) or enable the related PAx input line.
    //</h>
    //<h> Trigger mode
    //<i> Port PA pin edge/level event trigger setting.
        //<e2.1>  PA0
        //<i> External interrupt PA0 pin edge/level event trigger enable.
            //<o3.0..1> PIN0 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.3>  PA1
        //<i> External interrupt PA1 pin edge/level event trigger enable.
            //<o3.2..3> PIN1 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.5>  PA2
        //<i> External interrupt PA2 pin edge/level event trigger enable.
            //<o3.4..5> PIN2 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.7>  PA3
        //<i> External interrupt PA3 pin edge/level event trigger enable.
            //<o3.6..7> PIN3 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.9>  PA4
        //<i> External interrupt PA4 pin edge/level event trigger enable.
            //<o3.8..9> PIN4 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.11>  PA5
        //<i> External interrupt PA5 pin edge/level event trigger enable.
            //<o3.10..11> PIN5 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.13>  PA6
        //<i> External interrupt PA6 pin edge/level event trigger enable.
            //<o3.12..13> PIN6 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.15>  PA7
        //<i> External interrupt PA7 pin edge/level event trigger enable.
            //<o3.14..15> PIN7 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.17>  PA8
        //<i> External interrupt PA8 pin edge/level event trigger enable.
            //<o3.16..17> PIN8 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.19>  PA9
        //<i> External interrupt PA9 pin edge/level event trigger enable.
            //<o3.18..19> PIN9 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.21>  PA10
        //<i> External interrupt PA10 pin edge/level event trigger enable.
            //<o3.20..21> PIN10 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.23>  PA11
        //<i> External interrupt PA11 pin edge/level event trigger enable.
            //<o3.22..23> PIN11 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.25>  PA12
        //<i> External interrupt PA12 pin edge/level event trigger enable.
            //<o3.24..25> PIN12 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.27>  PA13
        //<i> External interrupt PA13 pin edge/level event trigger enable.
            //<o3.26..27> PIN13 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.29>  PA14
        //<i> External interrupt PA14 pin edge/level event trigger enable.
            //<o3.28..29> PIN14 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.31>  PA15
        //<i> External interrupt PA15 pin edge/level event trigger enable.
            //<o3.30..31> PIN15 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
    //</h>
    //<q4> Interrupt enable
    //<i> Port PA interrupt enable.
//</e>
#define CONF_ExicPAInit_EN           0
#define CONF_ExicPAInit_AndOrMask    0x00000000
#define CONF_ExicPAInit_Mask         0x00000000  
#define CONF_ExicPAInit_Mode         0x55555555
#define CONF_ExicPAInit_INT          0
#define CONF_ExicPAInit_AINV         0


//
//=============================  PB EXIC Setting  ==============================
//
//<e0> Enable EXIC PB initial
//<i> Port PB external interrupt configuration enable.
    //<h> AND (KBI)
    //<i> Port PB AND mask setting for External KBI input.
        //<o1.16..31>AND Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PB AND mask bits. Each bit is used to disable(mask) or enable the related PBx input line.
        //<q5> AND unmatch enable
        //<i> External interrupt PB AND path signal inverse enable.
    //</h>
    //<h> OR (Interrupt)
    //<i> Port PB OR mask setting for External interrupt input.
        //<o1.0..15> OR  Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PB OR mask bits. Each bit is used to disable(mask) or enable the related PBx input line.
    //</h>
    //<h> Trigger mode
    //<i> Port PB pin edge/level event trigger setting.
        //<e2.1>  PB0
        //<i> External interrupt PB0 pin edge/level event trigger enable.
            //<o3.0..1> PIN0 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.3>  PB1
        //<i> External interrupt PB1 pin edge/level event trigger enable.
            //<o3.2..3> PIN1 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.5>  PB2
        //<i> External interrupt PB2 pin edge/level event trigger enable.
            //<o3.4..5> PIN2 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.7>  PB3
        //<i> External interrupt PB3 pin edge/level event trigger enable.
            //<o3.6..7> PIN3 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.9>  PB4
        //<i> External interrupt PB4 pin edge/level event trigger enable.
            //<o3.8..9> PIN4 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.11>  PB5
        //<i> External interrupt PB5 pin edge/level event trigger enable.
            //<o3.10..11> PIN5 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.13>  PB6
        //<i> External interrupt PB6 pin edge/level event trigger enable.
            //<o3.12..13> PIN6 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.15>  PB7
        //<i> External interrupt PB7 pin edge/level event trigger enable.
            //<o3.14..15> PIN7 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.17>  PB8
        //<i> External interrupt PB8 pin edge/level event trigger enable.
            //<o3.16..17> PIN8 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.19>  PB9
        //<i> External interrupt PB9 pin edge/level event trigger enable.
            //<o3.18..19> PIN9 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.21>  PB10
        //<i> External interrupt PB10 pin edge/level event trigger enable.
            //<o3.20..21> PIN10 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.23>  PB11
        //<i> External interrupt PB11 pin edge/level event trigger enable.
            //<o3.22..23> PIN11 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.25>  PB12
        //<i> External interrupt PB12 pin edge/level event trigger enable.
            //<o3.24..25> PIN12 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.27>  PB13
        //<i> External interrupt PB13 pin edge/level event trigger enable.
            //<o3.26..27> PIN13 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.29>  PB14
        //<i> External interrupt PB14 pin edge/level event trigger enable.
            //<o3.28..29> PIN14 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.31>  PB15
        //<i> External interrupt PB15 pin edge/level event trigger enable.
            //<o3.30..31> PIN15 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
    //</h>
    //<q4> Interrupt enable
    //<i> Port PB interrupt enable.
//</e>
#define CONF_ExicPBInit_EN           0
#define CONF_ExicPBInit_AndOrMask    0x00000000
#define CONF_ExicPBInit_Mask         0x00000000  
#define CONF_ExicPBInit_Mode         0x55555555
#define CONF_ExicPBInit_INT          0
#define CONF_ExicPBInit_AINV         0


//
//=============================  PC EXIC Setting  ==============================
//
//<e0> Enable EXIC PC initial
//<i> Port PC external interrupt configuration enable.
    //<h> AND (KBI)
    //<i> Port PC AND mask setting for External KBI input.
        //<o1.16..31>AND Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PC AND mask bits. Each bit is used to disable(mask) or enable the related PCx input line.
        //<q5> AND unmatch enable
        //<i> External interrupt PC AND path signal inverse enable.
    //</h>
    //<h> OR (Interrupt)
    //<i> Port PC OR mask setting for External interrupt input.
        //<o1.0..15> OR  Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PC OR mask bits. Each bit is used to disable(mask) or enable the related PCx input line.
    //</h>
    //<h> Trigger mode
    //<i> Port PC pin edge/level event trigger setting.
        //<e2.1>  PC0
        //<i> External interrupt PC0 pin edge/level event trigger enable.
            //<o3.0..1> PIN0 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.3>  PC1
        //<i> External interrupt PC1 pin edge/level event trigger enable.
            //<o3.2..3> PIN1 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.5>  PC2
        //<i> External interrupt PC2 pin edge/level event trigger enable.
            //<o3.4..5> PIN2 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.7>  PC3
        //<i> External interrupt PC3 pin edge/level event trigger enable.
            //<o3.6..7> PIN3 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.9>  PC4
        //<i> External interrupt PC4 pin edge/level event trigger enable.
            //<o3.8..9> PIN4 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.11>  PC5
        //<i> External interrupt PC5 pin edge/level event trigger enable.
            //<o3.10..11> PIN5 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.13>  PC6
        //<i> External interrupt PC6 pin edge/level event trigger enable.
            //<o3.12..13> PIN6 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.15>  PC7
        //<i> External interrupt PC7 pin edge/level event trigger enable.
            //<o3.14..15> PIN7 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.17>  PC8
        //<i> External interrupt PC8 pin edge/level event trigger enable.
            //<o3.16..17> PIN8 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.19>  PC9
        //<i> External interrupt PC9 pin edge/level event trigger enable.
            //<o3.18..19> PIN9 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.21>  PC10
        //<i> External interrupt PC10 pin edge/level event trigger enable.
            //<o3.20..21> PIN10 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.23>  PC11
        //<i> External interrupt PC11 pin edge/level event trigger enable.
            //<o3.22..23> PIN11 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.25>  PC12
        //<i> External interrupt PC12 pin edge/level event trigger enable.
            //<o3.24..25> PIN12 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.27>  PC13
        //<i> External interrupt PC13 pin edge/level event trigger enable.
            //<o3.26..27> PIN13 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.29>  PC14
        //<i> External interrupt PC14 pin edge/level event trigger enable.
            //<o3.28..29> PIN14 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
    //</h>
    //<q4> Interrupt enable
    //<i> Port PC interrupt enable.
//</e>
#define CONF_ExicPCInit_EN           0
#define CONF_ExicPCInit_AndOrMask    0x00000000
#define CONF_ExicPCInit_Mask         0x00000000  
#define CONF_ExicPCInit_Mode         0x55555555
#define CONF_ExicPCInit_INT          0
#define CONF_ExicPCInit_AINV         0


//
//=============================  PD EXIC Setting  ==============================
//
//<e0> Enable EXIC PD initial
//<i> Port PD external interrupt configuration enable.
    //<h> AND (KBI)
    //<i> Port PD AND mask setting for External KBI input.
        //<o1.16..31>AND Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PD AND mask bits. Each bit is used to disable(mask) or enable the related PDx input line.
        //<q5> AND unmatch enable
        //<i> External interrupt PD AND path signal inverse enable.
    //</h>
    //<h> OR (Interrupt)
    //<i> Port PD OR mask setting for External interrupt input.
        //<o1.0..15> OR  Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PD OR mask bits. Each bit is used to disable(mask) or enable the related PDx input line.
    //</h>
    //<h> Trigger mode
    //<i> Port PD pin edge/level event trigger setting.
        //<e2.1>  PD0
        //<i> External interrupt PD0 pin edge/level event trigger enable.
            //<o3.0..1> PIN0 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.3>  PD1
        //<i> External interrupt PD1 pin edge/level event trigger enable.
            //<o3.2..3> PIN1 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.5>  PD2
        //<i> External interrupt PD2 pin edge/level event trigger enable.
            //<o3.4..5> PIN2 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.7>  PD3
        //<i> External interrupt PD3 pin edge/level event trigger enable.
            //<o3.6..7> PIN3 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.9>  PD4
        //<i> External interrupt PD4 pin edge/level event trigger enable.
            //<o3.8..9> PIN4 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.11>  PD5
        //<i> External interrupt PD5 pin edge/level event trigger enable.
            //<o3.10..11> PIN5 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.13>  PD6
        //<i> External interrupt PD6 pin edge/level event trigger enable.
            //<o3.12..13> PIN6 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.15>  PD7
        //<i> External interrupt PD7 pin edge/level event trigger enable.
            //<o3.14..15> PIN7 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.17>  PD8
        //<i> External interrupt PD8 pin edge/level event trigger enable.
            //<o3.16..17> PIN8 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.19>  PD9
        //<i> External interrupt PD9 pin edge/level event trigger enable.
            //<o3.18..19> PIN9 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.21>  PD10
        //<i> External interrupt PD10 pin edge/level event trigger enable.
            //<o3.20..21> PIN10 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.23>  PD11
        //<i> External interrupt PD11 pin edge/level event trigger enable.
            //<o3.22..23> PIN11 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.25>  PD12
        //<i> External interrupt PD12 pin edge/level event trigger enable.
            //<o3.24..25> PIN12 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.27>  PD13
        //<i> External interrupt PD13 pin edge/level event trigger enable.
            //<o3.26..27> PIN13 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.29>  PD14
        //<i> External interrupt PD14 pin edge/level event trigger enable.
            //<o3.28..29> PIN14 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.31>  PD15
        //<i> External interrupt PD15 pin edge/level event trigger enable.
            //<o3.30..31> PIN15 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
    //</h>
    //<q4> Interrupt enable
    //<i> Port PD interrupt enable.
//</e>
#define CONF_ExicPDInit_EN           0
#define CONF_ExicPDInit_AndOrMask    0x00000000
#define CONF_ExicPDInit_Mask         0x00000000  
#define CONF_ExicPDInit_Mode         0x55555555
#define CONF_ExicPDInit_INT          0
#define CONF_ExicPDInit_AINV         0


//
//=============================  PE EXIC Setting  ==============================
//
//<e0> Enable EXIC PE initial
//<i> Port PE external interrupt configuration enable.
    //<h> AND (KBI)
    //<i> Port PE AND mask setting for External KBI input.
        //<o1.16..31>AND Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PE AND mask bits. Each bit is used to disable(mask) or enable the related PEx input line.
        //<q5> AND unmatch enable
        //<i> External interrupt PE AND path signal inverse enable.
    //</h>
    //<h> OR (Interrupt)
    //<i> Port PE OR mask setting for External interrupt input.
        //<o1.0..15> OR  Mask  (0x0000 ~ 0xFFFF) <0x0000-0xFFFF>
        //<i> External interrupt PE OR mask bits. Each bit is used to disable(mask) or enable the related PEx input line.
    //</h>
    //<h> Trigger mode
    //<i> Port PE pin edge/level event trigger setting.
        //<e2.1>  PE0
        //<i> External interrupt PE0 pin edge/level event trigger enable.
            //<o3.0..1> PIN0 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.3>  PE1
        //<i> External interrupt PE1 pin edge/level event trigger enable.
            //<o3.2..3> PIN1 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.5>  PE2
        //<i> External interrupt PE2 pin edge/level event trigger enable.
            //<o3.4..5> PIN2 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.7>  PE3
        //<i> External interrupt PE3 pin edge/level event trigger enable.
            //<o3.6..7> PIN3 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.17>  PE8
        //<i> External interrupt PE8 pin edge/level event trigger enable.
            //<o3.16..17> PIN8 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.19>  PE9
        //<i> External interrupt PE9 pin edge/level event trigger enable.
            //<o3.18..19> PIN9 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.25>  PE12
        //<i> External interrupt PE12 pin edge/level event trigger enable.
            //<o3.24..25> PIN12 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.27>  PE13
        //<i> External interrupt PE13 pin edge/level event trigger enable.
            //<o3.26..27> PIN13 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.29>  PE14
        //<i> External interrupt PE14 pin edge/level event trigger enable.
            //<o3.28..29> PIN14 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
        //<e2.31>  PE15
        //<i> External interrupt PE15 pin edge/level event trigger enable.
            //<o3.30..31> PIN15 trigger event is <1=>Level <2=>Edge <3=> Dual-edge
            //<i> [1] Level : External input trigger by voltage level (Low or High level select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [2] Edge : External input trigger by single edge (Rising or Falling edge select by "INV : Input inverse" item in MG32x02z_GPIO_Init.h Chip Initial Wizard)
            //<i> [3] Dual-edge : External input trigger by rising or falling edge
        //</e>
    //</h>
    //<q4> Interrupt enable
    //<i> Port PE interrupt enable.
//</e>
#define CONF_ExicPEInit_EN           0
#define CONF_ExicPEInit_AndOrMask    0x00000000
#define CONF_ExicPEInit_Mask         0x00000000  
#define CONF_ExicPEInit_Mode         0x55555555
#define CONF_ExicPEInit_INT          0
#define CONF_ExicPEInit_AINV         0

//<q0.1> RXEV mask enable
//<i> Interrupt event mask control bit for RXEV (0= Disable mask, 1= Enable mask).
//<o1> NMI interrupt source select
//<0x00=> Disable
//<0x01=> External PIN
//<0x81=> WWDT 
//<0x85=> SYS 
//<0x8D=> EXIC0(PA)
//<0x91=> EXIC1(PB)
//<0x95=> EXIC2(PC)
//<0x9D=> EXIC3(PD/PE)
//<0xA1=> CMPx
//<0xA5=> DMA
//<0xAD=> ADC
//<0xB1=> DAC
//<0xB5=> TM0x
//<0xBD=> TM10
//<0xC1=> TM1x
//<0xC5=> TM20
//<0xCD=> TM2x
//<0xD1=> TM3x
//<0xD5=> URT0
//<0xDD=> URT123
//<0xE1=> URT4x
//<0xE5=> SPI0
//<0xED=> I2C0
//<0xF1=> I2Cx
//<0xFD=> APX
//<i> SYS including of (IWDT, PW, RTC, CSC, APB, MEM, EMB) interrupts
//<i> CMPx including of AC0/1/2/3 interrupts
//<i> TM0x, TM1x, TM2x, TM3x separately including of TM00/TM01, TM16, TM26, TM36 interrupts
//<i> URT4x, I2Cx separately including of URT4/5/6/7, I2C1 interrupts
#define MG32x02z_ExicRXEV_EN            0x00
#define MG32x02z_ExicNMI_SEL            0x00

// <<< end of configuration section >>>

void EXIC_Init(void);


#endif  // _MG32x02z_EXIC_Init_H
