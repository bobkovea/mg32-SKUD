/**
 ******************************************************************************
 *
 * @file        MG32x02z_GPIO_TSSOP20_Init.h
 *
 * @brief       This file is used to configure GPIO setting.
 *              Device : MG32F02A032
 *              Package: TSSOP20
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

#ifndef _MG32x02z_GPIO_Init_H

#define _MG32x02z_GPIO_Init_H

#include "MG32x02z.h"
#include "MG32x02z_GPIO.h"

// <<< Use Configuration Wizard in Context Menu >>>

#define MG32x02z_PIN0_Mask        0x0001
#define MG32x02z_PIN1_Mask        0x0002
#define MG32x02z_PIN2_Mask        0x0004
#define MG32x02z_PIN3_Mask        0x0008
#define MG32x02z_PIN4_Mask        0x0010
#define MG32x02z_PIN5_Mask        0x0020
#define MG32x02z_PIN6_Mask        0x0040
#define MG32x02z_PIN7_Mask        0x0080
#define MG32x02z_PIN8_Mask        0x0100
#define MG32x02z_PIN9_Mask        0x0200
#define MG32x02z_PIN10_Mask       0x0400
#define MG32x02z_PIN11_Mask       0x0800
#define MG32x02z_PIN12_Mask       0x1000
#define MG32x02z_PIN13_Mask       0x2000
#define MG32x02z_PIN14_Mask       0x4000
#define MG32x02z_PIN15_Mask       0x8000


#define PA_OUT_ADR               GPIOA_Base + 0
#define PA_FLT_ADR               IOMA_Base + 0x40
#define PA0_CR_ADR               IOMA_Base + 4*0
#define PA1_CR_ADR               IOMA_Base + 4*1
#define PA2_CR_ADR               IOMA_Base + 4*2
#define PA3_CR_ADR               IOMA_Base + 4*3
#define PA4_CR_ADR               IOMA_Base + 4*4
#define PA5_CR_ADR               IOMA_Base + 4*5
#define PA6_CR_ADR               IOMA_Base + 4*6
#define PA7_CR_ADR               IOMA_Base + 4*7
#define PA8_CR_ADR               IOMA_Base + 4*8
#define PA9_CR_ADR               IOMA_Base + 4*9
#define PA10_CR_ADR              IOMA_Base + 4*10
#define PA11_CR_ADR              IOMA_Base + 4*11
#define PA12_CR_ADR              IOMA_Base + 4*12
#define PA13_CR_ADR              IOMA_Base + 4*13
#define PA14_CR_ADR              IOMA_Base + 4*14
#define PA15_CR_ADR              IOMA_Base + 4*15

#define PB_OUT_ADR               GPIOB_Base + 0
#define PB_FLT_ADR               IOMB_Base + 0x40
#define PB0_CR_ADR               IOMB_Base + 4*0
#define PB1_CR_ADR               IOMB_Base + 4*1
#define PB2_CR_ADR               IOMB_Base + 4*2
#define PB3_CR_ADR               IOMB_Base + 4*3
#define PB4_CR_ADR               IOMB_Base + 4*4
#define PB5_CR_ADR               IOMB_Base + 4*5
#define PB6_CR_ADR               IOMB_Base + 4*6
#define PB7_CR_ADR               IOMB_Base + 4*7
#define PB8_CR_ADR               IOMB_Base + 4*8
#define PB9_CR_ADR               IOMB_Base + 4*9
#define PB10_CR_ADR              IOMB_Base + 4*10
#define PB11_CR_ADR              IOMB_Base + 4*11
#define PB12_CR_ADR              IOMB_Base + 4*12
#define PB13_CR_ADR              IOMB_Base + 4*13
#define PB14_CR_ADR              IOMB_Base + 4*14
#define PB15_CR_ADR              IOMB_Base + 4*15

#define PC_OUT_ADR               GPIOC_Base + 0
#define PC_FLT_ADR               IOMC_Base + 0x40
#define PC0_CR_ADR               IOMC_Base + 4*0
#define PC1_CR_ADR               IOMC_Base + 4*1
#define PC2_CR_ADR               IOMC_Base + 4*2
#define PC3_CR_ADR               IOMC_Base + 4*3
#define PC4_CR_ADR               IOMC_Base + 4*4
#define PC5_CR_ADR               IOMC_Base + 4*5
#define PC6_CR_ADR               IOMC_Base + 4*6
#define PC7_CR_ADR               IOMC_Base + 4*7
#define PC8_CR_ADR               IOMC_Base + 4*8
#define PC9_CR_ADR               IOMC_Base + 4*9
#define PC10_CR_ADR              IOMC_Base + 4*10
#define PC11_CR_ADR              IOMC_Base + 4*11
#define PC12_CR_ADR              IOMC_Base + 4*12
#define PC13_CR_ADR              IOMC_Base + 4*13
#define PC14_CR_ADR              IOMC_Base + 4*14
#define PC15_CR_ADR              IOMC_Base + 4*15

/**
 ******************************************************************************
 *
 * @brief       GPIO Initial Configure - MG32F02A032 (TSSOP20-Package)
 *
 ******************************************************************************
 */
//<h> GPIO Initial Configure - MG32F02A032 (TSSOP20-Package)

//
//==============================  PA IO Setting  ===============================
//
//  <e0> GPIOA Configuration
//      <o1> PA Output setting<0x0000-0xFFFF>
//          <i> GPIO PA output data bit 0~15. These bits are mapping to PA0 ~ PA15.
//      <o2> PA Input filter clock source select <0=> CLK_AHB <1=> CLK_AHB_DIV8 <2=> CLK_ILRCO <3=> TM00_TRGO <4=> CK_UT
//          <i> PA port input deglitch filter clock source select for all pins of the port.
//          <i> Default: FCKS = CLK_AHB
//      <e3.8> PA8 Configuration
//          <o12.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o12.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o12.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o12.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o12.8..9>      ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o12.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o12.12..15>    AFS : Alternate function select             <0=> GPA8
//          <i> Default: AFS = GPA8
//      </e> 
//      <e3.10> PA10 Configuration
//          <o14.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o14.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o14.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o14.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o14.8..9>      ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o14.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o14.12..15>    AFS : Alternate function select             <0=> GPA10
//          <i> Default: AFS = GPA10
//      </e> 
        #define CONF_GPIOAInit_EN           1
        #define CONF_PA_OUTPUT_DEFAULT      0x0000
        #define CONF_PA_FILTER_CLK          0
        #define CONF_GPIOAInit_Mask         0x0400
        #define CONF_PA0_CR                 0x00000000
        #define CONF_PA1_CR                 0x00000000
        #define CONF_PA2_CR                 0x00000000
        #define CONF_PA3_CR                 0x00000000
        #define CONF_PA4_CR                 0x00000000
        #define CONF_PA5_CR                 0x00000000
        #define CONF_PA6_CR                 0x00000000
        #define CONF_PA7_CR                 0x00000000
        #define CONF_PA8_CR                 0x00000023
        #define CONF_PA9_CR                 0x00000000
        #define CONF_PA10_CR                0x00000023
        #define CONF_PA11_CR                0x00000000
        #define CONF_PA12_CR                0x00000000
        #define CONF_PA13_CR                0x00000000
        #define CONF_PA14_CR                0x00000000
        #define CONF_PA15_CR                0x00000000
//  </e> 

//
//==============================  PB IO Setting  ===============================
//
//  <e0> GPIOB Configuration
//      <o1> PB Output setting<0x0000-0xFFFF>
//          <i> GPIO PB output data bit 0~15. These bits are mapping to PB0 ~ PB15.
//      <o2> PB Input filter clock source select <0=> CLK_AHB <1=> CLK_AHB_DIV8 <2=> CLK_ILRCO <3=> TM00_TRGO <4=> CK_UT
//          <i> PB port input deglitch filter clock source select for all pins of the port.
//          <i> Default: FCKS = CLK_AHB
//      <e3.0> PB0 Configuration
//          <o4.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o4.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o4.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o4.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o4.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <1=> LEVEL1 <2=> LEVEL2 <3=> LEVEL3
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [1] LEVEL1 : Drive strength-1/2
//             <i> [2] LEVEL2 : Drive strength-1/4
//             <i> [3] LEVEL3 : Drive strength-1/8
//          <o4.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o4.12..15>     AFS : Alternate function select             <0=> GPB0 <2=> SPI0_NSS <3=> TM01_ETR <4=> TM00_CKO <5=> TM16_ETR <7=> TM36_ETR
//          <i> Default: AFS = GPB0
//      </e> 
//      <e3.1> PB1 Configuration
//          <o5.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o5.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o5.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o5.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o5.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <1=> LEVEL1 <2=> LEVEL2 <3=> LEVEL3
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [1] LEVEL1 : Drive strength-1/2
//             <i> [2] LEVEL2 : Drive strength-1/4
//             <i> [3] LEVEL3 : Drive strength-1/8
//          <o5.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o5.12..15>     AFS : Alternate function select             <0=> GPB1 <2=> SPI0_MISO <3=> TM01_TRGO <4=> TM10_CKO <5=> TM16_TRGO <7=> TM36_TRGO
//          <i> Default: AFS = GPB1
//      </e> 
//      <e3.2> PB2 Configuration
//          <o6.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o6.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o6.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o6.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o6.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <1=> LEVEL1 <2=> LEVEL2 <3=> LEVEL3
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [1] LEVEL1 : Drive strength-1/2
//             <i> [2] LEVEL2 : Drive strength-1/4
//             <i> [3] LEVEL3 : Drive strength-1/8
//          <o6.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o6.12..15>     AFS : Alternate function select             <0=> GPB2 <1=> ADC0_TRG <2=> SPI0_CLK <3=> TM01_CKO <5=> TM16_CKO <7=> I2C0_SDA <10=> URT0_TX
//          <i> Default: AFS = GPB2
//      </e> 
//      <e3.3> PB3 Configuration
//          <o7.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o7.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o7.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o7.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o7.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <1=> LEVEL1 <2=> LEVEL2 <3=> LEVEL3
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [1] LEVEL1 : Drive strength-1/2
//             <i> [2] LEVEL2 : Drive strength-1/4
//             <i> [3] LEVEL3 : Drive strength-1/8
//          <o7.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o7.12..15>     AFS : Alternate function select             <0=> GPB3 <1=> ADC0_OUT <2=> SPI0_MOSI <5=> TM36_CKO <7=> I2C0_SCL <10=> URT0_RX
//          <i> Default: AFS = GPB3
//      </e> 
//      <e3.8> PB8 Configuration
//          <o12.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o12.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o12.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o12.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o12.8..9>      ODC : Output drive strength                 <0=> LEVEL0 <1=> LEVEL1 <2=> LEVEL2 <3=> LEVEL3
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [1] LEVEL1 : Drive strength-1/2
//             <i> [2] LEVEL2 : Drive strength-1/4
//             <i> [3] LEVEL3 : Drive strength-1/8
//          <o12.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o12.12..15>    AFS : Alternate function select             <0=> GPB8 <1=> CMP0_P0 <2=> RTC_OUT <3=> URT0_TX <6=> TM36_OC01 <7=> SPI0_D3 <10=> OBM_P0
//          <i> Default: AFS = GPB8
//      </e> 
//      <e3.9> PB9 Configuration
//          <o13.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o13.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o13.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o13.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o13.8..9>      ODC : Output drive strength                 <0=> LEVEL0 <1=> LEVEL1 <2=> LEVEL2 <3=> LEVEL3
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [1] LEVEL1 : Drive strength-1/2
//             <i> [2] LEVEL2 : Drive strength-1/4
//             <i> [3] LEVEL3 : Drive strength-1/8
//          <o13.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o13.12..15>    AFS : Alternate function select             <0=> GPB9 <1=> CMP1_P0 <2=> RTC_TS <3=> URT0_RX <6=> TM36_OC02 <7=> SPI0_D2 <10=> OBM_P1
//          <i> Default: AFS = GPB9
//      </e> 
//      <e3.10> PB10 Configuration
//          <o14.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o14.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o14.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o14.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o14.8..9>      ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o14.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o14.12..15>    AFS : Alternate function select             <0=> GPB10 <2=> I2C0_SCL <3=> URT0_NSS <6=> TM36_OC11 <7=> URT1_TX <10=> SPI0_NSSI
//          <i> Default: AFS = GPB10
//      </e> 
//      <e3.11> PB11 Configuration
//          <o15.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//          <o15.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o15.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o15.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o15.8..9>      ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o15.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o15.12..15>    AFS : Alternate function select             <0=> GPB11 <2=> I2C0_SDA <3=> URT0_DE <4=> IR_OUT <6=> TM36_OC12 <7=> URT1_RX <10=> DMA_TRG0
//          <i> Default: AFS = GPB11
//      </e> 
        #define CONF_GPIOBInit_EN           1
        #define CONF_PB_OUTPUT_DEFAULT      0x0000
        #define CONF_PB_FILTER_CLK          0
        #define CONF_GPIOBInit_Mask         0x0F0F
        #define CONF_PB0_CR                 0x00000002
        #define CONF_PB1_CR                 0x00000002
        #define CONF_PB2_CR                 0x00002002
        #define CONF_PB3_CR                 0x00002002
        #define CONF_PB4_CR                 0x00000000
        #define CONF_PB5_CR                 0x00000000
        #define CONF_PB6_CR                 0x00000000
        #define CONF_PB7_CR                 0x00000000
        #define CONF_PB8_CR                 0x00000002
        #define CONF_PB9_CR                 0x00000002
        #define CONF_PB10_CR                0x00000002
        #define CONF_PB11_CR                0x00000002
        #define CONF_PB12_CR                0x00000000
        #define CONF_PB13_CR                0x00000000
        #define CONF_PB14_CR                0x00000000
        #define CONF_PB15_CR                0x00000000
//  </e> 

//
//==============================  PC IO Setting  ===============================
//
//  <e0> GPIOC Configuration
//      <o1> PC Output setting<0x0000-0xFFFF>
//          <i> GPIO PC output data bit 0~15. These bits are mapping to PC0 ~ PC15.
//      <o2> PC Input filter clock source select <0=> CLK_AHB <1=> CLK_AHB_DIV8 <2=> CLK_ILRCO <3=> TM00_TRGO <4=> CK_UT
//          <i> PC port input deglitch filter clock source select for all pins of the port.
//          <i> Default: FCKS = CLK_AHB
//      <e3.0> PC0 Configuration
//          <o4.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o4.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o4.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o4.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o4.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o4.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o4.12..15>     AFS : Alternate function select             <0=> GPC0 <1=> ICKO <2=> TM00_CKO <3=> URT0_CLK <6=> TM36_OC00 <7=> I2C0_SCL <10=> URT0_TX
//          <i> Default: AFS = GPC0
//      </e> 
//      <e3.1> PC1 Configuration
//          <o5.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o5.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o5.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o5.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o5.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o5.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o5.12..15>     AFS : Alternate function select             <0=> GPC1 <1=> ADC0_TRG <2=> TM01_CKO <3=> TM36_IC0 <4=> URT1_CLK <6=> TM36_OC0N <7=> I2C0_SDA <10=> URT0_RX
//          <i> Default: AFS = GPC1
//      </e> 
//      <e3.4> PC4 Configuration
//          <o8.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = QB
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o8.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o8.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = ENABLE
//          <o8.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o8.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o8.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o8.12..15>     AFS : Alternate function select             <0=> GPC4 <1=> SWCLK <2=> I2C0_SCL <3=> URT0_RX <4=> URT1_RX <6=> TM36_OC2
//          <i> Default: AFS = GPC4
//      </e> 
//      <e3.5> PC5 Configuration
//          <o9.0..2>       IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = QB
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o9.3>          HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o9.5>          PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = ENABLE
//          <o9.7>          INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o9.8..9>       ODC : Output drive strength                 <0=> LEVEL0 <2=> LEVEL2
//          <i> Default: ODC = LEVEL0
//             <i> [0] LEVEL0 : Drive strength-full
//             <i> [2] LEVEL2 : Drive strength-1/4
//          <o9.10..11>     FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o9.12..15>     AFS : Alternate function select             <0=> GPC5 <1=> SWDIO <2=> I2C0_SDA <3=> URT0_TX <4=> URT1_TX <6=> TM36_OC3
//          <i> Default: AFS = GPC5
//      </e> 
//      <e3.6> PC6 Configuration
//          <o10.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = QB
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o10.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = ENABLE
//          <o10.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o10.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o10.12..15>    AFS : Alternate function select             <0=> GPC6 <1=> RSTN <2=> RTC_TS <3=> URT0_NSS <4=> URT1_NSS
//          <i> Default: AFS = GPC6
//      </e> 
//      <e3.13> PC13 Configuration
//          <o17.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o17.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o17.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o17.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o17.12..15>    AFS : Alternate function select             <0=> GPC13 <1=> XIN <2=> URT1_NSS <3=> URT0_CTS <5=> TM10_ETR <7=> TM36_OC00
//          <i> Default: AFS = GPC13
//      </e> 
//      <e3.14> PC14 Configuration
//          <o18.0..2>      IOM : IO mode control                       <0=> AIO <1=> ODO <2=> PPO <3=> DIN <4=> QB
//          <i> Default: IOM = AIO
//             <i> [0] AIO : analog IO
//             <i> [1] ODO : open drain output
//             <i> [2] PPO : push pull output
//             <i> [3] DIN : Digital input
//             <i> [4] QB : Quasi-Bidirectional output drive high one CLK
//          <o18.3>         HS : Output high speed                      <0=> DISABLE <1=> ENABLE
//          <i> Default: HS = DISABLE
//          <o18.5>         PU : Pull-up resister                       <0=> DISABLE <1=> ENABLE
//          <i> Default: PU = DISABLE
//          <o18.7>         INV : Input inverse                         <0=> DISABLE <1=> ENABLE
//          <i> Default: INV = DISABLE
//          <o18.10..11>    FDIV : Input filter clock divider           <0=> BYPASS <1=> DIV1 <2=> DIV4 <3=> DIV16
//          <i> Default: FDIV = BYPASS
//             <i> [0] BYPASS : Bypass filter
//             <i> [1] DIV1 : Divided by 1
//             <i> [2] DIV4 : Divided by 4
//             <i> [3] DIV16 : Divided by 16
//          <o18.12..15>    AFS : Alternate function select             <0=> GPC14 <1=> XOUT <2=> URT1_TMO <3=> URT0_RTS <5=> TM10_CKO <7=> TM36_OC10
//          <i> Default: AFS = GPC14
//      </e> 
        #define CONF_GPIOCInit_EN           1
        #define CONF_PC_OUTPUT_DEFAULT      0x7FFF
        #define CONF_PC_FILTER_CLK          0
        #define CONF_GPIOCInit_Mask         0x0003
        #define CONF_PC0_CR                 0x0000A022
        #define CONF_PC1_CR                 0x0000A021
        #define CONF_PC2_CR                 0x00000000
        #define CONF_PC3_CR                 0x00000000
        #define CONF_PC4_CR                 0x80000024
        #define CONF_PC5_CR                 0x80000024
        #define CONF_PC6_CR                 0x80000024
        #define CONF_PC7_CR                 0x00000000
        #define CONF_PC8_CR                 0x00000000
        #define CONF_PC9_CR                 0x00000000
        #define CONF_PC10_CR                0x00000000
        #define CONF_PC11_CR                0x00000000
        #define CONF_PC12_CR                0x00000000
        #define CONF_PC13_CR                0x00000000
        #define CONF_PC14_CR                0x00000000
        #define CONF_PC15_CR                0x00000000
//  </e> 
//</h> 

/**
 ******************************************************************************
 *
 * @brief       GPIO Initial Mask Matrix - MG32F02A032 (TSSOP20-Package)
 *
 ******************************************************************************
 */
    static const uint32_t GPIO_CFG[]=
    {
        #if CONF_GPIOAInit_EN == 1
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN0_Mask) == MG32x02z_PIN0_Mask
                PA0_CR_ADR,CONF_PA0_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN1_Mask) == MG32x02z_PIN1_Mask
                PA1_CR_ADR,CONF_PA1_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN2_Mask) == MG32x02z_PIN2_Mask
                PA2_CR_ADR,CONF_PA2_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN3_Mask) == MG32x02z_PIN3_Mask
                PA3_CR_ADR,CONF_PA3_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN4_Mask) == MG32x02z_PIN4_Mask
                PA4_CR_ADR,CONF_PA4_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN5_Mask) == MG32x02z_PIN5_Mask
                PA5_CR_ADR,CONF_PA5_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN6_Mask) == MG32x02z_PIN6_Mask
                PA6_CR_ADR,CONF_PA6_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN7_Mask) == MG32x02z_PIN7_Mask
                PA7_CR_ADR,CONF_PA7_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN8_Mask) == MG32x02z_PIN8_Mask
                PA8_CR_ADR,CONF_PA8_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN9_Mask) == MG32x02z_PIN9_Mask
                PA9_CR_ADR,CONF_PA9_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN10_Mask) == MG32x02z_PIN10_Mask
                PA10_CR_ADR,CONF_PA10_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN11_Mask) == MG32x02z_PIN11_Mask
                PA11_CR_ADR,CONF_PA11_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN12_Mask) == MG32x02z_PIN12_Mask
                PA12_CR_ADR,CONF_PA12_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN13_Mask) == MG32x02z_PIN13_Mask
                PA13_CR_ADR,CONF_PA13_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN14_Mask) == MG32x02z_PIN14_Mask
                PA14_CR_ADR,CONF_PA14_CR,
            #endif
            #if (CONF_GPIOAInit_Mask & MG32x02z_PIN15_Mask) == MG32x02z_PIN15_Mask
                PA15_CR_ADR,CONF_PA15_CR,
            #endif
            PA_FLT_ADR,CONF_PA_FILTER_CLK,
            PA_OUT_ADR,CONF_PA_OUTPUT_DEFAULT,
        #endif
        #if CONF_GPIOBInit_EN == 1
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN0_Mask) == MG32x02z_PIN0_Mask
                PB0_CR_ADR,CONF_PB0_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN1_Mask) == MG32x02z_PIN1_Mask
                PB1_CR_ADR,CONF_PB1_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN2_Mask) == MG32x02z_PIN2_Mask
                PB2_CR_ADR,CONF_PB2_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN3_Mask) == MG32x02z_PIN3_Mask
                PB3_CR_ADR,CONF_PB3_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN4_Mask) == MG32x02z_PIN4_Mask
                PB4_CR_ADR,CONF_PB4_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN5_Mask) == MG32x02z_PIN5_Mask
                PB5_CR_ADR,CONF_PB5_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN6_Mask) == MG32x02z_PIN6_Mask
                PB6_CR_ADR,CONF_PB6_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN7_Mask) == MG32x02z_PIN7_Mask
                PB7_CR_ADR,CONF_PB7_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN8_Mask) == MG32x02z_PIN8_Mask
                PB8_CR_ADR,CONF_PB8_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN9_Mask) == MG32x02z_PIN9_Mask
                PB9_CR_ADR,CONF_PB9_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN10_Mask) == MG32x02z_PIN10_Mask
                PB10_CR_ADR,CONF_PB10_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN11_Mask) == MG32x02z_PIN11_Mask
                PB11_CR_ADR,CONF_PB11_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN12_Mask) == MG32x02z_PIN12_Mask
                PB12_CR_ADR,CONF_PB12_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN13_Mask) == MG32x02z_PIN13_Mask
                PB13_CR_ADR,CONF_PB13_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN14_Mask) == MG32x02z_PIN14_Mask
                PB14_CR_ADR,CONF_PB14_CR,
            #endif
            #if (CONF_GPIOBInit_Mask & MG32x02z_PIN15_Mask) == MG32x02z_PIN15_Mask
                PB15_CR_ADR,CONF_PB15_CR,
            #endif
            PB_FLT_ADR,CONF_PB_FILTER_CLK,
            PB_OUT_ADR,CONF_PB_OUTPUT_DEFAULT,
        #endif
        #if CONF_GPIOCInit_EN == 1
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN0_Mask) == MG32x02z_PIN0_Mask
                PC0_CR_ADR,CONF_PC0_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN1_Mask) == MG32x02z_PIN1_Mask
                PC1_CR_ADR,CONF_PC1_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN2_Mask) == MG32x02z_PIN2_Mask
                PC2_CR_ADR,CONF_PC2_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN3_Mask) == MG32x02z_PIN3_Mask
                PC3_CR_ADR,CONF_PC3_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN4_Mask) == MG32x02z_PIN4_Mask
                PC4_CR_ADR,CONF_PC4_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN5_Mask) == MG32x02z_PIN5_Mask
                PC5_CR_ADR,CONF_PC5_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN6_Mask) == MG32x02z_PIN6_Mask
                PC6_CR_ADR,CONF_PC6_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN7_Mask) == MG32x02z_PIN7_Mask
                PC7_CR_ADR,CONF_PC7_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN8_Mask) == MG32x02z_PIN8_Mask
                PC8_CR_ADR,CONF_PC8_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN9_Mask) == MG32x02z_PIN9_Mask
                PC9_CR_ADR,CONF_PC9_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN10_Mask) == MG32x02z_PIN10_Mask
                PC10_CR_ADR,CONF_PC10_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN11_Mask) == MG32x02z_PIN11_Mask
                PC11_CR_ADR,CONF_PC11_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN12_Mask) == MG32x02z_PIN12_Mask
                PC12_CR_ADR,CONF_PC12_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN13_Mask) == MG32x02z_PIN13_Mask
                PC13_CR_ADR,CONF_PC13_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN14_Mask) == MG32x02z_PIN14_Mask
                PC14_CR_ADR,CONF_PC14_CR,
            #endif
            #if (CONF_GPIOCInit_Mask & MG32x02z_PIN15_Mask) == MG32x02z_PIN15_Mask
                PC15_CR_ADR,CONF_PC15_CR,
            #endif
            PC_FLT_ADR,CONF_PC_FILTER_CLK,
            PC_OUT_ADR,CONF_PC_OUTPUT_DEFAULT,
        #endif
        0,
    };
// <<< end of Configuration section >>>    
 
    
void GPIO_Init(void);    
    
    
#endif  // _MG32x02z_GPIO_Init_H
