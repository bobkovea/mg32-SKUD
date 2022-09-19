/**
 ******************************************************************************
 *
 * @file        MG32x02z_APB_Init.h
 *
 * @brief       This file is used to configure APB setting.
 *              Apply device : MG32F02A128/U128/A064/U064
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2021/07/15
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
 ******************************************************************************
 */

#ifndef _MG32x02z_APB_Init_H

#define _MG32x02z_APB_Init_H

/* Includes ------------------------------------------------------------------*/
/* Wizard menu ---------------------------------------------------------------*/
// <<< Use Configuration Wizard in Context Menu >>>

//  <h> IR Configuration
//      <o0.12..14> IR data envelope signal source select 
//          <0=> 0 (Output 0)
//          <1=> TM20 : TM20_TRGO signal
//          <2=> TM26 : TM26_TRGO signal
//          <3=> TM36 : TM36_TRGO signal
//          <4=> SPI0 : SPI0_MOSI signal
//          <5=> URT1 : URT1_TX signal
//          <6=> URT2 : URT2_TX signal
//      <q0.5> IR data envelope signal inverse enable bit <0=> Disable <1=> Enable
//      <o0.8..10> IR carrier clock source select 
//          <0=> 0 (Output 0)
//          <1=> TM00 : TM00_TRGO signal
//          <2=> TM01 : TM01_TRGO signal
//          <3=> TM10 : TM10_TRGO signal
//          <4=> TM16 : TM16_TRGO signal
//          <5=> URT1 : URT1_TMO signal
//          <6=> URT2 : URT2_TMO signal
//      <q0.4> IR clock signal inverse enable bit <0=> Disable <1=> Enable
//  </h>
//  
//  <h> ITR6/7 Configuration
//      <o1.0..2> Timer internal common trigger source ITR6 source select
//          <0=> TM00 : TM00_TRGO signal
//          <1=> TM10 : TM10_TRGO signal
//          <2=> TM20 : TM20_TRGO signal
//          <3=> TM36 : TM36_TRGO signal
//          <4=> INTPB : INT_PB signal
//          <5=> U1TMO : URT1_TMO signal
//          <6=> U2BRO : URT2_BRO signal
//          <7=> U2TMO : URT2_TMO signal
//      <o1.4..7> Timer internal common trigger source ITR7 source select
//          <0=> TM01 : TM01_TRGO signal
//          <1=> TM16 : TM16_TRGO signal
//          <2=> TM26 : TM26_TRGO signal
//          <3=> ADC0 : ADC0_OUT signal
//          <4=> INTPD : INT_PD signal
//          <5=> U1BRO : URT1_BRO signal
//          <8=> ICKO : ICKO_INT signal
//          <9=> RTC : RTC_OUT signal
//          <10=> XOR : TM36_XOR signal
//          <11=> NCO0 : NCO0_OUT signal
//  </h>

#define CONF_APB_CR0        0x00000000
#define CONF_APB_CR2        0x00000000

//  <h> OBM0 Configuration
//      <h> OBM0 break signal source channel-n select
//          <o0.16..19> OBM0 break signal source channel-0 select
//              <0=> BKS0 Logic 1 
//              <1=> BKS0 INT PA       
//              <2=> BKS0 INT PC       
//              <3=> BKS0 ADC0 OUT     
//              <4=> BKS0 TM00 TRGO    
//              <5=> BKS0 TM10 TRGO    
//              <6=> BKS0 TM20 TRGO    
//              <7=> BKS0 CCL P0       
//              <8=> BKS0 TM20 OC00    
//              <9=> BKS0 TM36 OC2     
//              <10=> BKS0 CMP0 OUT   
//              <12=> BKS0 URT0 TX    
//              <13=> BKS0 URT2 TX    
//              <14=> BKS0 URT0 RX    
//              <15=> BKS0 URT2 RX    
//          <q0.8> OBM0 break source-0 signal inverse enable bit <0=> Disable <1=> Enable
//
//          <o0.20..23> OBM0 break signal source channel-1 select
//              <0=> BKS1 Logic 1    
//              <1=> BKS1 INT PB     
//              <2=> BKS1 INT PD      
//              <3=> BKS1 INT BOD1   
//              <4=> BKS1 TM01 TRGO  
//              <5=> BKS1 TM16 TRGO  
//              <6=> BKS1 TM26 TRGO  
//              <7=> BKS1 CCL P1      
//              <8=> BKS1 TM20 OC10  
//              <9=> BKS1 TM36 OC3    
//              <10=> BKS1 CMP1 OUT 
//              <12=> BKS1 URT1 TX   
//              <14=> BKS1 URT1 RX 
//          <q0.9> OBM0 break source-1 signal inverse enable bit <0=> Disable <1=> Enable
//
//          <o0.24..27> OBM0 break signal source channel-2 select
//              <0=> BKS2 Logic 1
//              <1=> BKS2 INT PE   
//              <3=> BKS2 SPI0 MOSI
//              <6=> BKS2 TM36 TRGO
//              <12=> BKS2 URT2 BRO
//              <13=> BKS2 URT2 TMO
//          <q0.10> OBM0 break source-2 signal inverse enable bit <0=> Disable <1=> Enable
//
//      </h>
//      <o0.0..1> OBM0 break operation mode select 
//          <i> User selects the mode to control the APB_OBM0_SW signal. When selects AND, the APB_OBM0_SW signal is directly controlled by the AND signal 
//          <i> of all break channels' output. When selects CLR/SET/TOGGLE, the APB_OBM0_SW signal is controlled by STA(APB_OBM0_STA) bit and can update by firmware.
//          <0=> AND : AND signal of all break channels' output (OBMx_LevelSwitch) 
//          <1=> CLR : STA bit is cleared by falling edge of OR signal (OBMx_ClearByFallingEdge)
//          <2=> SET : STA bit is set by falling edge of OR signal (OBMx_SetByFallingEdge) 
//          <4=> TOGGLE : STA bit is toggle by falling edge of OR signal (OBMx_DualEdgeSwitch)
//      <o0.4..5> OBM0 break switching signal initial state. <2=> 0 (Output 0) <3=> 1 (Output 1)
//
//      <h> OBM0 output source channel-n signal select.
//          <o1.16..19> OBM0 output source channel-0 select
//              <0=> OBMxCH0 Logic 0
//              <1=> OBMxCH0 INT PA 
//              <2=> OBMxCH0 INT PC 
//              <3=> OBMxCH0 INT PE 
//              <4=> OBMxCH0 TM00 CKO 
//              <5=> OBMxCH0 TM10 CKO 
//              <6=> OBMxCH0 TM20 CKO 
//              <7=> OBMxCH0 TM36 CKO 
//              <8=> OBMxCH0 TM20 OC00
//              <9=> OBMxCH0 TM36 OC00
//              <10=> OBMxCH0 TM36 OC2 
//              <12=> OBMxCH0 OBM I0     
//              <13=> OBMxCH0 ITR6       
//          <q1.0> OBM0 source channel-0 signal inverse enable bit <0=> Disable <1=> Enable
//
//          <o1.20..23> OBM0 output source channel-1 select
//              <0=> OBMxCH1 Logic 0    
//              <1=> OBMxCH1 INT PB      
//              <2=> OBMxCH1 INT PD      
//              <4=> OBMxCH1 TM01 CKO 
//              <5=> OBMxCH1 TM16 CKO 
//              <6=> OBMxCH1 TM26 CKO 
//              <8=> OBMxCH1 TM20 OC01
//              <9=> OBMxCH1 TM36 OC01
//              <10=> OBMxCH1 TM36 OC3 
//              <12=> OBMxCH1 OBM I1 
//              <13=> OBMxCH1 ITR7   
//              <14=> OBMxCH1 ICKO INT 
//          <q1.1> OBM0 source channel-1 signal inverse enable bit <0=> Disable <1=> Enable
//      </h>
//      <q1.2> OBM0 output signal inverse enable bit <0=> Disable <1=> Enable
//      <o1.4..5> OBM0 output deglitch filter clock source select 
//          <i> The filter is filtering the output signal by sampling 3-times.
//          <0=> Disable
//          <1=> APB : CLK_APB
//          <2=> APB_DIV8 : CLK_APB divide by 8
//          <3=> TM00_TRGO
//  </h>

#define CONF_APB_OBM00      0x00000020
#define CONF_APB_OBM01      0x00000000

//  <H> OBM1 Configuration
//      <h> OBM1 break signal source channel-n select
//          <o0.16..19> OBM1 break signal source channel-0 select
//              <0=> BKS0 Logic 1 
//              <1=> BKS0 INT PA       
//              <2=> BKS0 INT PC       
//              <3=> BKS0 ADC0 OUT     
//              <4=> BKS0 TM00 TRGO    
//              <5=> BKS0 TM10 TRGO    
//              <6=> BKS0 TM20 TRGO    
//              <7=> BKS0 CCL P0       
//              <8=> BKS0 TM20 OC00    
//              <9=> BKS0 TM36 OC2     
//              <10=> BKS0 CMP0 OUT   
//              <12=> BKS0 URT0 TX    
//              <13=> BKS0 URT2 TX    
//              <14=> BKS0 URT0 RX    
//              <15=> BKS0 URT2 RX    
//          <q0.8> OBM1 break source-0 signal inverse enable bit <0=> Disable <1=> Enable
//
//          <o0.20..23> OBM1 break signal source channel-1 select
//              <0=> BKS1 Logic 1    
//              <1=> BKS1 INT PB     
//              <2=> BKS1 INT PD      
//              <3=> BKS1 INT BOD1   
//              <4=> BKS1 TM01 TRGO  
//              <5=> BKS1 TM16 TRGO  
//              <6=> BKS1 TM26 TRGO  
//              <7=> BKS1 CCL P1      
//              <8=> BKS1 TM20 OC10  
//              <9=> BKS1 TM36 OC3    
//              <10=> BKS1 CMP1 OUT 
//              <12=> BKS1 URT1 TX   
//              <14=> BKS1 URT1 RX 
//          <q0.9> OBM1 break source-1 signal inverse enable bit <0=> Disable <1=> Enable
//
//          <o0.24..27> OBM1 break signal source channel-2 select
//              <0=> BKS2 Logic 1
//              <1=> BKS2 INT PE   
//              <3=> BKS2 SPI0 MOSI
//              <6=> BKS2 TM36 TRGO
//              <12=> BKS2 URT2 BRO
//              <13=> BKS2 URT2 TMO
//          <q0.10> OBM1 break source-2 signal inverse enable bit <0=> Disable <1=> Enable
//
//      </h>
//      <o0.0..1> OBM1 break operation mode select 
//          <i> User selects the mode to control the APB_OBM1_SW signal. When selects AND, the APB_OBM1_SW signal is directly controlled by the AND signal 
//          <i> of all break channels' output. When selects CLR/SET/TOGGLE, the APB_OBM1_SW signal is controlled by STA(APB_OBM1_STA) bit and can update by firmware.
//          <0=> AND : AND signal of all break channels' output (OBMx_LevelSwitch) 
//          <1=> CLR : STA bit is cleared by falling edge of OR signal (OBMx_ClearByFallingEdge)
//          <2=> SET : STA bit is set by falling edge of OR signal (OBMx_SetByFallingEdge) 
//          <4=> TOGGLE : STA bit is toggle by falling edge of OR signal (OBMx_DualEdgeSwitch)
//      <o0.4..5> OBM1 break switching signal initial state. <2=> 0 (Output 0) <3=> 1 (Output 1)
//
//      <h> OBM1 output source channel-n signal select.
//          <o1.16..19> OBM1 output source channel-0 select
//              <0=> OBMxCH0 Logic 0
//              <1=> OBMxCH0 INT PA 
//              <2=> OBMxCH0 INT PC 
//              <3=> OBMxCH0 INT PE 
//              <4=> OBMxCH0 TM00 CKO 
//              <5=> OBMxCH0 TM10 CKO 
//              <6=> OBMxCH0 TM20 CKO 
//              <7=> OBMxCH0 TM36 CKO 
//              <8=> OBMxCH0 TM20 OC00
//              <9=> OBMxCH0 TM36 OC00
//              <10=> OBMxCH0 TM36 OC2 
//              <12=> OBMxCH0 OBM I0     
//              <13=> OBMxCH0 ITR6       
//          <q1.0> OBM1 source channel-0 signal inverse enable bit <0=> Disable <1=> Enable
//
//          <o1.20..23> OBM1 output source channel-1 select
//              <0=> OBMxCH1 Logic 0    
//              <1=> OBMxCH1 INT PB      
//              <2=> OBMxCH1 INT PD      
//              <4=> OBMxCH1 TM01 CKO 
//              <5=> OBMxCH1 TM16 CKO 
//              <6=> OBMxCH1 TM26 CKO 
//              <8=> OBMxCH1 TM20 OC01
//              <9=> OBMxCH1 TM36 OC01
//              <10=> OBMxCH1 TM36 OC3 
//              <12=> OBMxCH1 OBM I1 
//              <13=> OBMxCH1 ITR7   
//              <14=> OBMxCH1 ICKO INT 
//          <q1.1> OBM1 source channel-1 signal inverse enable bit <0=> Disable <1=> Enable
//      </h>
//      <q1.2> OBM1 output signal inverse enable bit <0=> Disable <1=> Enable
//      <o1.4..5> OBM1 output deglitch filter clock source select 
//          <i> The filter is filtering the output signal by sampling 3-times.
//          <0=> Disable
//          <1=> APB : CLK_APB
//          <2=> APB_DIV8 : CLK_APB divide by 8
//          <3=> TM00_TRGO
//  </h>

#define CONF_APB_OBM10      0x00000020
#define CONF_APB_OBM11      0x00000000

//  
//  <e0.24> NCO Configuration
//      <i> NCO Overflow Frequency = CK_NCO * INC_Value / 2^20
//      <o0.28..30> NCO input clock source select 
//          <0=> APB NCO IHRCO      
//          <1=> APB NCO CK PLL       
//          <2=> APB NCO APB          
//          <3=> APB NCO CK LS        
//          <4=> APB NCO TM00 TRGO    
//          <5=> APB NCO CK0          
//
//      <o0.26> NCO output mode select 
//          <i> The NCO output frequency needs to be smaller than 1/2 APB clock frequency.
//          <i> If user needs interrupt support the NCO output frequency needs to be less than 1/4 APB clock frequency.
//          <0=> FDC : fixed duty cycle mode
//          <1=> PFM : pulse frequency mode 
//
//      <o1.24..26> NCO PFM mode output pulse width select (for PFM mode)
//          <0=> APB PFM 1Clock
//          <0=> APB PFM 2Clock     
//          <0=> APB PFM 4Clock     
//          <0=> APB PFM 8Clock     
//          <0=> APB PFM 16Clock    
//          <0=> APB PFM 32Clock    
//          <0=> APB PFM 64Clock    
//          <0=> APB PFM 128Clock   
//
//      <q0.25> NCO output inverse enable
//      
//      <o1.0..19> NCO adder accumulator store data <1-1048575>
//          <i> Input range is 1~1048575.
//  </e>

#define CONF_APB_NCO00      0x00000000
#define CONF_APB_NCO01      1

// <<< end of Configuration section >>> 
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/    
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/**
 * @name	Function announce
 *   		
 */
///@{  
void APB_Init(void);    
///@}

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/

#endif  // _MG32x02z_APB_INIT_H
