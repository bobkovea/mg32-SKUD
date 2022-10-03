/**
 *******************************************************************************
 * @file        MG32x02z_TM_Init.h
 *
 * @brief       The TM initial code h file (for MG32F02A032 chip)
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2020/08/25
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2016 MegaWin Technology Co., Ltd.
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
#include "MG32x02z.h"
#include "MG32x02z_TM.h"
#include "MG32x02z_MEM.h"


#ifndef _MG32x02z_TM_INIT_H
/*!< _MG32x02z_TM_INIT_H */ 
#define _MG32x02z_TM_INIT_H

#include "MG32x02z_TM_DRV.h"


//*** <<< Use Configuration Wizard in Context Menu >>> ***
//  <e0.0> Configure TM00 Module
//      <h> Clock configuration
//          <o1.6..7> Main / Prescaler counter clock from <0=> Internal clock <3=> External Clock
//          <h> Internal Clock 
//              <o1.8..9> Internal Clock from <0=> PROC : CK_TM00_PR process clock from CSC <2=> CK_LS
//              <o1.12..13> Internal Clock divider <0=> DIV1 : divided by 1 <1=> DIV2 : divided by 2 <2=> DIV4 : divided by 4 <3=> DIV8 : divided by 8  
//          </h>
//          <h> External Clock
//              <o1.4..5> External Clock source from <0=> ETR (CK_ETR) <1=> ITR (CK_ITR)
//              <o4.8..10> ITR from <0=> ITR0 : TM10_TRGO <2=> ITR2 : CMP0_OUT  <4=> ITR4 : INT_PA <5=> ITR5 : INT_PB <6=> ITR6  <7=> ITR7
//          </h>
//      </h>
//      <h> Timer operation mode
//          <o2.4..5> Operation mode (Up count) <0=> Cascade : 8-bit counter with 8-bit prescaler  Mode <1=> Separate : Separated two 8-bit counters Mode <2=> Full-Counter : 16-bit counter Mode
//          <o2.10..11> External trigger (EXF) <0=> Disable external trigger <1=> Enable external trigger <3=> Enable external invert trigger
//          <o2.15> Timer external trigger update event <0=> Disable <1=> Enable
//      </h>
//      <e3.0> ClockOut config
//          <o3.2..3> TM00 CKO initial state <2=> Output 0 <3=> Output 1
//          <o3.1> CKO event from <0=> Prescaler counter overflow <1=> Main counter overflow
//          <o2.8..9> Repeatability parameter <0=> Always clock out <1=> Only Output once cycle <3=> Repeatability output (Apply TRGI application)
//      </e>
//      <h> Trigger Input/Output config (TRGI & TRGO)
//          <o4.6..7> (TRGI) Timer trigger source from <0=> ETR <1=> ITR (source from Clock configuration)
//          <o4.0..2> (TRGI) Main counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.3..5> (TRGI) Prescaler counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.12..15> (TRGO) Timer trigger output mode select <0=> RST : TM01_RST (Main Timer Reset) <1=> EN : TM01_EN (Main Timer Enable) <2=> UEV : TM01_UEV (Main Timer Update event)
//                                                              <3=> TOF : TM01_TOF (Main Timer overflow) <5=> EN2 : TM01_EN2 (Timer-2 Enable) <6=> TOF2 :TM01_TOF2 (Timer-2 overflow)
//                                                              <8=> UEV2 : TM01_UEV2 (Timer-2 Update event) <9=> SW : TM01_TRGO_SW (software control bit) <14=> TRGI : TM01_TRGI (internal TRGI signal)
//          <o4.22..23> (TRGO) Timer UEV for <0=> All : output all UEV pulses <1=> TOF : output timer overflow pulses <2=> UDF : output timer underflow pulses
//          <o2.12> (UEV) Update event generation for main Timer. <1=> Disable <0=> Enable
//              <i> Update event is generation from counter overflow/underflow.
//          <o4.25> (TRGO) Timer TRGO output inverse enable bit. <0=> Disable <1=> Enable
//      </h>
//      <o5> Main counter range <0-255>
//      <o6> Prescaler counter range <0-255>
//  </e>
#define CONF_TM00_ENABLE_OPTION 0x00000001  
#define CONF_TM00_CLK           0x00000000  
#define CONF_TM00_CR0           0x00000000
#define CONF_TM00_CKO           0x00000008
#define CONF_TM00_TRG           0x00000000
#define CONF_TM00_ARR           199
#define CONF_TM00_PSARR         39

//  <e0.0> Configure TM01 Module
//      <h> Clock configuration
//          <o1.6..7> Main / Prescaler counter clock from <0=> Internal clock <3=> External Clock
//          <h> Internal Clock 
//              <o1.8..9> Internal Clock from <0=> PROC : CK_TM01_PR process clock from CSC <2=> CK_LS
//              <o1.12..13> Internal Clock divider <0=> DIV1 : divided by 1 <1=> DIV2 : divided by 2 <2=> DIV4 : divided by 4 <3=> DIV8 : divided by 8  
//          </h>
//          <h> External Clock
//              <o1.4..5> External Clock source from <0=> ETR (CK_ETR) <1=> ITR (CK_ITR)
//              <o4.8..10> ITR from <0=> ITR0 : TM16_TRGO <2=> ITR2 : CMP1_OUT <4=> ITR4 : INT_PC <5=> ITR5 : INT_PD <6=> ITR6  <7=> ITR7
//          </h>
//      </h>
//      <h> Timer operation mode
//          <o2.4..5> Operation mode (Up count) <0=> Cascade : 8-bit counter with 8-bit prescaler  Mode <1=> Separate : Separated two 8-bit counters Mode <2=> Full-Counter : 16-bit counter Mode
//          <o2.10..11> External trigger (EXF) <0=> Disable external trigger <1=> Enable external trigger <3=> Enable external invert trigger
//          <o2.15> Timer external trigger update event <0=> Disable <1=> Enable
//      </h>
//      <e3.0> ClockOut config
//          <o3.2..3> TM01 CKO initial state <2=> Output 0 <3=> Output 1
//          <o3.1> CKO event from <0=> Prescaler counter overflow <1=> Main counter overflow
//          <o2.8..9> Repeatability parameter <0=> Always clock out <1=> Only Output once cycle <3=> Repeatability output (Apply TRGI application)
//      </e>
//      <h> Trigger Input/Output config (TRGI & TRGO)
//          <o4.6..7> (TRGI) Timer trigger source from <0=> ETR <1=> ITR (source from Clock configuration)
//          <o4.0..2> (TRGI) Main counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.3..5> (TRGI) Prescaler counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.12..15> (TRGO) Timer trigger output mode select <0=> RST : TM01_RST (Main Timer Reset) <1=> EN : TM01_EN (Main Timer Enable) <2=> UEV : TM01_UEV (Main Timer Update event)
//                                                              <3=> TOF : TM01_TOF (Main Timer overflow) <5=> EN2 : TM01_EN2 (Timer-2 Enable) <6=> TOF2 :TM01_TOF2 (Timer-2 overflow)
//                                                              <8=> UEV2 : TM01_UEV2 (Timer-2 Update event) <9=> SW : TM01_TRGO_SW (software control bit) <14=> TRGI : TM01_TRGI (internal TRGI signal)
//          <o4.22..23> (TRGO) Timer UEV for <0=> All : output all UEV pulses <1=> TOF : output timer overflow pulses <2=> UDF : output timer underflow pulses
//          <o2.12> (UEV) Update event generation for main Timer. <1=> Disable <0=> Enable
//              <i> Update event is generation from counter overflow/underflow.
//          <o4.25> (TRGO) Timer TRGO output inverse enable bit. <0=> Disable <1=> Enable
//      </h>
//      <o5> Main counter range <0-255>
//      <o6> Prescaler counter range <0-255>
//  </e>
#define CONF_TM01_ENABLE_OPTION 0x00000001  
#define CONF_TM01_CLK           0x00000000  
#define CONF_TM01_CR0           0x00000000
#define CONF_TM01_CKO           0x00000008
#define CONF_TM01_TRG           0x00000000
#define CONF_TM01_ARR           47
#define CONF_TM01_PSARR         39

//  <e0.0> Configure TM10 Module
//      <h> Clock configuration
//          <o1.6..7> Main / Prescaler counter clock from <0=> Internal clock <3=> External Clock
//          <h> Internal Clock 
//              <o1.8..9> Internal Clock from <0=> PROC : CK_TM10_PR process clock from CSC <2=> CK_LS
//              <o1.12..13> Internal Clock divider <0=> DIV1 : divided by 1 <1=> DIV2 : divided by 2 <2=> DIV4 : divided by 4 <3=> DIV8 : divided by 8  
//          </h>
//          <h> External Clock
//              <o1.4..5> External Clock source from <0=> ETR (CK_ETR) <1=> ITR (CK_ITR)
//              <o4.8..10> ITR from <0=> ITR0 : TM00_TRGO <2=> ITR2 : CMP0_OUT <4=> ITR4 : INT_PA <5=> ITR5 : INT_PB <6=> ITR6  <7=> ITR7
//          </h>
//      </h>
//      <h> Timer operation mode
//          <o2.4..5> Operation mode (Up count) <0=> Cascade : 16-bit counter with 16-bit prescaler  Mode <1=> Separate : Separated two 16-bit counters Mode <2=> Full-Counter : 32-bit counter Mode
//          <o2.10..11> External trigger (EXF) <0=> Disable external trigger <1=> Enable external trigger <3=> Enable external invert trigger
//          <o2.15> Timer external trigger update event <0=> Disable <1=> Enable
//      </h>
//      <e3.0> ClockOut config
//          <o3.2..3> TM10 CKO initial state <2=> Output 0 <3=> Output 1
//          <o3.1> CKO event from <0=> Prescaler counter overflow <1=> Main counter overflow
//          <o2.8..9> Repeatability parameter <0=> Always clock out <1=> Only Output once cycle <3=> Repeatability output (Apply TRGI application)
//      </e>
//      <h> Trigger Input/Output config (TRGI & TRGO)
//          <o4.6..7> (TRGI) Timer trigger source from <0=> ETR <1=> ITR (source from Clock configuration)
//          <o4.0..2> (TRGI) Main counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.3..5> (TRGI) Prescaler counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.12..15> (TRGO) Timer trigger output mode select <0=> RST : TM10_RST (Main Timer Reset) <1=> EN : TM10_EN (Main Timer Enable) <2=> UEV : TM10_UEV (Main Timer Update event)
//                                                              <3=> TOF : TM10_TOF (Main Timer overflow) <5=> EN2 : TM10_EN2 (Timer-2 Enable) <6=> TOF2 :TM10_TOF2 (Timer-2 overflow)
//                                                              <8=> UEV2 : TM10_UEV2 (Timer-2 Update event) <9=> SW : TM10_TRGO_SW (software control bit) <14=> TRGI : TM10_TRGI (internal TRGI signal)
//          <o4.22..23> (TRGO) Timer UEV for <0=> All : output all UEV pulses <1=> TOF : output timer overflow pulses <2=> UDF : output timer underflow pulses
//          <o2.12> (UEV) Update event generation for main Timer. <1=> Disable <0=> Enable
//              <i> Update event is generation from counter overflow/underflow.
//          <o4.25> (TRGO) Timer TRGO output inverse enable bit. <0=> Disable <1=> Enable
//      </h>
//      <o5> Main counter range <0-65535>
//      <o6> Prescaler counter range <0-65535>
//  </e>
#define CONF_TM10_ENABLE_OPTION 0x00000001  
#define CONF_TM10_CLK           0x00000000  
#define CONF_TM10_CR0           0x00000000
#define CONF_TM10_CKO           0x00000008
#define CONF_TM10_TRG           0x00000000
#define CONF_TM10_ARR           9999
#define CONF_TM10_PSARR         7

//  <e0.0> Configure TM16 Module
//      <h> Clock configuration
//          <o1.6..7> Main / Prescaler counter clock from <0=> Internal clock <3=> External Clock
//          <h> Internal Clock 
//              <o1.8..9> Internal Clock from <0=> PROC : CK_TM16_PR process clock from CSC <2=> CK_LS
//              <o1.12..13> Internal Clock divider <0=> DIV1 : divided by 1 <1=> DIV2 : divided by 2 <2=> DIV4 : divided by 4 <3=> DIV8 : divided by 8  
//          </h>
//          <h> External Clock
//              <o1.4..5> External Clock source from <0=> ETR (CK_ETR) <1=> ITR (CK_ITR)
//              <o4.8..10> ITR from <0=> ITR0 : TM01_TRGO <2=> ITR2 : CMP1_OUT <4=> ITR4 : INT_PC <5=> ITR5 : INT_PD <6=> ITR6  <7=> ITR7
//          </h>
//      </h>
//      <h> Timer operation mode
//          <o2.4..5> Operation mode <0=> Cascade : 16-bit counter with 16-bit prescaler  Mode <1=> Separate : Separated two 16-bit counters Mode <2=> Full-Counter : 32-bit counter Mode
//          <o2.6..7> Up or down count <0=> Up count (Main & Prescaler counter) <3=> Down count (Main & Prescaler counter)
//          <o2.10..11> External trigger (EXF) <0=> Disable external trigger <1=> Enable external trigger <3=> Enable external invert trigger
//          <o2.15> Timer external trigger update event <0=> Disable <1=> Enable
//      </h>
//      <e3.0> ClockOut config
//          <o3.2..3> TM16 CKO initial state <2=> Output 0 <3=> Output 1
//          <o3.1> CKO event from <0=> Prescaler counter overflow <1=> Main counter overflow
//          <o2.8..9> Repeatability parameter <0=> Always clock out <1=> Only Output once cycle <3=> Repeatability output (Apply TRGI application)
//      </e>
//      <h> Trigger Input/Output config (TRGI & TRGO)
//          <o4.6..7> (TRGI) Timer trigger source from <0=> ETR <1=> ITR (source from Clock configuration)
//          <o4.0..2> (TRGI) Main counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.3..5> (TRGI) Prescaler counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.12..15> (TRGO) Timer trigger output mode select <0=> RST : TM16_RST (Main Timer Reset) <1=> EN : TM16_EN (Main Timer Enable) <2=> UEV : TM16_UEV (Main Timer Update event)
//                                                              <3=> TOF : TM16_TOF (Main Timer overflow) <4=> TUF : TM16_TUF (Main Timer underflow) 
//                                                              <5=> EN2 : TM16_EN2 (Timer-2 Enable) <6=> TOF2 :TM16_TOF2 (Timer-2 overflow)
//                                                              <7=> DIR : TM16_DIR (Main Timer direction event)
//                                                              <8=> UEV2 : TM16_UEV2 (Timer-2 Update event) <9=> SW : TM16_TRGO_SW (software control bit) <14=> TRGI : TM16_TRGI (internal TRGI signal)
//          <o4.22..23> (TRGO) Timer UEV for <0=> All : output all UEV pulses <1=> TOF : output timer overflow pulses <2=> UDF : output timer underflow pulses
//          <o2.12> (UEV) Update event generation for main Timer. <1=> Disable <0=> Enable
//              <i> Update event is generation from counter overflow/underflow.
//          <o4.25> (TRGO) Timer TRGO output inverse enable bit. <0=> Disable <1=> Enable
//      </h>
//      <o5> Main counter range <0-65535>
//      <o6> Prescaler counter range <0-65535>
//  </e>
#define CONF_TM16_ENABLE_OPTION 0x00000001  
#define CONF_TM16_CLK           0x00000000  
#define CONF_TM16_CR0           0x00000000
#define CONF_TM16_CKO           0x00000008
#define CONF_TM16_TRG           0x00000000
#define CONF_TM16_ARR           19999
#define CONF_TM16_PSARR         39


//  <e0.0> Configure TM36 Module
//      <h> Clock configuration
//          <o1.6..7> Main / Prescaler counter clock from <0=> Internal clock <3=> External Clock
//          <h> Internal Clock 
//              <o1.8..9> Internal Clock from <0=> PROC : CK_TM36_PR process clock from CSC <2=> CK_LS
//              <o1.12..13> Internal Clock divider <0=> DIV1 : divided by 1 <1=> DIV2 : divided by 2 <2=> DIV4 : divided by 4 <3=> DIV8 : divided by 8  
//          </h>
//          <h> External Clock
//              <o1.4..5> External Clock source from <0=> ETR (CK_ETR) <1=> ITR (CK_ITR) <2=> IN0 (TM36_IN0) <3=> IN1 (TM36_IN1)
//              <o4.8..10> ITR from <0=> ITR0 : TM10_TRGO  <2=> ITR2 : CMP0_OUT <3=> ITR3 : CMP1_OUT <4=> ITR4 : INT_PA <5=> ITR5 : INT_PC <6=> ITR6  <7=> ITR7
//          </h>
//      </h>
//      <h> Timer operation mode
//          <o2.4..5> Operation mode <0=> Cascade : 16-bit counter with 16-bit prescaler  Mode <1=> Separate : Separated two 16-bit counters Mode <2=> Full-Counter : 32-bit counter Mode
//          <o2.6..7> Up or down count <0=> Up count (Main & Prescaler counter) <3=> Down count (Main & Prescaler counter)
//          <o2.10..11> External trigger (EXF) <0=> Disable external trigger <1=> Enable external trigger <3=> Enable external invert trigger
//          <o2.15> Timer external trigger update event <0=> Disable <1=> Enable
//      </h>
//      <e3.0> ClockOut/OC/PWM configuration
//          <o3.2..3> TM36 CKO initial state <2=> Output 0 <3=> Output 1
//          <o3.1> CKO event from <0=> Prescaler counter overflow <1=> Main counter overflow
//      </e>
//      <e2.16> Rpetition Timer/Counter configuration (with TRGI trigger)
//          <o2.8..9> Repeatability parameter <0=> Always clock out <1=> Only Output once cycle <3=> Repeatability output (Apply TRGI application)
//          <o1.20> Repetition Timer/Counter clock source <0=> MAIN : clock input from Main timer overflow/underflow <1=> CKO : clock input from CK_CKOM 
//          <o2.17> Main Timer/Counter stop enable when repetition counter underflow. <0=> Disable <1=> Enable 
//          <o7.16..23> Repetition timer/counter auto-reload value register. <0-255>
//      </e>
//      <h> Trigger Input/Output configuration (TRGI & TRGO)
//          <o4.6..7> (TRGI) Timer trigger source from <0=> ETR <1=> ITR (source from Clock configuration) <2=> IN0 (TM36_IN0) <3=> IN1 (TM36_IN1)
//          <o4.0..2> (TRGI) Main counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.3..5> (TRGI) Prescaler counter trigger input mode <0=> No operation <1=> Trigger rising edge <2=> Reset rising edge <3=> Gate High <4=> Reset dual edge <5=> Trigger falling edge
//                                                           <6=> Reset falling edge <7=> Gate Low
//          <o4.12..15> (TRGO) Timer trigger output mode select <0=> RST : TM36_RST (Main Timer Reset) <1=> EN : TM36_EN (Main Timer Enable) <2=> UEV : TM36_UEV (Main Timer Update event)
//                                                              <3=> TOF : TM36_TOF (Main Timer overflow) <4=> TUF : TM36_TUF (Main Timer underflow)
//                                                              <5=> EN2 : TM36_EN2 (Timer-2 Enable) <6=> TOF2 :TM36_TOF2 (Timer-2 overflow)
//                                                              <7=> DIR : TM36_DIR (Main Timer direction event)
//                                                              <8=> UEV2 : TM36_UEV2 (Timer-2 Update event) <9=> SW : TM36_TRGO_SW (software control bit) 
//                                                              <10=> OS0 : TM36_OS0 (channel-0 output state signal) <11=> OS1 : TM36_OS1 (channel-1 output state signal)
//                                                              <12=> OS2 : TM36_OS2 (channel-2 output state signal) <13=> OS3 : TM36_OS3 (channel-3 output state signal)
//                                                              <14=> TRGI : TM36_TRGI (internal TRGI signal) <15=> POE : TM36_POE (Output enable register preload signal)
//          <o4.22..23> (TRGO) Timer UEV for <0=> All : output all UEV pulses <1=> TOF : output timer overflow pulses <2=> UDF : output timer underflow pulses
//          <o2.12> (UEV) Update event generation for main Timer. <1=> Disable <0=> Enable
//              <i> Update event is generation from counter overflow/underflow.
//          <o4.25> (TRGO) Timer TRGO output inverse enable bit. <0=> Disable <1=> Enable
//      </h>
//      <o5> Main counter range <0-65535>
//      <o6> Prescaler counter range <0-65535>
//      <h> QEI 
//          <i> TMx_ETR is QEI_IDX
//          <i> TMx_IN0 is QEI_DIR
//          <i> TMx_IN1 is QEI_CLK
//          <o4.16..18> QEI mode <0=> No operation (Disable QEI) <1=> N0POS : TM36_IN0 positive (high level up count, low level down count)
//                                                               <2=> IN0NEG : TM36_IN0 negative (low level up count, high level down count)
//                                                               <3=> IN0TRG : TM36_IN0 trigger (edge depending on TM36_IN1 level)
//                                                               <4=> IN1TRG : TM36_IN1 trigger (edge depending on TM36_IN0 level)
//                                                               <5=> BOTH : Both TM36_IN0 and TM36_IN1 edge
//          <e4.19> Main Timer QEI external index signal input. <0=> Disable <1=> Enable (Accept QEI IDX)
//              <o4.20..21> Main Timer QEI external index signal input reset timer transition state select. <0=> 1T2 : State change between 1 and 2
//                                                                                                          <1=> 2T3 : State change between 2 and 3
//                                                                                                          <2=> 3T4 : State change between 3 and 4
//                                                                                                          <3=> 4T1 : State change between 4 and 1
//          </e>
//      </h>
//      <h> Channel0 mode
//          <o8.0..2> Channel-0 function <0=> 0x0 = NOP (No operation) <1=> 16bit_IC (Input capture) <2=> 16bit_OC (Output compare) <3=> 8bitx2_OC (Two 8-bit compare)
//                                       <4=> 16bit_PWM (16bit PWM) <5=> 8bitx2_PWM (Two 8bit PWMs) <6=> 16bit_PWM_DTG (16bit PWM with DTG) <0x7=> 8bitx2_PWM_DTG (Two 8bit PWMs with DTG)
//          <o9.0..1> (IC) Timer channel 0 input Mux select for input capture. <0=> IC00 : TM36_IC0 <1=> IC01 : TM36_ITR <2=> IC02 : CMP0_OUT <3=> IC03 : TM36_XOR
//          <o9.16..17> (IC) Timer channel 0 input trigger edge select. <0=> Disable : disable capture data <1=> Rising edge <2=> Falling edge <3=> Dual-edge
//          <o10.0> (OUT) Timer channel 0 OC compare/compare-L output signal initial state. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o10.8> (OUT) Timer channel 0 OC compare-H output signal initial state for two 8-Bit comparator mode.. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o11.0> (OUT) Timer channel 0 OC line-0 OC00 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.1> (OUT) Timer channel 0 OC line-1 OC01 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.2> (OUT) Timer channel 0 OC line-2 OC02 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.16> (OUT) Timer channel 0 OC0N (complement) line output enable. <0=> Disable (output by TM36_BK0N_STA setting) <1=> Enable
//          <o12.0> (OUT) Timer channel 0 output inverse enable. <0=> Disable <1=> Enable
//          <o12.4> (OUT) Timer channel 0 OC0H output inverse enable. <0=> Disable <1=> Enable
//          <o12.8> (OUT) Timer channel 0 OC0N output inverse enable. <0=> Disable <1=> Enable
//          <o13.24> (OUT) Timer BK input active or stop condition output OC0 state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o13.28> (OUT) Timer BK input active or stop condition output OC0N state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o14.0..15> (OUT) CC0A, CC0B <0-65535>
//      </h>
//      <h> Channel1 mode
//          <o8.4..6> Channel-1 function <0=> 0x0 = NOP (No operation) <1=> 16bit_IC (Input capture) <2=> 16bit_OC (Output compare) <3=> 8bitx2_OC (Two 8-bit compare)
//                                       <4=> 16bit_PWM (16bit PWM) <5=> 8bitx2_PWM (Two 8bit PWMs) <6=> 16bit_PWM_DTG (16bit PWM with DTG) <0x7=> 8bitx2_PWM_DTG (Two 8bit PWMs with DTG)
//          <o9.4..5> (IC) Timer channel 1 input Mux select for input capture. <0=> IC00 : TM36_IC1 <1=> IC01 : TM36_ITR <2=> IC02 : CMP1_OUT 
//          <o9.18..19> (IC) Timer channel 1 input trigger edge select. <0=> Disable : disable capture data <1=> Rising edge <2=> Falling edge <3=> Dual-edge
//          <o10.1> (OUT) Timer channel 1 OC compare/compare-L output signal initial state. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o10.9> (OUT) Timer channel 1 OC compare-H output signal initial state for two 8-Bit comparator mode.. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o11.4> (OUT) Timer channel 1 OC line-0 OC10 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.5> (OUT) Timer channel 1 OC line-1 OC11 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.6> (OUT) Timer channel 1 OC line-2 OC12 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.20> (OUT) Timer channel 1 OC1N (complement) line output enable. <0=> Disable (output by TM36_BK0N_STA setting) <1=> Enable
//          <o12.1> (OUT) Timer channel 1 output inverse enable. <0=> Disable <1=> Enable
//          <o12.5> (OUT) Timer channel 1 OC1H output inverse enable. <0=> Disable <1=> Enable
//          <o12.9> (OUT) Timer channel 1 OC1N output inverse enable. <0=> Disable <1=> Enable
//          <o13.25> (OUT) Timer BK input active or stop condition output OC1 state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o13.29> (OUT) Timer BK input active or stop condition output OC1N state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o15.0..15> (OUT) CC1A, CC1B <0-65535>
//      </h>
//      <h> Channel2 mode
//          <o8.8..10> Channel-2 function <0=> 0x0 = NOP (No operation) <1=> 16bit_IC (Input capture) <2=> 16bit_OC (Output compare) <3=> 8bitx2_OC (Two 8-bit compare)
//                                       <4=> 16bit_PWM (16bit PWM) <5=> 8bitx2_PWM (Two 8bit PWMs) <6=> 16bit_PWM_DTG (16bit PWM with DTG) <0x7=> 8bitx2_PWM_DTG (Two 8bit PWMs with DTG)
//          <o9.8..9> (IC) Timer channel 2 input Mux select for input capture. <0=> IC00 : TM36_IC2 <1=> IC01 : TM36_ITR 
//          <o9.20..21> (IC) Timer channel 2 input trigger edge select. <0=> Disable : disable capture data <1=> Rising edge <2=> Falling edge <3=> Dual-edge
//          <o10.2> (OUT) Timer channel 2 OC compare/compare-L output signal initial state. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o10.10> (OUT) Timer channel 2 OC compare-H output signal initial state for two 8-Bit comparator mode.. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o11.8> (OUT) Timer channel 2 OC line-0 OC2 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o11.24> (OUT) Timer channel 2 OC2N (complement) line output enable. <0=> Disable (output by TM36_BK0N_STA setting) <1=> Enable
//          <o12.2> (OUT) Timer channel 2 output inverse enable. <0=> Disable <1=> Enable
//          <o12.6> (OUT) Timer channel 2 OC2H output inverse enable. <0=> Disable <1=> Enable
//          <o12.10> (OUT) Timer channel 2 OC2N output inverse enable. <0=> Disable <1=> Enable
//          <o13.26> (OUT) Timer BK input active or stop condition output OC2 state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o13.30> (OUT) Timer BK input active or stop condition output OC2N state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o16.0..15> (OUT) CC2A, CC2B <0-65535>
//      </h>
//      <h> Channel3 mode
//          <o8.12..14> Channel-3 function <0=> 0x0 = NOP (No operation) <1=> 16bit_IC (Input capture) <2=> 16bit_OC (Output compare) <3=> 8bitx2_OC (Two 8-bit compare)
//                                       <4=> 16bit_PWM (16bit PWM) <5=> 8bitx2_PWM (Two 8bit PWMs)
//          <o9.12..13> (IC) Timer channel 3 input Mux select for input capture. <0=> IC00 : TM36_IC3 <1=> IC01 : TM36_ITR <3=> IC03 : TM36_XOR
//          <o9.22..23> (IC) Timer channel 3 input trigger edge select. <0=> Disable : disable capture data <1=> Rising edge <2=> Falling edge <3=> Dual-edge
//          <o10.3> (OUT) Timer channel 3 OC compare/compare-L output signal initial state. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o10.11> (OUT) Timer channel 3 OC compare-H output signal initial state for two 8-Bit comparator mode.. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o11.12> (OUT) Timer channel 3 OC line-0 OC3 output enable. <0=> Disable (output by TM36_BK0_STA setting) <1=> Enable
//          <o12.3> (OUT) Timer channel 3 output inverse enable. <0=> Disable <1=> Enable
//          <o12.7> (OUT) Timer channel 3 OC3H output inverse enable. <0=> Disable <1=> Enable
//          <o13.27> (OUT) Timer BK input active or stop condition output OC3 state select. <0=> 0 (Output 0) <1=> 1 (Output 1)
//          <o17.0..15> (OUT) CC3A, CC3B <0-65535>
//      </h>
//      <h> Align / Dead time / Break control
//          <o18.0..1> Timer OC0/1/2/3 PWM mode select. <0=> Edge Left-aligned <1=> Center-aligned
//          <o1.16..17> Timer internal dead time clock CK_DTG divider. <0=> DIV1 : divided by 1 <1=> DIV2 : divided by 2 <3=> DIV4 : divided by 4 <4=> DIV8 : divided by 8
//          <o18.8..15> Timer output DTG dead-time delay for all channels. <0-255>
//          <o13.0..1> Timer Break Input enable for OC0/1/2/3. <0=> Disable <3=> Enable
//          <o13.4> Timer break control mode select. <0=> Latch mode <1=> Cycle by cycle
//          <o13.20..23> Timer OC0/1/2/3 output switch control when break event happened. <0=> Stop (Switch to stop state register setting) <15=> Hold (hold the output state)
//          <o13.8> Enable Break signal from TM36_BK0 input.
//          <o13.9> Enable Break signal from INT_BOD1 input.
//          <o13.10> Enable Break signal from INT_PB input.
//          <o13.11> Enable Break signal from ADC0_OUT input.
//          <o13.12> Enable Break signal from CMP0_OUT input.
//          <o13.13> Enable Break signal from CMP1_OUT input.
//          <o13.16> Enable Break signal from missing clock detect(MCD) event input.
//          <o13.18> Enable Break signal from  CPU LOCKUP event input.
//      </h>
//  </e>
#define CONF_TM36_ENABLE_OPTION 0x00000001  
#define CONF_TM36_CLK           0x00000000  
#define CONF_TM36_CR0           0x00000000
#define CONF_TM36_CKO           0x00000008
#define CONF_TM36_TRG           0x00000000
#define CONF_TM36_ARR           19999
#define CONF_TM36_PSARR         3
#define CONF_TM36_RCNT          0
#define CONF_TM36_CCMDS         0x00000000
#define CONF_TM36_ICCR          0x00000000
#define CONF_TM36_OSCR          0x00008080
#define CONF_TM36_OCCR0         0x00000000
#define CONF_TM36_OCCR1         0x00000000
#define CONF_TM36_BS            0x00000000
#define CONF_TM36_CC0A          0x00000000
#define CONF_TM36_CC1A          0x00000000
#define CONF_TM36_CC2A          0x00000000
#define CONF_TM36_CC3A          0x00000000
#define CONF_TM36_PWM           0x00000000



//*** <<< end of configuration section >>>    ***






/**
 * @name	Function announce
 *   		
 */
///@{  
void TM_Init (void);
///@}


#endif  // _MG32x02z_TM_INIT_H

