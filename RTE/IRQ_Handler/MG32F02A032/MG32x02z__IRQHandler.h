
/**
 ******************************************************************************
 *
 * @file        MG32x02z__IRQHandler.H
 *
 * @brief       This file contains all the functions prototypes for the IRQHandler
 *              firmware library.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.01
 * @date        2022/05/10
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
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

#ifndef __MG32x02z_IRQHANDLER_H
#define __MG32x02z_IRQHANDLER_H
#define __MG32x02z_IRQHANDLER_H_VER 100                     /*!< File Version */


#ifdef __cplusplus
 extern "C" {
#endif

/* Wizard menu ---------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void NMI_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WWDT_IRQHandler(void);
void SYS_IRQHandler(void);
void EXINT0_IRQHandler(void);
void EXINT1_IRQHandler(void);
void EXINT2_IRQHandler(void);
void EXINT3_IRQHandler(void);
void COMP_IRQHandler(void);
void DMA_IRQHandler(void);
void ADC_IRQHandler(void);
void DAC_IRQHandler(void);
void TM0x_IRQHandler(void);
void TM10_IRQHandler(void);
void TM1x_IRQHandler(void);
void TM20_IRQHandler(void);
void TM2x_IRQHandler(void);
void TM3x_IRQHandler(void);
void URT0_IRQHandler(void);
void URT123_IRQHandler(void);
void URT4x_IRQHandler(void);
void SPI0_IRQHandler(void);
void I2C0_IRQHandler(void);
void I2Cx_IRQHandler(void);
void USB_IRQHandler(void);
void APX_IRQHandler(void);

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/
extern void HardFault_IRQ(void);
extern void WWDT_IRQ(void);
extern void IWDT_IRQ(void);
extern void PW_IRQ(void);
extern void RTC_IRQ(void);
extern void CSC_IRQ(void);
extern void APB_IRQ(void);
extern void MEM_IRQ(void);
extern void EMB_IRQ(void);
extern void EXINT0_IRQ(void);
extern void EXINT1_IRQ(void);
extern void EXINT2_IRQ(void);
extern void EXINT3_IRQ(void);
extern void CMP_IRQ(void);
extern void DMA_IRQ(void);
extern void ADC_IRQ(void);
extern void DAC_IRQ(void);
extern void TM00_IRQ(void);
extern void TM01_IRQ(void);
extern void TM10_IRQ(void);
extern void TM16_IRQ(void);
extern void TM20_IRQ(void);
extern void TM26_IRQ(void);
extern void TM36_IRQ(void);
extern void URT0_IRQ(void);
extern void URT1_IRQ(void);
extern void URT2_IRQ(void);
extern void URT3_IRQ(void);
extern void URT4_IRQ(void);
extern void URT5_IRQ(void);
extern void URT6_IRQ(void);
extern void URT7_IRQ(void);
extern void SPI0_IRQ(void);
extern void I2C0_IRQ(void);
extern void I2C1_IRQ(void);
extern void RTC_IRQ(void);
extern void WWDT_IRQ(void);
extern void APX_IRQ(void);
extern void USB_IRQ(void);

#ifdef __cplusplus
}
#endif

#endif

