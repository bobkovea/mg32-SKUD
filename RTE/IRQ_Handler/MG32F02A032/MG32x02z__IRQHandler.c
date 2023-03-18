

/**
 ******************************************************************************
 *
 * @file        MG32x02z__IRQHandler.c
 * @brief       The demo IRQHandler C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.26
 * @date        2022/12/28
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


/* Wizard menu ---------------------------------------------------------------*/
/* USER CODE BEGIN Wizard */
// to do ...
/* USER CODE END Wizard */


/* Includes ------------------------------------------------------------------*/
#include "MG32x02z__IRQHandler.h"
#include "RTE_Components.h"
// include middleware support
#if defined(IRQHandler_Middleware_Level_)
    #include "MG32x02z_MID.h"
#endif
// include driver support
#if defined(IRQHandler_Driver_Level_)
    #include "MG32x02z_DRV.h"
#endif
// check Keil enviroment
#if !(defined(IRQHandler_Middleware_Level_) || defined(IRQHandler_Driver_Level_)) 
    #error "Please select 'Driver-All' or 'Middleware-All' option in Keil's Manage Run-Time Enviornent"
#endif


/* External vairables --------------------------------------------------------*/
#if defined(IRQHandler_Middleware_Level_)
	void MID_IncTick(void);             // (Middleware level) Please reference
                                        // "MG32x02z_Common_MID.c" file in 'Driver' option.
#else
	void IncTick(void);                 // (Driver level) Please reference
                                        // "MG32x02z__Common_DRV.c" file in 'Driver' option.
#endif
/* USER CODE BEGIN Private vairables */
// to do ...
/* USER CODE END Private vairables */


/* Exported variables --------------------------------------------------------*/
/* USER CODE BEGIN Private variables */
// to do ...
/* USER CODE END Private variables */


/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN Private functions */
// to do ...
/* USER CODE END Private functions */


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN Private typedef */
// to do ...
/* USER CODE END Private typedef */


/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Private define */
// to do ...
/* USER CODE END Private define */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Private macro */
// to do ...
/* USER CODE END Private macro */


/* Private variables ---------------------------------------------------------*/
// (Middleware level)
#if defined(IRQHandler_Middleware_Level_)       
    #if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wmissing-variable-declarations"
            __weak MID_OBMx_HandleTypeDef   mOBMx;
            __weak ADC_HandleTypeDef        mADC;
            __weak DMA_HandleTypeDef        mDMA;
            __weak TM_HandleTypeDef         mTM00;
            __weak TM_HandleTypeDef         mTM01;
            __weak TM_HandleTypeDef         mTM10;
            __weak TM_HandleTypeDef         mTM16;
            __weak TM_HandleTypeDef         mTM20;
            __weak TM_HandleTypeDef         mTM26;
            __weak TM_HandleTypeDef         mTM36;
            __weak RTC_HandleTypeDef        mRTC;
            __weak IWDT_HandleTypeDef       mIWDT;
            __weak URT_HandleTypeDef        mURT0;
            __weak URT_HandleTypeDef        mURT1;
            __weak URT_HandleTypeDef        mURT2;
            __weak URT_HandleTypeDef        mURT3;
            __weak SPI_HandleTypeDef        mUSPI0;
            __weak SPI_HandleTypeDef        mUSPI1;
            __weak SPI_HandleTypeDef        mUSPI2;
            __weak SPI_HandleTypeDef        mUSPI3;
            __weak URT_HandleTypeDef        mURT4;
            __weak URT_HandleTypeDef        mURT5;
            __weak URT_HandleTypeDef        mURT6;
            __weak URT_HandleTypeDef        mURT7;
            __weak SPI_HandleTypeDef        mSPI0;
            __weak WWDT_HandleTypeDef       mWWDT;
            __weak EXIC_HandleTypeDef       mEXIC_PA;
            __weak EXIC_HandleTypeDef       mEXIC_PB;
            __weak EXIC_HandleTypeDef       mEXIC_PC;
            __weak EXIC_HandleTypeDef       mEXIC_PD;
            __weak I2C_HandleTypeDef        mI2C0;
            __weak I2C_HandleTypeDef        mI2C1;
            // ----------------------------------------------------------------
            #if !defined(MG32_4TH)
                __weak CMP_HandleTypeDef    mCMP;
            #endif
            // ----------------------------------------------------------------
            #if defined(MG32_1ST) || defined(MG32_3RD)
                __weak EMB_HandleTypeDef    mEMB;
            #endif
            // ----------------------------------------------------------------
            #if !(defined(MG32_2ND) || defined(MG32_4TH))
                __weak DAC_HandleTypeDef    mDAC;
            #endif
            // ----------------------------------------------------------------
            #if defined(MG32_3RD) || defined(MG32_4TH)
                __weak CCL_HandleTypeDef    mCCL0;
                __weak CCL_HandleTypeDef    mCCL1;
            #endif
            // ----------------------------------------------------------------
        #pragma clang diagnostic pop
    // ------------------------------------------------------------------------
    #else
        __weak MID_OBMx_HandleTypeDef   mOBMx;
        __weak ADC_HandleTypeDef        mADC;
        __weak DMA_HandleTypeDef        mDMA;
        __weak TM_HandleTypeDef         mTM00;
        __weak TM_HandleTypeDef         mTM01;
        __weak TM_HandleTypeDef         mTM10;
        __weak TM_HandleTypeDef         mTM16;
        __weak TM_HandleTypeDef         mTM20;
        __weak TM_HandleTypeDef         mTM26;
        __weak TM_HandleTypeDef         mTM36;
        __weak RTC_HandleTypeDef        mRTC;
        __weak IWDT_HandleTypeDef       mIWDT;
        __weak URT_HandleTypeDef        mURT0;
        __weak URT_HandleTypeDef        mURT1;
        __weak URT_HandleTypeDef        mURT2;
        __weak URT_HandleTypeDef        mURT3;
        __weak SPI_HandleTypeDef        mUSPI0;
        __weak SPI_HandleTypeDef        mUSPI1;
        __weak SPI_HandleTypeDef        mUSPI2;
        __weak SPI_HandleTypeDef        mUSPI3;
        __weak URT_HandleTypeDef        mURT4;
        __weak URT_HandleTypeDef        mURT5;
        __weak URT_HandleTypeDef        mURT6;
        __weak URT_HandleTypeDef        mURT7;
        __weak SPI_HandleTypeDef        mSPI0;
        __weak WWDT_HandleTypeDef       mWWDT;
        __weak EXIC_HandleTypeDef       mEXIC_PA;
        __weak EXIC_HandleTypeDef       mEXIC_PB;
        __weak EXIC_HandleTypeDef       mEXIC_PC;
        __weak EXIC_HandleTypeDef       mEXIC_PD;
        __weak I2C_HandleTypeDef        mI2C0;
        __weak I2C_HandleTypeDef        mI2C1;
        // --------------------------------------------------------------------
        #if !(defined(MG32_4TH))
            __weak CMP_HandleTypeDef    mCMP;
        #endif
        // --------------------------------------------------------------------
        #if defined(MG32_1ST) || defined(MG32_3RD)
            __weak EMB_HandleTypeDef    mEMB;
        #endif
        // --------------------------------------------------------------------
        #if defined(MG32_1ST) || defined(MG32_3RD)
            __weak DAC_HandleTypeDef    mDAC;
        #endif
        // --------------------------------------------------------------------
        #if defined(MG32_3RD) || defined(MG32_4TH)
            __weak CCL_HandleTypeDef    mCCL0;
            __weak CCL_HandleTypeDef    mCCL1;
        #endif
        // --------------------------------------------------------------------
    #endif
    // ------------------------------------------------------------------------

#endif

/* USER CODE BEGIN Private variables */
// to do ...
/* USER CODE END Private variables */


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN Private prototypes */
// to do ...
/* USER CODE END Private prototypes */
__weak void I2C_Timeout_Handler(I2C_Struct* I2Cx);
__weak void I2C_ByteMode_Event_Handler(I2C_Struct* I2Cx);


/**
 *******************************************************************************
 * @brief       An NMI can be signalled by a peripheral or triggered by software. 
 *              This is the highest priority exception other than reset.
 * @return      No
 *******************************************************************************
 */
void NMI_Handler(void)
{
    /* USER CODE BEGIN NonMaskableInt_IRQ 0 */
    // to do...
    /* USER CODE END NonMaskableInt_IRQ 0 */

    /* USER CODE BEGIN NonMaskableInt_IRQ 1 */
    // to do...
    /* USER CODE END NonMaskableInt_IRQ 1 */
}

/**
 *******************************************************************************
 * @brief       A supervisor call (SVC) is an exception that is triggered by the 
 *              SVC instruction. In an OS environment, applications can use SVC 
 *              instructions to access OS kernel functions and device drivers.
 * @return      No
 *******************************************************************************
 */
void SVC_Handler(void)
{
    /* USER CODE BEGIN SVC_IRQ 0 */
    // to do...
    /* USER CODE END SVC_IRQ 0 */

    /* USER CODE BEGIN SVC_IRQ 1 */
    // to do...
    /* USER CODE END SVC_IRQ 1 */
}

/**
 *******************************************************************************
 * @brief       PendSV is an interrupt-driven request for system-level service. 
 *              In an OS environment, use PendSV for context switching when no 
 *              other exception is active.
 * @return      No
 *******************************************************************************
 */
void PendSV_Handler(void)
{
    /* USER CODE BEGIN PendSV_IRQ 0 */
    // to do...
    /* USER CODE END PendSV_IRQ 0 */

    /* USER CODE BEGIN PendSV_IRQ 1 */
    // to do...
    /* USER CODE END PendSV_IRQ 1 */
}

/**
 *******************************************************************************
 * @brief       If the device implements the SysTick timer, a SysTick exception 
 *              is an exception the system timer generates when it reaches zero. 
 *              Software can also generate a SysTick exception. In an OS 
 *              environment, the device can use this exception as system tick.
 * @return      No
 *******************************************************************************
 */
void SysTick_Handler(void)
{
    // ------------------------------------------------------------------------
    // SysTick ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN SysTick_IRQ 0 */
    // to do...
    /* USER CODE END SysTick_IRQ 0 */
    
    #if defined(IRQHandler_Middleware_Level_)
        MID_IncTick(); 
    #else
        IncTick();
    #endif

    /* USER CODE BEGIN SysTick_IRQ 1 */
    // to do...
    /* USER CODE END SysTick_IRQ 1 */
}

/**
 *******************************************************************************
 * @brief       WWDT: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_WWDT_IRQ_)
void WWDT_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // WWDT ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN WWDG_IRQ 0 */
    // to do...
    /* USER CODE END WWDG_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_WWDT_IRQHandler(&mWWDT);
    #else
        /*
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function WWDT_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        WWDT_IRQ();
    #endif

    /* USER CODE BEGIN WWDG_IRQ 1 */
    // to do...
    /* USER CODE END WWDG_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       SYS: An interrupt, or IRQ, is an exception signalled by a
 *              peripheral, or generated by a software request. 
 * @details     SYS_IRQ hava IWDT, PW, RTC, CSC, APB,MEM or EMB interrupt source.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_SYS_IRQ_)
void SYS_IRQHandler(void)
{
    /* USER CODE BEGIN SYS_IRQ 0 */
    // to do...
    /* USER CODE END SYS_IRQ 0 */

    // ------------------------------------------------------------------------
    // IWDT ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_iwdt_b1)
    {
        /* USER CODE BEGIN IWDT_IRQ 0 */
        // to do...
        /* USER CODE END IWDT_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
            MID_IWDT_IRQHandler(&mIWDT);
        #else
            /*
             NOTE : This function should not be modified. When the IRQ handler is needed, 
                    function IWDT_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            IWDT_IRQ();
        #endif

        /* USER CODE BEGIN IWDT_IRQ 1 */
        // to do...
        /* USER CODE END IWDT_IRQ 1 */
    }
    // ------------------------------------------------------------------------
    // PW ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_pw_b1)
    {
        /* USER CODE BEGIN PW_IRQ 0 */
        // to do...
        /* USER CODE END PW_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
            MID_PW_IRQHandler();
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function PW_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            PW_IRQ();
        #endif

        /* USER CODE BEGIN PW_IRQ 1 */
        // to do...
        /* USER CODE END PW_IRQ 1 */
    }
    // ------------------------------------------------------------------------
    // RTC ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_rtc_b1)
    {
        /* USER CODE BEGIN RTC_IRQ 0 */
        // to do...
        /* USER CODE END RTC_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
                MID_RTC_IRQHandler(&mRTC);
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function RTC_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            RTC_IRQ();
        #endif

        /* USER CODE BEGIN RTC_IRQ 1 */
        // to do...
        /* USER CODE END RTC_IRQ 1 */
    }
    // ------------------------------------------------------------------------
    // CSC ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_csc_b1)
    {
        /* USER CODE BEGIN CSC_IRQ 0 */
        // to do...
        /* USER CODE END CSC_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
                MID_CSC_IRQHandler();
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function CSC_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            CSC_IRQ();
        #endif

        /* USER CODE BEGIN CSC_IRQ 1 */
        // to do...
        /* USER CODE END CSC_IRQ 1 */
    }
    // ------------------------------------------------------------------------
    // APB ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_apb_b1)
    {
        /* USER CODE BEGIN APB_IRQ 0 */
        // to do...
        /* USER CODE END APB_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
            #if defined(MG32_1ST)
            if(__DRV_APB_GET_IT_SOURCE(APB_IT_OBM1))
                    MID_OBMx_IRQHandler(&mOBMx);
            #endif
            #if defined(MG32_2ND)
            if((__DRV_APB_GET_IT_SOURCE(APB_IT_OBM0)) || (__DRV_APB_GET_IT_SOURCE(APB_IT_OBM1)))
                    MID_OBMx_IRQHandler(&mOBMx);
            #endif
            #if defined(MG32_3RD) || defined(MG32_4TH) 
            if((__DRV_APB_GET_IT_SOURCE(APB_IT_OBM0)) || (__DRV_APB_GET_IT_SOURCE(APB_IT_OBM1)))
                    MID_OBMx_IRQHandler(&mOBMx);
            else
                    MID_NCO_IRQHandler();
            #endif
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function APB_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            APB_IRQ();
        #endif

        /* USER CODE BEGIN APB_IRQ 1 */
        // to do...
        /* USER CODE END APB_IRQ 1 */
    }
    // ------------------------------------------------------------------------
    // MEM ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_mem_b1)
    {
        /* USER CODE BEGIN MEM_IRQ 0 */
        // to do...
        /* USER CODE END MEM_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
            MID_MEM_IRQHandler();
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function MEM_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            MEM_IRQ();
        #endif

        /* USER CODE BEGIN MEM_IRQ 1 */
        // to do...
        /* USER CODE END MEM_IRQ 1 */
    }
    // ------------------------------------------------------------------------
    // EMB ISR
    // ------------------------------------------------------------------------
    #if defined EMB_Base
        if(__DRV_EXIC_GET_ID1_SOURCE() & EXIC_SRC0_ID1_emb_b1)
        {
            /* USER CODE BEGIN EMB_IRQ 0 */
            // to do...
            /* USER CODE END EMB_IRQ 0 */
            #if defined(IRQHandler_Middleware_Level_)
                    MID_EMB_IRQHandler(&mEMB);
            #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function EMB_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
                    EMB_IRQ();
            #endif

            /* USER CODE BEGIN EMB_IRQ 1 */
            // to do...
            /* USER CODE END EMB_IRQ 1 */
        }
    #endif
    
    /* USER CODE BEGIN SYS_IRQ 1 */
    // to do...
    /* USER CODE END SYS_IRQ 1 */

}

#endif

/**
 *******************************************************************************
 * @brief       EXINT0: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request.
 * @details     EXINT0 handles port PA external interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_EXINT0_IRQ_)
void EXINT0_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // EXINT0 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN EXINT0_IRQ 0 */
    // to do...
    /* USER CODE END EXINT0_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_EXIC_IRQHandler(&mEXIC_PA);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function EXINT0_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        EXINT0_IRQ();
    #endif

    /* USER CODE BEGIN EXINT0_IRQ 1 */
    // to do...
    /* USER CODE END EXINT0_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       EXINT1: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request.
 * @details     EXINT1 handles port PB external interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_EXINT1_IRQ_)
void EXINT1_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // EXINT1 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN EXINT1_IRQ 0 */
    // to do...
    /* USER CODE END EXINT1_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_EXIC_IRQHandler(&mEXIC_PB);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function EXINT1_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        EXINT1_IRQ();
    #endif

    /* USER CODE BEGIN EXINT1_IRQ 1 */
    // to do...
    /* USER CODE END EXINT1_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       EXINT2: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     EXINT2 handles port PC external interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_EXINT2_IRQ_)
void EXINT2_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // EXINT2 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN EXINT2_IRQ 0 */
    // to do...
    /* USER CODE END EXINT2_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_EXIC_IRQHandler(&mEXIC_PC);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function EXINT2_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        EXINT2_IRQ();
    #endif

    /* USER CODE BEGIN EXINT2_IRQ 1 */
    // to do...
    /* USER CODE END EXINT2_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       EXINT3: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     EXINT3 handles port PD external interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_EXINT3_IRQ_)
void EXINT3_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // EXINT3 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN EXINT3_IRQ 0 */
    // to do...
    /* USER CODE END EXINT3_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_EXIC_IRQHandler(&mEXIC_PD);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function EXINT3_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        EXINT3_IRQ();
    #endif

    /* USER CODE BEGIN EXINT3_IRQ 1 */
    // to do...
    /* USER CODE END EXINT3_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       COMP: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     COMP handles port CMP0~3 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_COMP_IRQ_)
void COMP_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // COMP ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN COMP_IRQ 0 */
    // to do...
    /* USER CODE END COMP_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_CMP_IRQHandler(&mCMP);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function COMP_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        CMP_IRQ();
    #endif

    /* USER CODE BEGIN COMP_IRQ 1 */
    // to do...
    /* USER CODE END COMP_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       DMA: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_DMA_IRQ_)
void DMA_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // DMA ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN DMA_IRQ 0 */
    // to do...
    /* USER CODE END DMA_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_DMA_IRQHandler(&mDMA);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function DMA_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        DMA_IRQ();
    #endif

    /* USER CODE BEGIN DMA_IRQ 1 */
    // to do...
    /* USER CODE END DMA_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       ADC: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_ADC_IRQ_)
void ADC_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // ADC ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN ADC_IRQ 0 */
    // to do...
    /* USER CODE END ADC_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_ADC_IRQHandler(&mADC);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function ADC_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        ADC_IRQ();
    #endif

    /* USER CODE BEGIN ADC_IRQ 1 */
    // to do...
    /* USER CODE END ADC_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       DAC: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_DAC_IRQ_)
void DAC_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // DAC ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN DAC_IRQ 0 */
    // to do...
    /* USER CODE END DAC_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_DAC_IRQHandler(&mDAC);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function DAC_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        DAC_IRQ();
    #endif

    /* USER CODE BEGIN DAC_IRQ 1 */
    // to do...
    /* USER CODE END DAC_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       TM0x: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     TM0x handles port TM00 or TM01 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_TM0x_IRQ_)
void TM0x_IRQHandler(void)
{
    /* USER CODE BEGIN TM0x_IRQ 0 */
    // to do...
    /* USER CODE END TM0x_IRQ 0 */

    // ------------------------------------------------------------------------
    // TM00 ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm00_b0 )
    {
        /* USER CODE BEGIN TM00_IRQ 0 */
        // to do...
        /* USER CODE END TM00_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
                MID_TM_IRQHandler(&mTM00);
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function TM00_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            TM00_IRQ();
        #endif

        /* USER CODE BEGIN TM00_IRQ 1 */
        // to do...
        /* USER CODE END TM00_IRQ 1 */
    }

    // ------------------------------------------------------------------------
    // TM01 ISR
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm01_b0)
    {
        /* USER CODE BEGIN TM01_IRQ 0 */
        // to do...
        /* USER CODE END TM01_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
                MID_TM_IRQHandler(&mTM01);
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function TM01_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
                TM01_IRQ();
        #endif

        /* USER CODE BEGIN TM01_IRQ 1 */
        // to do...
        /* USER CODE END TM01_IRQ 1 */
    }

    /* USER CODE BEGIN TM0x_IRQ 1 */
    // to do...
    /* USER CODE END TM0x_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       TM10: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_TM10_IRQ_)
void TM10_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // TM10 ISR 
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN TM10_IRQ 0 */
    // to do...
    /* USER CODE END TM10_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_TM_IRQHandler(&mTM10);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function TM10_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        TM10_IRQ();
    #endif

    /* USER CODE BEGIN TM10_IRQ 1 */
    // to do...
    /* USER CODE END TM10_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       TM1x: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     TM1x handles port TM16 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_TM1x_IRQ_)
void TM1x_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // TM16 ISR 
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN TM16_IRQ 0 */
    // to do...
    /* USER CODE END TM16_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_TM_IRQHandler(&mTM16);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function TM16_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers. 
        */
        TM16_IRQ();
    #endif
    
    /* USER CODE BEGIN TM16_IRQ 1 */
    // to do...
    /* USER CODE END TM16_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       TM20: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_TM20_IRQ_)
void TM20_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // TM20 ISR 
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN TM20_IRQ 0 */
    // to do...
    /* USER CODE END TM20_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_TM_IRQHandler(&mTM20);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function TM20_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        TM20_IRQ();
    #endif
    
    /* USER CODE BEGIN TM20_IRQ 1 */
    // to do...
    /* USER CODE END TM20_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       TM2x: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     TM2x handles port TM26 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_TM2x_IRQ_)
void TM2x_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // TM26 ISR 
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN TM26_IRQ 0 */
    // to do...
    /* USER CODE END TM26_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_TM_IRQHandler(&mTM26);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function TM26_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        TM26_IRQ();
    #endif
    
    /* USER CODE BEGIN TM26_IRQ 1 */
    // to do...
    /* USER CODE END TM26_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       TM3x: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     TM3x handles port TM36 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_TM3x_IRQ_)
void TM3x_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // TM36 ISR 
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN TM36_IRQ 0 */
    // to do...
    /* USER CODE END TM36_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_TM_IRQHandler(&mTM36);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function TM36_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers. 
        */
        TM36_IRQ();
    #endif
    
    /* USER CODE BEGIN TM36_IRQ 1 */
    // to do...
    /* USER CODE END TM36_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       URT0: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_URT0_IRQ_)
void URT0_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // URT0 ISR 
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN URT0_IRQ 0 */
    // to do...
    /* USER CODE END URT0_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        if(IS_URT_SPIMODE(URT0)==SET)
        {
            MID_SPI_IRQHandler(&mUSPI0);
        }
        else
        {
            MID_URT_IRQHandler(&mURT0);
        }
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function URT0_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        URT0_IRQ();
    #endif
    
    /* USER CODE BEGIN URT0_IRQ 1 */
    // to do...
    /* USER CODE END URT0_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       URT123: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     URT123 handles port URT1, URT2 or URT3 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_URT123_IRQ_)
void URT123_IRQHandler(void)
{
    /* USER CODE BEGIN URT123_IRQ 0 */
    // to do...
    /* USER CODE END URT123_IRQ 0 */
    
    // ------------------------------------------------------------------------
    // URT1 ISR 
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_1ST : MG32F02A132, MG32F02A072, MA862
    //  MG32_2ND : MG32F02A032
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    //  MG32_4TH : MG32F02V032
    // ------------------------------------------------------------------------
    #if defined URT1_Base
                if(__DRV_EXIC_GET_ID21_SOURCE() & EXIC_SRC5_ID21_urt1_b1)
                {
                        /* USER CODE BEGIN URT1_IRQ 0 */
                        // to do...
                        /* USER CODE END URT1_IRQ 0 */
                        #if defined(IRQHandler_Middleware_Level_)
                                if(IS_URT_SPIMODE(URT1)==SET)
                                {
                                        MID_SPI_IRQHandler(&mUSPI1);
                                }
                                else
                                { 
                                        MID_URT_IRQHandler(&mURT1);
                                }
                        #else
                                /* 
                                NOTE : This function should not be modified. When the IRQ handler is needed,
                                                function URT1_IRQ must be implemented in the user file.
                                                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
                                */
                                URT1_IRQ();
                        #endif
                        
                        /* USER CODE BEGIN URT1_IRQ 1 */
                        // to do...
                        /* USER CODE END URT1_IRQ 1 */
                }
        #endif
    // ------------------------------------------------------------------------
    // URT2 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_1ST : MG32F02A132, MG32F02A072, MA862
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    // ------------------------------------------------------------------------
    #if defined URT2_Base
                if(__DRV_EXIC_GET_ID21_SOURCE() & EXIC_SRC5_ID21_urt2_b1)
                {
                        /* USER CODE BEGIN URT2_IRQ 0 */
                        // to do...
                        /* USER CODE END URT2_IRQ 0 */
                        #if defined(IRQHandler_Middleware_Level_)
                                if(IS_URT_SPIMODE(URT2)==SET)
                                {
                                        MID_SPI_IRQHandler(&mUSPI2);
                                }
                                else
                                { 
                                        MID_URT_IRQHandler(&mURT2);
                                } 
                        #else
                                /* 
                                NOTE : This function should not be modified. When the IRQ handler is needed,
                                                function URT2_IRQ must be implemented in the user file.
                                                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
                                */
                                URT2_IRQ();
                        #endif
                        
                        /* USER CODE BEGIN URT2_IRQ 1 */
                        // to do...
                        /* USER CODE END URT2_IRQ 1 */
                }
        #endif
    // ------------------------------------------------------------------------
    // URT3 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_1ST : MG32F02A132, MG32F02A072, MA862
    // ------------------------------------------------------------------------
    #if defined URT3_Base
        if(__DRV_EXIC_GET_ID21_SOURCE() & EXIC_SRC5_ID21_urt3_b1)
        {
            /* USER CODE BEGIN URT3_IRQ 0 */
            // to do...
            /* USER CODE END URT3_IRQ 0 */
            #if defined(IRQHandler_Middleware_Level_)
                if(IS_URT_SPIMODE(URT3)==SET)
                {
                    MID_SPI_IRQHandler(&mUSPI3);
                }
                else
                { 
                    MID_URT_IRQHandler(&mURT3);
                }
            #else
                /* 
                NOTE : This function should not be modified. When the IRQ handler is needed,
                        function URT3_IRQ must be implemented in the user file.
                        Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
                */
                URT3_IRQ();
            #endif
            
            /* USER CODE BEGIN URT3_IRQ 1 */
            // to do...
            /* USER CODE END URT3_IRQ 1 */
        }
    #endif
    
    /* USER CODE BEGIN URT123_IRQ 1 */
    // to do...
    /* USER CODE END URT123_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       URT4x: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     URT4x handles port URT4, URT5, URT6 or URT7 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_URT4x_IRQ_)
void URT4x_IRQHandler(void)
{
    /* USER CODE BEGIN URT4x_IRQ 0 */
    // to do...
    /* USER CODE END URT4x_IRQ 0 */

    // ------------------------------------------------------------------------
    // URT4 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    //  MG32_4TH : MG32F02V032
    // ------------------------------------------------------------------------
    if(__DRV_EXIC_GET_ID22_SOURCE() & EXIC_SRC5_ID22_urt4_b2)
    {
        /* USER CODE BEGIN URT4_IRQ 0 */
        // to do...
        /* USER CODE END URT4_IRQ 0 */
        #if defined(IRQHandler_Middleware_Level_)
            MID_URT_IRQHandler(&mURT4);
        #else
            /* 
             NOTE : This function should not be modified. When the IRQ handler is needed,
                    function URT4_IRQ must be implemented in the user file.
                    Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
            */
            URT4_IRQ();
        #endif
        
        /* USER CODE BEGIN URT4_IRQ 1 */
        // to do...
        /* USER CODE END URT4_IRQ 1 */
    }

    // ------------------------------------------------------------------------
    // URT5 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    // ------------------------------------------------------------------------
    #if defined URT5_Base
        if( __DRV_EXIC_GET_ID22_SOURCE() & EXIC_SRC5_ID22_urt5_b2)
        {
            /* USER CODE BEGIN URT5_IRQ 0 */
            // to do...
            /* USER CODE END URT5_IRQ 0 */
            #if defined(IRQHandler_Middleware_Level_)
                MID_URT_IRQHandler(&mURT5);
            #else
                /* 
                 NOTE : This function should not be modified. When the IRQ handler is needed,
                        function URT5_IRQ must be implemented in the user file.
                        Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
                */
                URT5_IRQ();
            #endif
            
            /* USER CODE BEGIN URT5_IRQ 1 */
            // to do...
            /* USER CODE END URT5_IRQ 1 */
        }
    #endif
    // ------------------------------------------------------------------------
    // URT6 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    // ------------------------------------------------------------------------
    #if defined URT6_Base
        if( __DRV_EXIC_GET_ID22_SOURCE() & EXIC_SRC5_ID22_urt6_b2)
        {
            /* USER CODE BEGIN URT6_IRQ 0 */
            // to do...
            /* USER CODE END URT6_IRQ 0 */
            #if defined(IRQHandler_Middleware_Level_)
                MID_URT_IRQHandler(&mURT6);
            #else
                /* 
                 NOTE : This function should not be modified. When the IRQ handler is needed,
                        function URT6_IRQ must be implemented in the user file.
                        Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
                */
                URT6_IRQ();
            #endif
            
            /* USER CODE BEGIN URT6_IRQ 1 */
            // to do...
            /* USER CODE END URT6_IRQ 1 */
        }
    #endif
    // ------------------------------------------------------------------------
    // URT7 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    // ------------------------------------------------------------------------
    #if defined URT7_Base
        if( __DRV_EXIC_GET_ID22_SOURCE() & EXIC_SRC5_ID22_urt7_b2)
        {
            /* USER CODE BEGIN URT7_IRQ 0 */
            // to do...
            /* USER CODE END URT7_IRQ 0 */
            #if defined(IRQHandler_Middleware_Level_)
                MID_URT_IRQHandler(&mURT7);
            #else
                /* 
                 NOTE : This function should not be modified. When the IRQ handler is needed,
                        function URT7_IRQ must be implemented in the user file.
                        Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
                */
                URT7_IRQ();
            #endif
            
            /* USER CODE BEGIN URT7_IRQ 1 */
            // to do...
            /* USER CODE END URT7_IRQ 1 */
        }
    #endif
    
    /* USER CODE BEGIN URT4x_IRQ 1 */
    // to do...
    /* USER CODE END URT4x_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       SPI0: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_SPI0_IRQ_)
void SPI0_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // SPI0 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN SPI0_IRQ 0 */
    // to do...
    /* USER CODE END SPI0_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_SPI_IRQHandler(&mSPI0);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function SPI0_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        SPI0_IRQ();
    #endif
    
    /* USER CODE BEGIN SPI0_IRQ 1 */
    // to do...
    /* USER CODE END SPI0_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       I2C0: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_I2C0_IRQ_)
void I2C0_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // I2C0 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN I2C0_IRQ 0 */
    // to do...
    /* USER CODE END I2C0_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_I2C_IRQHandler(&mI2C0);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function I2C0_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        I2C0_IRQ();
    #endif
    
    /* USER CODE BEGIN I2C0_IRQ 1 */
    // to do...
    /* USER CODE END I2C0_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       I2Cx: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     I2Cx handles port I2C1 interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_I2Cx_IRQ_)
void I2Cx_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // I2C1 ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN I2C1_IRQ 0 */
    // to do...
    /* USER CODE END I2C1_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        MID_I2C_IRQHandler(&mI2C1);
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function I2C1_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        I2C1_IRQ();
    #endif
    
    /* USER CODE BEGIN I2C1_IRQ 1 */
    // to do...
    /* USER CODE END I2C1_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief       USB: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_USB_IRQ_)
void USB_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // USB ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN USB_IRQ 0 */
    // to do...
    /* USER CODE END USB_IRQ 0 */
    /* 
     NOTE : This function should not be modified. When the IRQ handler is needed,
            function USB_IRQ must be implemented in the user file.
            Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
    */
    USB_IRQ();
    
    /* USER CODE BEGIN USB_IRQ 1 */
    // to do...
    /* USER CODE END USB_IRQ 1 */
}

#endif

/**
 *******************************************************************************
 * @brief       APX: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     APX handles port ASB or CCLx interrupt.
 * @return      No
 *******************************************************************************
 */
#if defined(MG32x02z_APX_IRQ_)
void APX_IRQHandler(void)
{
    // ------------------------------------------------------------------------
    // APX ISR
    // ------------------------------------------------------------------------
    /* USER CODE BEGIN APX_IRQ 0 */
    // to do...
    /* USER CODE END APX_IRQ 0 */
    #if defined(IRQHandler_Middleware_Level_)
        if((__DRV_APX_GET_IT_SOURCE(APX_IT_CCL0)))
        {
            MID_APX_CCL_IRQHandler(&mCCL0);
        }
        else if ((__DRV_APX_GET_IT_SOURCE(APX_IT_CCL1)))
        {
            MID_APX_CCL_IRQHandler(&mCCL1);
        }
    #else
        /* 
         NOTE : This function should not be modified. When the IRQ handler is needed,
                function APX_IRQ must be implemented in the user file.
                Users can use "Add new item to group "Source group 1"..." to add IRQ handlers.
        */
        APX_IRQ();
    #endif
    
    /* USER CODE BEGIN APX_IRQ 1 */
    // to do...
    /* USER CODE END APX_IRQ 1 */
}

#endif


#if (defined(WWDT_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       WWDT module reset event service
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
void WWDT_IRQ (void)
{

    
    if(WWDT_GetSingleFlagStatus(WWDT_WINF) == DRV_Happened)
    {
        // When WWDT counter refreshing and value over the window compare threshold condition.
        // To do...
        
        WWDT_ClearFlag(WWDT_WINF);
    }
    
    if(WWDT_GetSingleFlagStatus(WWDT_WRNF) == DRV_Happened)
    {
        // When WWDT counter warning.
        // To do...
        WWDT_ClearFlag(WWDT_WRNF);
    }
        
    if(WWDT_GetSingleFlagStatus(WWDT_TF) == DRV_Happened)
    {
        // When WWDT timer timeout interrupt.
        // To do...
        WWDT_ClearFlag(WWDT_TF);
    }
}
#endif

#if (defined(IWDT_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       IWDT module IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak  void IWDT_IRQ (void)
{
    if(IWDT_GetSingleFlagStatus(IWDT_EW1F) == DRV_Happened)
    {
        // When early wake up 1 event happened.
        // To do...
        IWDT_ClearFlag(IWDT_EW1F);
        IWDT_RefreshCounter();
    }
    
    if(IWDT_GetSingleFlagStatus(IWDT_EW0F) == DRV_Happened)
    {
        // When early wake up 0 event happened.
        // To do...
        IWDT_ClearFlag(IWDT_EW0F);
        IWDT_RefreshCounter();
    }

    if(IWDT_GetSingleFlagStatus(IWDT_TF) == DRV_Happened)
    {
        // When timer timeout event happened.
        // To do...
        IWDT_ClearFlag(IWDT_TF);
        IWDT_RefreshCounter();
    }
}
#endif

#if (defined(PW_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       PW module IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void PW_IRQ (void)
{
    
    
    if(PW_GetSingleFlagStatus(PW_BOD0F) == DRV_Happened)
    {
        /* 
            When VDD voltage is less than BOD0 level. MCU cannot clear 
            BOD0F flag, until VDD voltage is greater than BOD0 level.
        */
        // When power on reset happened.
        // To do...
        PW_ClearFlag(PW_BOD0F);
    }
    
    if(PW_GetSingleFlagStatus(PW_BOD1F) == DRV_Happened)
    {
        // When Brown-Out detect BOD1 happened.
        // To do...
        PW_ClearFlag(PW_BOD1F);
    }
    
#if defined(PW_INT_BOD2_IE_mask_w)
    if(PW_GetSingleFlagStatus(PW_BOD2F) == DRV_Happened)
    {
        // When Brown-Out detect BOD2 happened.
        // To do...
        PW_ClearFlag(PW_BOD1F);
    }
#endif

    if(PW_GetSingleFlagStatus(PW_WKF) == DRV_Happened)
    {
        // When system received wakeup event happened.
        // To do...
        PW_ClearFlag(PW_WKF);
    }
}
#endif

#if (defined(RTC_Base) && defined(IRQHandler_Driver_Level_))

/**
 *******************************************************************************
 * @brief       RTC module reset event service
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
void RTC_IRQ (void)
{
    if(RTC_GetSingleFlagStatus(RTC_RCRF) == DRV_Happened)
    {
        // When RTC_RCR register reload finished, software capture finished or RTC_ALM register value update allowed.
        // To do...
        RTC_ClearFlag(RTC_RCRF);
    }

    if(RTC_GetSingleFlagStatus(RTC_TOF) == DRV_Happened)
    {
        // When RTC timer overflow.
        // To do...
        RTC_ClearFlag(RTC_TOF);
    }

    if(RTC_GetSingleFlagStatus(RTC_TSF) == DRV_Happened)
    {
        // When RTC time stamp.
        // To do...
        RTC_ClearFlag(RTC_TSF);
    }

    if(RTC_GetSingleFlagStatus(RTC_PCF) == DRV_Happened)
    {
        // When RTC periodic interrupt.
        // To do...
        RTC_ClearFlag(RTC_PCF);
    }

    if(RTC_GetSingleFlagStatus(RTC_ALMF) == DRV_Happened)
    {
        // When RTC alarm matched.
        // To do...
        RTC_ClearFlag(RTC_ALMF);
    }
    

}
#endif

#if (defined(CSC_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       CSC module IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak  void CSC_IRQ (void)
{
    if(CSC_GetSingleFlagStatus(CSC_MCDF) == DRV_Happened)
    {
        // XOSC missing clock detect failure happened.
        // To do...
        CSC_ClearFlag (CSC_MCDF);
    }

    if(CSC_GetSingleFlagStatus(CSC_PLLF) == DRV_Happened)
    {
        // PLL clock is stable.
        // To do...
        CSC_ClearFlag (CSC_PLLF);
    }

    if(CSC_GetSingleFlagStatus(CSC_IHRCOF) == DRV_Happened)
    {
        // IHRCO clock is stable.
        // To do...
        CSC_ClearFlag (CSC_IHRCOF);
    }

    if(CSC_GetSingleFlagStatus(CSC_ILRCOF) == DRV_Happened)
    {
        // ILRCO clock is stable.
        // To do...
        CSC_ClearFlag (CSC_ILRCOF);
    }

    if(CSC_GetSingleFlagStatus(CSC_XOSCF) == DRV_Happened)
    {
        // XOSC clock is stable.
        // To do...
        CSC_ClearFlag (CSC_XOSCF);
    }
}
#endif 

#if (defined(APB_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       APB interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void APB_IRQ(void)
{
    #if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    // APB OBM1 trigger event detect flag
    if(APB_GetSingleFlagStatus(APB, APB_OBM1F) == DRV_Happened)
    {       
        // To do...
        
        APB_ClearFlag(APB, APB_OBM1F);
    }
    #endif

    #if defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    // APB OBM0 trigger event detect flag
    if(APB_GetSingleFlagStatus(APB, APB_OBM0F) == DRV_Happened)
    {       
        // To do...
        
        APB_ClearFlag(APB, APB_OBM0F);
    }
    #endif

    #if defined(MG32_3RD) || defined(MG32_4TH)
    // APB NCO0 trigger event detect flag
    if(APB_GetSingleFlagStatus(APB, APB_NCO0F) == DRV_Happened)
    {       
        // To do...
        
        APB_ClearFlag(APB, APB_NCO0F);
    }
    #endif
}
#endif

#if (defined(MEM_Base) && defined(IRQHandler_Driver_Level_))

/**
 *******************************************************************************
 * @brief       MEM_IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
                MEM_IRQ();
 * @endcode     
 * @par         Modify
 *              __weak void MEM_IRQ(void)
 *******************************************************************************
 */
__weak void MEM_IRQ(void)
{


}
#endif

#if (defined(EMB_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       EMB_IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
                EMB_IRQ();
 * @endcode     
 * @par         Modify
 *              __weak void EMB_IRQ(void)
 *******************************************************************************
 */
__weak void EMB_IRQ(void)
{


}
#endif

#if (defined(EXIC_PA) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       EXIC interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void EXINT0_IRQ(void)
{
    if(EXIC_GetPxTriggerAndITFlagStatus(EXIC_PA_ITF)==DRV_Happened)
    {
        // To do...
        
        
        EXIC_ClearPxTriggerITFlag(EXIC_PA_ITF,EXIC_PX_AF);
    }
    if(EXIC_GetPxTriggerOrITFlagStatus(EXIC_PA_ITF)==DRV_Happened)
    {
        // To do...
       
        EXIC_ClearPxTriggerEventFlag(EXIC_PA, EXIC_PX_AllPIN );
    }
}
#endif

#if (defined(EXIC_PB) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void EXINT1_IRQ(void)
{
    if(EXIC_GetPxTriggerAndITFlagStatus(EXIC_PB_ITF)==DRV_Happened)
    {
        // To do...
        
        
        EXIC_ClearPxTriggerITFlag(EXIC_PB_ITF,EXIC_PX_AF);
    }
    if(EXIC_GetPxTriggerOrITFlagStatus(EXIC_PB_ITF)==DRV_Happened)
    {
        // To do...
       
        EXIC_ClearPxTriggerEventFlag(EXIC_PB, EXIC_PX_AllPIN );
    }   
}
#endif

#if (defined(EXIC_PC) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void EXINT2_IRQ(void)
{
    if(EXIC_GetPxTriggerAndITFlagStatus(EXIC_PC_ITF)==DRV_Happened)
    {
        // To do...
        
        
        EXIC_ClearPxTriggerITFlag(EXIC_PC_ITF,EXIC_PX_AF);
    }
    if(EXIC_GetPxTriggerOrITFlagStatus(EXIC_PC_ITF)==DRV_Happened)
    {
        // To do...
       
        EXIC_ClearPxTriggerEventFlag(EXIC_PC, EXIC_PX_AllPIN );
    }  
}
#endif

#if ((defined(EXIC_PD) || defined(EXIC_PE)) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void EXINT3_IRQ(void)
{
    if( __DRV_EXIC_GET_ID6_SOURCE() & EXIC_SRC1_ID6_exint3_b2)
    {
        if(EXIC_GetPxTriggerAndITFlagStatus(EXIC_PD_ITF)==DRV_Happened)
        {
            // To do...
               
            EXIC_ClearPxTriggerITFlag(EXIC_PD_ITF,EXIC_PX_AF);
        }
        if(EXIC_GetPxTriggerOrITFlagStatus(EXIC_PD_ITF)==DRV_Happened)
        {
            // To do...
           
            EXIC_ClearPxTriggerEventFlag(EXIC_PD, EXIC_PX_AllPIN );
        }   
    }
    #if defined(EXIC_SRC1_ID6_exint4_b2)
        if( __DRV_EXIC_GET_ID6_SOURCE() & EXIC_SRC1_ID6_exint4_b2)
        {
            if(EXIC_GetPxTriggerAndITFlagStatus(EXIC_PE_ITF)==DRV_Happened)
            {
                // To do...
                   
                EXIC_ClearPxTriggerITFlag(EXIC_PE_ITF,EXIC_PX_AF);
            }
            if(EXIC_GetPxTriggerOrITFlagStatus(EXIC_PE_ITF)==DRV_Happened)
            {
                // To do...
               
                EXIC_ClearPxTriggerEventFlag(EXIC_PE, EXIC_PX_AllPIN );
            }   
        }
    #endif
}
#endif

#if (defined(CMP_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       Compare interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void CMP_IRQ(void)
{
    
    #if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD)
    // AC0  rising / falling edge flag
    if (CMP_GetSingleFlagStatus(CMP, AC0_RisingEdge_Flag) == DRV_Happened)
    {
        // Rising edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC0_RisingEdge_Flag);
    }
    if (CMP_GetSingleFlagStatus(CMP, AC0_FallingEdge_Flag) == DRV_Happened)
    {
        // Falling edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC0_FallingEdge_Flag);
    }

    // AC1  rising / falling edge flag
    if (CMP_GetSingleFlagStatus(CMP, AC1_RisingEdge_Flag) == DRV_Happened)
    {
        // Rising edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC1_RisingEdge_Flag);
    }
    if (CMP_GetSingleFlagStatus(CMP, AC1_FallingEdge_Flag) == DRV_Happened)
    {
        // Falling edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC1_FallingEdge_Flag);
    }
    #endif

    #if defined(MG32_1ST)
    // AC2  rising / falling edge flag
    if (CMP_GetSingleFlagStatus(CMP, AC2_RisingEdge_Flag) == DRV_Happened)
    {
        // Rising edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC2_RisingEdge_Flag);
    }
    if (CMP_GetSingleFlagStatus(CMP, AC2_FallingEdge_Flag) == DRV_Happened)
    {
        // Falling edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC2_FallingEdge_Flag);
    }

    // AC3  rising / falling edge flag
    if (CMP_GetSingleFlagStatus(CMP, AC3_RisingEdge_Flag) == DRV_Happened)
    {
        // Rising edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC3_RisingEdge_Flag);
    }
    if (CMP_GetSingleFlagStatus(CMP, AC3_FallingEdge_Flag) == DRV_Happened)
    {
        // Falling edge interrupt flag 
        // To do...
        
        CMP_ClearFlag (CMP, AC3_FallingEdge_Flag);
    }
    #endif
}
#endif

#if (defined(DMA_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       DMA interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void DMA_IRQ(void)
{
    #if defined(MG32_1ST) || defined(MG32_2ND) || defined(MG32_3RD) || defined(MG32_4TH)
    // DMA channel-0 global interrupt flag
    if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH0_GIF) == DRV_Happened)
    {
        // DMA channel-0 transfer complete flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH0_TCF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH0_TCF);
        }
        // DMA channel-0 transfer half flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH0_THF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH0_THF);
        }
        // DMA channel-0 transfer error flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH0_ERRF) == DRV_Happened)
        {
            // To do...
            
            DMA_ClearFlag(DMA, DMA_FLAG_CH0_ERRF);
        }
    }
    #endif

    #if defined(MG32_1ST) || defined(MG32_3RD) || defined(MG32_4TH)
    // DMA channel-1 global interrupt flag
    if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH1_GIF) == DRV_Happened)
    {
        // DMA channel-1 transfer complete flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH1_TCF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH1_TCF);
        }
        // DMA channel-1 transfer half flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH1_THF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH1_THF);
        }
        // DMA channel-1 transfer error flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH1_ERRF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH1_ERRF);
        }
    }

    // DMA channel-2 global interrupt flag
    if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH2_GIF) == DRV_Happened)
    {
        // DMA channel-2 transfer complete flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH2_TCF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH2_TCF);
        }
        // DMA channel-2 transfer half flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH2_THF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH2_THF);
        }
        // DMA channel-2 transfer error flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH2_ERRF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH2_ERRF);
        }
    }
    #endif

    #if defined(MG32_3RD) || defined(MG32_4TH)
    // DMA channel-3 global interrupt flag
    if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH3_GIF) == DRV_Happened)
    {
        // DMA channel-3 transfer complete flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH3_TCF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH3_TCF);
        }
        // DMA channel-3 transfer half flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH3_THF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH3_THF);
        }
        // DMA channel-3 transfer error flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH3_ERRF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH3_ERRF);
        }
    }
    #endif

    #if defined(MG32_3RD)
    // DMA channel-4 global interrupt flag
    if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH4_GIF) == DRV_Happened)
    {
        // DMA channel-4 transfer complete flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH4_TCF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH4_TCF);
        }
        // DMA channel-4 transfer half flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH4_THF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH4_THF);
        }
        // DMA channel-4 transfer error flag
        if(DMA_GetSingleFlagStatus(DMA, DMA_FLAG_CH4_ERRF) == DRV_Happened)
        {
            // To do...

            DMA_ClearFlag(DMA, DMA_FLAG_CH4_ERRF);
        }
    }
    #endif
}
#endif

#if (defined(ADC0_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       ADC interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void ADC_IRQ(void)
{
    
    // accumulation 0/1/2
    if (ADC_GetSingleFlagStatus(ADC0, ADC_SUMOVRF) == DRV_Happened)
    {
        // ADC0 data sum-0,1,2  register overrun flag 
        // To do...

        ADC_ClearFlag (ADC0, ADC_SUMOVRF);
        ADC_ClearSum0Flags(ADC0, ADC_SUMxUF);
        ADC_ClearSum1Flags(ADC0, ADC_SUMxUF);
        ADC_ClearSum2Flags(ADC0, ADC_SUMxUF);
    }

    if (ADC_GetSingleFlagStatus(ADC0, ADC_SUMCF) == DRV_Happened)
    {
        // ADC0 data sum-0,1,2  accumulation complete flag 
        // To do...

        ADC_ClearFlag (ADC0, ADC_SUMCF);
    }

    if (ADC_GetSingleFlagStatus(ADC0, ADC_SUMOF) == DRV_Happened)
    {
        // ADC0 data sum-0,1,2 accumulation overflow or underflow flag
        // To do...

        ADC_ClearFlag (ADC0, ADC_SUMOF);
    }

    
    // window detect
    if (ADC_GetSingleFlagStatus(ADC0, ADC_WDHF) == DRV_Happened)
    {
        // ADC0 voltage window detect outside high event flag
        // To do...

        ADC_ClearFlag (ADC0, ADC_WDHF);
    }

    if (ADC_GetSingleFlagStatus(ADC0, ADC_WDIF) == DRV_Happened)
    {
        // ADC0 voltage window detect inside event flag 
        // To do...

        ADC_ClearFlag (ADC0, ADC_WDIF);
    }

    if (ADC_GetSingleFlagStatus(ADC0, ADC_WDLF) == DRV_Happened)
    {
        // ADC0 voltage window detect outside low event flag  
        // To do...

        ADC_ClearFlag (ADC0, ADC_WDLF);
    }

    // conversion overrun
    if (ADC_GetSingleFlagStatus(ADC0, ADC_OVRF) == DRV_Happened)
    {
        // ADC0 conversion overrun event flag   
        // To do...

        ADC_ClearFlag (ADC0, ADC_OVRF);
    }

    // conversion end
    if (ADC_GetSingleFlagStatus(ADC0, ADC_ESCNVF) == DRV_Happened)
    {
        // ADC0 channel scan conversion end flag   
        // To do...

        ADC_ClearFlag (ADC0, ADC_ESCNVF);
    }
    if (ADC_GetSingleFlagStatus(ADC0, ADC_E1CNVF) == DRV_Happened)
    {
        // ADC0 one-time conversion end flagg  
        // To do...

        ADC_ClearFlag (ADC0, ADC_E1CNVF);
    }

    // sampling end
    if (ADC_GetSingleFlagStatus(ADC0, ADC_ESMPF) == DRV_Happened)
    {
        // ADC0 sampling end flag 
        // To do...

        ADC_ClearFlag (ADC0, ADC_ESMPF);
    }
}
#endif

#if (defined(DAC_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       DAC interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void DAC_IRQ(void)
{
    #if defined(MG32_1ST) || defined(MG32_3RD)
    // DAC ready flag to update new data to data register
    if (DAC_GetAllFlagStatus(DAC) & Ready_Flag)
    {
        // To do...

        DAC_ClearFlag(DAC,Ready_Flag);
    }
    // DAC conversion underrun event flag
    if (DAC_GetAllFlagStatus(DAC) & Underrun_Flag)
    {
        // To do...

        DAC_ClearFlag(DAC,Underrun_Flag);
    }
    #endif
}
#endif

#if (defined(TM00_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM00 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM00_IRQ(void)
{
    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM00, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM00, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM00, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM00, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM00, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...

        TM_ClearFlag (TM00, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM00, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM00, TMx_EXF);
    }
}
#endif

#if (defined(TM01_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM01 interrupt function. 
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM01_IRQ(void)
{
    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM01, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM01, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM01, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM01, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM01, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...

        TM_ClearFlag (TM01, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM01, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM01, TMx_EXF);
    }
}
#endif

#if (defined(TM10_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM10 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM10_IRQ(void)
{
    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM10, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM10, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM10, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM10, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM10, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...
        
        TM_ClearFlag (TM10, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM10, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM10, TMx_EXF);
    }
}
#endif

#if (defined(TM16_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM16 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM16_IRQ(void)
{
    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM16, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM16, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM16, TMx_TUF) == DRV_Happened)
    {
        // Main Timer underflow flag
        // To do...

        TM_ClearFlag (TM16, TMx_TUF);
    }
    if (TM_GetSingleFlagStatus(TM16, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM16, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM16, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...

        TM_ClearFlag (TM16, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM16, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM16, TMx_EXF);
    }
}
#endif

#if (defined(TM20_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM20 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM20_IRQ(void)
{
    #if defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM20, TMx_IDCF) == DRV_Happened)
    {
        // Repetition timer underflow flag. 
        // To do...

        TM_ClearFlag (TM20, TMx_IDCF);
    }
    #endif
    // ------------------------------------------------------------------------
    #if defined(MG32_3RD) || defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM20, TMx_RTUF) == DRV_Happened)
    {
        // Repetition timer underflow flag. 
        // To do...

        TM_ClearFlag (TM20, TMx_RTUF);
    }
    #endif
    // ------------------------------------------------------------------------
    // Channel1 - IC/OC 
    if (TM_GetSingleFlagStatus(TM20, TMx_CF1B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        // To do...

        TM_ClearFlag (TM20, TMx_CF1B);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_CF1A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event main flag
        // To do...

        TM_ClearFlag (TM20, TMx_CF1A);
    }

    // Channel0 - IC/OC 
    if (TM_GetSingleFlagStatus(TM20, TMx_CF0B) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event sub flag
        // To do...

        TM_ClearFlag (TM20, TMx_CF0B);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_CF0A) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event main flag
        // To do...
        
        TM_ClearFlag (TM20, TMx_CF0A);
    }

    // ------------------------------------------------------------------------
    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM20, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM20, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM20, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM20, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...

        TM_ClearFlag (TM20, TMx_TOF);
    }

    // ------------------------------------------------------------------------
    // external trigger
    if (TM_GetSingleFlagStatus(TM20, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...
        
        TM_ClearFlag (TM20, TMx_EXF);
    }
}
#endif

#if (defined(TM26_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM26 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM26_IRQ(void)
{
    #if defined(MG32_3RD)
    if (TM_GetSingleFlagStatus(TM26, TMx_RTUF) == DRV_Happened)
    {
        // Repetition timer underflow flag.
        // To do...

        TM_ClearFlag (TM26, TMx_RTUF);
    }
    #endif

    // QEI event
    if (TM_GetSingleFlagStatus(TM26, TMx_QPEF) == DRV_Happened)
    {
        // Main Timer QEI phase state transition error detect flag.
        // To do...

        TM_ClearFlag (TM26, TMx_QPEF);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_IDXF) == DRV_Happened)
    {
        // Main Timer QEI external index signal input active detect and internal timer reset flag.
        // To do...

        TM_ClearFlag (TM26, TMx_IDXF);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_DIRCF) == DRV_Happened)
    {
        // Main Timer up/down counting direction change flag.
        // To do...

        TM_ClearFlag (TM26, TMx_DIRCF);
    }

    // Channel1 - IC/OC 
    if (TM_GetSingleFlagStatus(TM26, TMx_CF1B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        // To do...

        TM_ClearFlag (TM26, TMx_CF1B);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_CF1A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event main flag
        // To do...

        TM_ClearFlag (TM26, TMx_CF1A);
    }

    // Channel0 - IC/OC 
    if (TM_GetSingleFlagStatus(TM26, TMx_CF0B) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event sub flag
        // To do...

        TM_ClearFlag (TM26, TMx_CF0B);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_CF0A) == DRV_Happened)
    {
        // Timer IC0 falling edge flag/OC0 event main flag
        // To do...
        
        TM_ClearFlag (TM26, TMx_CF0A);
    }

    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM26, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM26, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_TUF) == DRV_Happened)
    {
        // Main Timer underflow flag
        // To do...

        TM_ClearFlag (TM26, TMx_TUF);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM26, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM26, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...

        TM_ClearFlag (TM26, TMx_TOF);
    }

    // external trigger
    if (TM_GetSingleFlagStatus(TM26, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM26, TMx_EXF);
    }
}
#endif

#if (defined(TM36_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       TM36 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void TM36_IRQ(void)
{
    // ------------------------------------------------------------------------
    // Duty capture flag.
    #if defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM36, TMx_IDCF) == DRV_Happened)
    {
        // Input duty capture complete flag.. 
        // To do...

        TM_ClearFlag (TM36, TMx_IDCF);
    }
    #endif

    // ------------------------------------------------------------------------
    // Repetition timer flag.
    #if defined(MG32_3RD) || defined(MG32_4TH)
    if (TM_GetSingleFlagStatus(TM36, TMx_RTUF) == DRV_Happened)
    {
        // Repetition timer underflow flag. 
        // To do...

        TM_ClearFlag (TM36, TMx_RTUF);
    }
    #endif

    // ------------------------------------------------------------------------
    // QEI event
    if (TM_GetSingleFlagStatus(TM36, TMx_QPEF) == DRV_Happened)
    {
        // Main Timer QEI phase state transition error detect flag.
        // To do...

        TM_ClearFlag (TM36, TMx_QPEF);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_IDXF) == DRV_Happened)
    {
        // Main Timer QEI external index signal input active detect and internal timer reset flag.
        // To do...

        TM_ClearFlag (TM36, TMx_IDXF);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_DIRCF) == DRV_Happened)
    {
        // Main Timer up/down counting direction change flag.
        // To do...

        TM_ClearFlag (TM36, TMx_DIRCF);
    }

    // ------------------------------------------------------------------------
    // Sub event - IC/OC 
    if (TM_GetSingleFlagStatus(TM36, TMx_CF3B) == DRV_Happened)
    {
        // Timer IC3 falling edge flag/OC3 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF3B);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF2B) == DRV_Happened)
    {
        // Timer IC2 falling edge flag/OC2 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF2B);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF1B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF1B);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF0B) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF0B);
    }

    // Main event - IC/OC 
    if (TM_GetSingleFlagStatus(TM36, TMx_CF3A) == DRV_Happened)
    {
        // Timer IC3 falling edge flag/OC3 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF3A);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF2A) == DRV_Happened)
    {
        // Timer IC2 falling edge flag/OC2 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF2A);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF1A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF1A);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_CF0A) == DRV_Happened)
    {
        // Timer IC1 falling edge flag/OC1 event sub flag
        // To do...

        TM_ClearFlag (TM36, TMx_CF0A);
    }

    // ------------------------------------------------------------------------
    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM36, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...

        TM_ClearFlag (TM36, TMx_TUF2);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_TUF) == DRV_Happened)
    {
        // Main Timer underflow flag
        // To do...

        TM_ClearFlag (TM36, TMx_TUF);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_TOF2) == DRV_Happened)
    {
        // 2nd Timer overflow flag
        // To do...

        TM_ClearFlag (TM36, TMx_TOF2);
    }
    if (TM_GetSingleFlagStatus(TM36, TMx_TOF) == DRV_Happened)
    {
        // Main Timer overflow flag
        // To do...

        TM_ClearFlag (TM36, TMx_TOF);
    }

    // ------------------------------------------------------------------------
    // Break input event
    if (TM_GetSingleFlagStatus(TM36, TMx_BKF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM36, TMx_BKF);
    }

    // ------------------------------------------------------------------------
    // external trigger
    if (TM_GetSingleFlagStatus(TM36, TMx_EXF) == DRV_Happened)
    {
        // Timer external trigger flag
        // To do...

        TM_ClearFlag (TM36, TMx_EXF);
    }
}
#endif

#if (defined(URT0_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT0 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void URT0_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t URT_Flag;
    uint32_t data;

    URT_Flag   = URT_GetITAllFlagStatus(URT0);
    URT_ITFlag = (URT_Flag & URT_GetITStatus(URT0));

    if((URT_ITFlag & URT_IT_UG) == URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_SADR) == URT_IT_SADR)
        {
            // To do ......

            URT_ClearITFlag(URT0,URT_IT_SADR);
        }
        if((URT_ITFlag & URT_IT_BRT) == URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT0,URT_IT_BRT);
        }
        if((URT_ITFlag & URT_IT_TMO) == URT_IT_TMO)
        {
            // To do ......

            URT_ClearITFlag(URT0,URT_IT_TMO);
        }
        if((URT_ITFlag & URT_IT_CALC) == URT_IT_CALC)
        {
            #if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
                if( URT_Flag & URT_EVENT_CALOVF)
                {
                    // Calibration result overflow ( over baudrate generator range)
                    // To do ......
                }
                else if( URT_Flag & URT_EVENT_CALUDF)
                {
                    // Calibration result underflow ( under baudrate generator range)
                    // To do ......
                }
                else
                {
                    // Calibration complete.
                    // To do ......
                }
            #endif
            URT_ClearITFlag(URT0,URT_IT_CALC);
        }

        URT_ClearITFlag(URT0,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX) == URT_IT_RX)
    {
        //---when RX Data Register have data---//
        data = URT_GetRXData(URT0);
        URT_SetTXData(URT0, 1, data);             //read data auto clear RX flag.

        // To do ......
//        URT_ClearITFlag(URT0,URT_IT_RX);
    }
    if((URT_ITFlag & URT_IT_TX) == URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT0,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_LS) == URT_IT_LS)
    {
        if((URT_ITFlag & URT_IT_IDL) == URT_IT_IDL)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_IDL);
        }
        if((URT_ITFlag & URT_IT_CTS) == URT_IT_CTS)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_CTS);
        }
        if((URT_ITFlag & URT_IT_BK) == URT_IT_BK)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_BK);
        }
        URT_ClearITFlag(URT0,URT_IT_LS); 
    }
    if((URT_ITFlag & URT_IT_ERR) == URT_IT_ERR)
    {
        if((URT_ITFlag & URT_IT_PE) == URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_FE) == URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_FE);
        }
        if((URT_ITFlag & URT_IT_NCE) == URT_IT_NCE)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_NCE);
        }
        if((URT_ITFlag & URT_IT_ROVR) == URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_ROVR);
        }
        #if defined(URT_STA_TUDRF_mask_w)
            if((URT_ITFlag & URT_IT_TUDR) == URT_IT_TUDR)
            {
                //To do......
                URT_ClearITFlag(URT0,URT_IT_TUDR);
            }
        #endif
        if((URT_ITFlag & URT_IT_TXE) == URT_IT_TXE)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_TXE);
        }
        if((URT_ITFlag & URT_IT_RXTMO) == URT_IT_RXTMO)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_RXTMO);
        }
        if((URT_ITFlag & URT_IT_IDTMO) == URT_IT_IDTMO)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_IDTMO);
        }
        if((URT_ITFlag & URT_IT_BKTMO) == URT_IT_BKTMO)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_BKTMO);
        }
        if((URT_ITFlag & URT_IT_CALTMO) == URT_IT_CALTMO)
        {
            //To do......

            URT_ClearITFlag(URT0,URT_IT_CALTMO);
        }
        URT_ClearITFlag(URT0,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC) == URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT0, URT_IT_TC);    //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(URT1_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT1 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void URT1_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t URT_Flag;
    uint32_t data;

    URT_Flag   = URT_GetITAllFlagStatus(URT1);
    URT_ITFlag = (URT_Flag & URT_GetITStatus(URT1));

    if((URT_ITFlag & URT_IT_UG) == URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_SADR) == URT_IT_SADR)
        {
            // To do ......

            URT_ClearITFlag(URT1,URT_IT_SADR);
        }
        if((URT_ITFlag & URT_IT_BRT) == URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT1,URT_IT_BRT);
        }
        if((URT_ITFlag & URT_IT_TMO) == URT_IT_TMO)
        {
            // To do ......

            URT_ClearITFlag(URT1,URT_IT_TMO);
        }
        if((URT_ITFlag & URT_IT_CALC) == URT_IT_CALC)
        {
            #if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
                if( URT_Flag & URT_EVENT_CALOVF)
                {
                    // Calibration result overflow ( over baudrate generator range)
                    // To do ......
                }
                else if( URT_Flag & URT_EVENT_CALUDF)
                {
                    // Calibration result underflow ( under baudrate generator range)
                    // To do ......
                }
                else
                {
                    // Calibration complete.
                    // To do ......
                }
            #endif
            URT_ClearITFlag(URT1,URT_IT_CALC);
        }

        URT_ClearITFlag(URT1,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX) == URT_IT_RX)
    {
        //---when RX Data Register have data---//
        data = URT_GetRXData(URT1);
        URT_SetTXData(URT1, 1, data);             //read data auto clear RX flag.

        // To do ......
//        URT_ClearITFlag(URT1,URT_IT_RX);
    }
    if((URT_ITFlag & URT_IT_TX) == URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT1,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_LS) == URT_IT_LS)
    {
        if((URT_ITFlag & URT_IT_IDL) == URT_IT_IDL)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_IDL);
        }
        if((URT_ITFlag & URT_IT_CTS) == URT_IT_CTS)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_CTS);
        }
        if((URT_ITFlag & URT_IT_BK) == URT_IT_BK)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_BK);
        }
        URT_ClearITFlag(URT1,URT_IT_LS); 
    }
    if((URT_ITFlag & URT_IT_ERR) == URT_IT_ERR)
    {
        if((URT_ITFlag & URT_IT_PE) == URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_FE) == URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_FE);
        }
        if((URT_ITFlag & URT_IT_NCE) == URT_IT_NCE)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_NCE);
        }
        if((URT_ITFlag & URT_IT_ROVR) == URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_ROVR);
        }
        #if defined(URT_STA_TUDRF_mask_w)
            if((URT_ITFlag & URT_IT_TUDR) == URT_IT_TUDR)
            {
                //To do......
                URT_ClearITFlag(URT1,URT_IT_TUDR);
            }
        #endif
        if((URT_ITFlag & URT_IT_TXE) == URT_IT_TXE)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_TXE);
        }
        if((URT_ITFlag & URT_IT_RXTMO) == URT_IT_RXTMO)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_RXTMO);
        }
        if((URT_ITFlag & URT_IT_IDTMO) == URT_IT_IDTMO)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_IDTMO);
        }
        if((URT_ITFlag & URT_IT_BKTMO) == URT_IT_BKTMO)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_BKTMO);
        }
        if((URT_ITFlag & URT_IT_CALTMO) == URT_IT_CALTMO)
        {
            //To do......

            URT_ClearITFlag(URT1,URT_IT_CALTMO);
        }
        URT_ClearITFlag(URT1,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC) == URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT1, URT_IT_TC);    //Write TXData auto clear TC flag.
    }
}
#endif 

#if (defined(URT2_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT2 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void URT2_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t URT_Flag;
    uint32_t data;
    
    URT_Flag   = URT_GetITAllFlagStatus(URT2);
    URT_ITFlag = (URT_Flag & URT_GetITStatus(URT2));

    if((URT_ITFlag & URT_IT_UG) == URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_SADR) == URT_IT_SADR)
        {
            // To do ......

            URT_ClearITFlag(URT2,URT_IT_SADR);
        }
        if((URT_ITFlag & URT_IT_BRT) == URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT2,URT_IT_BRT);
        }
        if((URT_ITFlag & URT_IT_TMO) == URT_IT_TMO)
        {
            // To do ......

            URT_ClearITFlag(URT2,URT_IT_TMO);
        }
        if((URT_ITFlag & URT_IT_CALC) == URT_IT_CALC)
        {
            #if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
                if( URT_Flag & URT_EVENT_CALOVF)
                {
                    // Calibration result overflow ( over baudrate generator range)
                    // To do ......
                }
                else if( URT_Flag & URT_EVENT_CALUDF)
                {
                    // Calibration result underflow ( under baudrate generator range)
                    // To do ......
                }
                else
                {
                    // Calibration complete.
                    // To do ......
                }
            #endif
            URT_ClearITFlag(URT2,URT_IT_CALC);
        }

        URT_ClearITFlag(URT2,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX) == URT_IT_RX)
    {
        //---when RX Data Register have data---//
        data = URT_GetRXData(URT2);
        URT_SetTXData(URT2, 1, data);             //read data auto clear RX flag.

        // To do ......
//        URT_ClearITFlag(URT2,URT_IT_RX);
    }
    if((URT_ITFlag & URT_IT_TX) == URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT2,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_LS) == URT_IT_LS)
    {
        if((URT_ITFlag & URT_IT_IDL) == URT_IT_IDL)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_IDL);
        }
        if((URT_ITFlag & URT_IT_CTS) == URT_IT_CTS)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_CTS);
        }
        if((URT_ITFlag & URT_IT_BK) == URT_IT_BK)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_BK);
        }
        URT_ClearITFlag(URT2,URT_IT_LS); 
    }
    if((URT_ITFlag & URT_IT_ERR) == URT_IT_ERR)
    {
        if((URT_ITFlag & URT_IT_PE) == URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_FE) == URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_FE);
        }
        if((URT_ITFlag & URT_IT_NCE) == URT_IT_NCE)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_NCE);
        }
        if((URT_ITFlag & URT_IT_ROVR) == URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_ROVR);
        }
        #if defined(URT_STA_TUDRF_mask_w)
            if((URT_ITFlag & URT_IT_TUDR) == URT_IT_TUDR)
            {
                //To do......
                URT_ClearITFlag(URT2,URT_IT_TUDR);
            }
        #endif
        if((URT_ITFlag & URT_IT_TXE) == URT_IT_TXE)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_TXE);
        }
        if((URT_ITFlag & URT_IT_RXTMO) == URT_IT_RXTMO)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_RXTMO);
        }
        if((URT_ITFlag & URT_IT_IDTMO) == URT_IT_IDTMO)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_IDTMO);
        }
        if((URT_ITFlag & URT_IT_BKTMO) == URT_IT_BKTMO)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_BKTMO);
        }
        if((URT_ITFlag & URT_IT_CALTMO) == URT_IT_CALTMO)
        {
            //To do......

            URT_ClearITFlag(URT2,URT_IT_CALTMO);
        }
        URT_ClearITFlag(URT2,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC) == URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT2, URT_IT_TC);    //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(URT3_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT3 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void URT3_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t URT_Flag;
    uint32_t data;

    URT_Flag   = URT_GetITAllFlagStatus(URT3);
    URT_ITFlag = (URT_Flag & URT_GetITStatus(URT3));

    if((URT_ITFlag & URT_IT_UG) == URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_SADR) == URT_IT_SADR)
        {
            // To do ......

            URT_ClearITFlag(URT3,URT_IT_SADR);
        }
        if((URT_ITFlag & URT_IT_BRT) == URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT3,URT_IT_BRT);
        }
        if((URT_ITFlag & URT_IT_TMO) == URT_IT_TMO)
        {
            // To do ......

            URT_ClearITFlag(URT3,URT_IT_TMO);
        }
        if((URT_ITFlag & URT_IT_CALC) == URT_IT_CALC)
        {
            #if defined(URT_STA_CALOVF_mask_w) && defined(URT_STA_CALUDF_mask_w)
                if( URT_Flag & URT_EVENT_CALOVF)             
                {
                    // Calibration result overflow ( over baudrate generator range)
                    // To do ......
                }
                else if( URT_Flag & URT_EVENT_CALUDF)
                {
                    // Calibration result underflow ( under baudrate generator range)
                    // To do ......
                }
                else
                {
                    // Calibration complete.
                    // To do ......
                }
            #endif
            URT_ClearITFlag(URT3,URT_IT_CALC);
        }

        URT_ClearITFlag(URT3,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX) == URT_IT_RX)
    {
        //---when RX Data Register have data---//
        data = URT_GetRXData(URT3);
        URT_SetTXData(URT3, 1, data);             //read data auto clear RX flag.

        // To do ......
//        URT_ClearITFlag(URT3,URT_IT_RX);
    }
    if((URT_ITFlag & URT_IT_TX) == URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT3,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_LS) == URT_IT_LS)
    {
        if((URT_ITFlag & URT_IT_IDL) == URT_IT_IDL)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_IDL);
        }
        if((URT_ITFlag & URT_IT_CTS) == URT_IT_CTS)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_CTS);
        }
        if((URT_ITFlag & URT_IT_BK) == URT_IT_BK)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_BK);
        }
        URT_ClearITFlag(URT3,URT_IT_LS); 
    }
    if((URT_ITFlag & URT_IT_ERR) == URT_IT_ERR)
    {
        if((URT_ITFlag & URT_IT_PE) == URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_FE) == URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_FE);
        }
        if((URT_ITFlag & URT_IT_NCE) == URT_IT_NCE)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_NCE);
        }
        if((URT_ITFlag & URT_IT_ROVR) == URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_ROVR);
        }
        #if defined(URT_STA_TUDRF_mask_w)
            if((URT_ITFlag & URT_IT_TUDR) == URT_IT_TUDR)
            {
                //To do......
                URT_ClearITFlag(URT3,URT_IT_TUDR);
            }
        #endif
        if((URT_ITFlag & URT_IT_TXE) == URT_IT_TXE)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_TXE);
        }
        if((URT_ITFlag & URT_IT_RXTMO) == URT_IT_RXTMO)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_RXTMO);
        }
        if((URT_ITFlag & URT_IT_IDTMO) == URT_IT_IDTMO)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_IDTMO);
        }
        if((URT_ITFlag & URT_IT_BKTMO) == URT_IT_BKTMO)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_BKTMO);
        }
        if((URT_ITFlag & URT_IT_CALTMO) == URT_IT_CALTMO)
        {
            //To do......

            URT_ClearITFlag(URT3,URT_IT_CALTMO);
        }
        URT_ClearITFlag(URT3,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC) == URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT3, URT_IT_TC);    //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(URT4_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT4 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
 __weak void URT4_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t data;

    URT_ITFlag = (URT_GetITAllFlagStatus(URT4) & URT_GetITStatus(URT4));

    if((URT_ITFlag & URT_IT_UG)==URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_BRT)==URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT4,URT_IT_BRT);
        }
    
        URT_ClearITFlag(URT4,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX)==URT_IT_RX)
    {
        data = URT_GetRXData(URT4);
        URT_SetTXData(URT4, 1, data);
        // To do ......
//        URT_ClearITFlag(URT4,URT_IT_RX);         //read data auto clear RX flag.
    }
    if((URT_ITFlag & URT_IT_TX)==URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT4,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_ERR)==URT_IT_ERR)
    {
        if((URT_ITFlag & URT_IT_PE)==URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT4,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_ROVR)==URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT4,URT_IT_ROVR);
        }
        if((URT_ITFlag & URT_IT_FE)==URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT4,URT_IT_FE);
        }

        URT_ClearITFlag(URT4,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC)==URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT4, URT_IT_TC);       //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(URT5_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT5 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void URT5_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t data;

    URT_ITFlag = (URT_GetITAllFlagStatus(URT5) & URT_GetITStatus(URT5));

    if((URT_ITFlag & URT_IT_UG)==URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_BRT)==URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT5,URT_IT_BRT);
        }

        URT_ClearITFlag(URT5,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX)==URT_IT_RX)
    {
        data = URT_GetRXData(URT5);
        URT_SetTXData(URT5, 1, data);
        // To do ......
//        URT_ClearITFlag(URT5,URT_IT_RX);         //read data auto clear RX flag.
    }
    if((URT_ITFlag & URT_IT_TX)==URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT5,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_ERR)==URT_IT_ERR)
    {
        
        if((URT_ITFlag & URT_IT_PE)==URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT5,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_ROVR)==URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT5,URT_IT_ROVR);
        }
        if((URT_ITFlag & URT_IT_FE)==URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT5,URT_IT_FE);
        }

        URT_ClearITFlag(URT5,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC)==URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT5, URT_IT_TC);      //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(URT6_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT6 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
 __weak void URT6_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t data;

    URT_ITFlag = (URT_GetITAllFlagStatus(URT6) & URT_GetITStatus(URT6));

    if((URT_ITFlag & URT_IT_UG)==URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_BRT)==URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT6,URT_IT_BRT);
        }

        URT_ClearITFlag(URT6,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX)==URT_IT_RX)
    {
        data = URT_GetRXData(URT6);
        URT_SetTXData(URT6, 1, data);
        // To do ......
//        URT_ClearITFlag(URT6,URT_IT_RX);         //read data auto clear RX flag.
    }
    if((URT_ITFlag & URT_IT_TX)==URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT6,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_ERR)==URT_IT_ERR)
    {
        
        if((URT_ITFlag & URT_IT_PE)==URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT6,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_ROVR)==URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT6,URT_IT_ROVR);
        }
        if((URT_ITFlag & URT_IT_FE)==URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT6,URT_IT_FE);
        }

        URT_ClearITFlag(URT6,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC)==URT_IT_TC)
    {
        //To do......
        
        URT_ClearITFlag(URT6, URT_IT_TC);      //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(URT7_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       URT7 interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void URT7_IRQ(void)
{
    uint32_t URT_ITFlag;
    uint32_t data;
    
    URT_ITFlag = (URT_GetITAllFlagStatus(URT7) & URT_GetITStatus(URT7));
    
    if((URT_ITFlag & URT_IT_UG)==URT_IT_UG)
    {
        if((URT_ITFlag & URT_IT_BRT)==URT_IT_BRT)
        {
            // To do ......

            URT_ClearITFlag(URT7,URT_IT_BRT);
        }

        URT_ClearITFlag(URT7,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX)==URT_IT_RX)
    {
        data = URT_GetRXData(URT7);
        URT_SetTXData(URT7, 1, data);
        // To do ......
//        URT_ClearITFlag(URT7,URT_IT_RX);         //read data auto clear RX flag.
    }
    if((URT_ITFlag & URT_IT_TX)==URT_IT_TX)
    {
        // To do ......

        URT_ClearITFlag(URT7,URT_IT_TX);          //Write TXData auto clear TX flag.
    }
    if((URT_ITFlag & URT_IT_ERR)==URT_IT_ERR)
    {
        if((URT_ITFlag & URT_IT_PE)==URT_IT_PE)
        {
            //To do......

            URT_ClearITFlag(URT7,URT_IT_PE);
        }
        if((URT_ITFlag & URT_IT_ROVR)==URT_IT_ROVR)
        {
            //To do......

            URT_ClearITFlag(URT7,URT_IT_ROVR);
        }
        if((URT_ITFlag & URT_IT_FE)==URT_IT_FE)
        {
            //To do......

            URT_ClearITFlag(URT7,URT_IT_FE);
        }

        URT_ClearITFlag(URT7,URT_IT_ERR);
    }
    if((URT_ITFlag & URT_IT_TC)==URT_IT_TC)
    {
        //To do......

        URT_ClearITFlag(URT7, URT_IT_TC);     //Write TXData auto clear TC flag.
    }
}
#endif

#if (defined(SPI0_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief         SPI module IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void SPI0_IRQ (void)
{
    if(SPI_GetSingleFlagStatus(SPI0, SPI_TCF) == DRV_Happened)   
    {
        // SPI transmission complete happened.
        // To do...
        SPI_ClearFlag (SPI0, SPI_TCF);
    }
    
    if(SPI_GetSingleFlagStatus(SPI0, SPI_RXF) == DRV_Happened)   
    {
        // Receive data buffer high level happened.
        // To do...
        SPI_ClearFlag (SPI0,SPI_RXF);
    }
    
    if(SPI_GetSingleFlagStatus(SPI0, SPI_TXF) == DRV_Happened)   
    {
        // Transmit data buffer level low happened.
        // To do...
        SPI_ClearFlag (SPI0, SPI_TXF);
    }

    if(SPI_GetSingleFlagStatus(SPI0, SPI_MODF) == DRV_Happened)   
    {
        // Mode detect fault happened.
        // To do...
        SPI_ClearFlag (SPI0, SPI_MODF);
    }

    if(SPI_GetSingleFlagStatus(SPI0, SPI_WEF) == DRV_Happened)   
    {
        // Slave mode write error happened.
        // To do...
        SPI_ClearFlag (SPI0, SPI_WEF);
    }
    
    if(SPI_GetSingleFlagStatus(SPI0, SPI_ROVRF) == DRV_Happened)   
    {
        // Receive overrun happened.
        // To do...
        SPI_ClearFlag (SPI0, SPI_ROVRF);
    }
    
    if(SPI_GetSingleFlagStatus(SPI0, SPI_TUDRF) == DRV_Happened)   
    {
        // Slave mode transmit underrun happened.
        // To do...
        SPI_ClearFlag (SPI0, SPI_TUDRF);
    }
    
    if(SPI_GetSingleFlagStatus(SPI0, SPI_IDLF) == DRV_Happened)
    {
        // SPI slave mode NSS idle happened
        // To do...
        SPI_ClearFlag (SPI0, SPI_IDLF);
    }
}
#endif

#if (defined(I2C0_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       I2C Timeout Handler
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
                I2C_Timeout_Handler(I2C0)
                I2C_Timeout_Handler(I2C1)
 * @endcode
 * @par         Modify
 *              __weak void I2C_Timeout_Handler(I2C_Struct* I2Cx)
 *******************************************************************************
 */
__weak void I2C_Timeout_Handler(I2C_Struct* I2Cx)
{
    if(I2C_GetFlagStatus(I2Cx, I2C_FLAG_TMOUTF))
    {
        // I2C0 time-out detect.
        // to do..
        I2C_ClearFlag(I2Cx, I2C_FLAG_TMOUTF);
    }
}

/**
 *******************************************************************************
 * @brief       I2C ByteMode Event Handler
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
                I2C_ByteMode_Event_Handler(I2C0);
                I2C_ByteMode_Event_Handler(I2C1);
 * @endcode
 * @par         Modify
 *              __weak void I2C_ByteMode_Event_Handler(I2C_Struct* I2Cx)
 *******************************************************************************
 */
__weak void I2C_ByteMode_Event_Handler(I2C_Struct* I2Cx)
{
    if(I2C_GetFlagStatus(I2Cx, I2C_FLAG_EVENTF))
    {
        // I2C status event interrupt.
        // to do..
        switch(I2C_GetEventCode(I2Cx)){
            case 0x00:  // Bus error during MASTER or selected slave modes, due to an illegal START or STOP condition. State 0x00 can also occur when interference causes the I2C block to enter an undefined state.
                    // to do..
                break;

            case 0x08:  // A START condition has been transmitted.
                    // to do..
                break;

            case 0x10:  // A repeated START condition has been transmitted.
                    // to do..
                break;

            case 0x18:  // SLA+W has been transmitted; ACK has been received.
                    // to do..
                break;

            case 0x20:  // SLA+W has been transmitted; NOT ACK has been received.
                    // to do..
                break;

            case 0x28:  // Data byte in DAT has been transmitted; ACK has been received.
                    // to do..
                break;

            case 0x30:  // Data byte in DAT has been transmitted; NOT ACK has been received.
                    // to do..
                break;

            case 0x38:  // Arbitration lost in SLA+R/W or Data bytes.
                    // to do..
                break;

            case 0x40:  // SLA+R has been transmitted; ACK has been received.
                    // to do..
                break;

            case 0x48:  // SLA+R has been transmitted; NOT ACK has been received.
                    // to do..
                break;

            case 0x50:  // Data byte has been received; ACK has been returned.
                    // to do..
                break;

            case 0x58:  // Data byte has been received; NOT ACK has been returned.
                    // to do..
                break;

            case 0x60:  // Own SLA+W has been received; ACK has been returned.
                    // to do..
                break;

            case 0x68:  // Arbitration lost in SLA+R/W as master; Own SLA+W has been received, ACK returned.
                    // to do..
                break;

            case 0x70:  // General Call address (0x00) has been received; ACK has been returned.
                    // to do..
                break;

            case 0x78:  // Arbitration lost in SLA+R/W as master; General Call address has been received, ACK has been returned.
                    // to do..
                break;

            case 0x80:  // Previously addressed with own SLA address; DATA has been received; ACK has been returned.
                    // to do..
                break;

            case 0x88:  // Previously addressed with own SLA; DATA byte has been received; NOT ACK has been returned.
                    // to do..
                break;

            case 0x90:  // Previously addressed with General Call; DATA byte has been received; ACK has been returned.
                    // to do..
                break;

            case 0x98:  // Previously addressed with General Call; DATA byte has been received; NOT ACK has been returned.
                    // to do..
                break;

            case 0xA0:  // A STOP condition or condition has been received while still addressed as Slave Receiver or Slave Transmitter.
                    // to do..
                break;

            case 0xA8:  // Own SLA+R has been received; ACK has been returned.
                    // to do..
                break;

            case 0xB0:  // Arbitration lost in SLA+R/W as master; Own SLA+R has been received, ACK has been returned.
                    // to do..
                break;

            case 0xB8:  // Data byte in DAT has been transmitted; ACK has been received.
                    // to do..
                break;

            case 0xC0:  // Data byte in DAT has been transmitted; NOT ACK has been received.
                    // to do..
                break;

            case 0xC8:  // Last data byte in DAT has been transmitted (AA = 0); ACK has been received.
                    // to do..
                break;

            case 0xF8:  // No relevant state information available; Bus is released ; EVENTF = 0 and no interrupt asserted.(Default)
                    // to do..
                break;
        }
        // to do..
        I2C_ClearFlag(I2Cx, I2C_FLAG_EVENTF);
    }
}

/**
 *******************************************************************************
 * @brief       I2C0_IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
                I2C0_IRQ();
 * @endcode     
 * @par         Modify
 *              __weak void I2C0_IRQ(void)
 *******************************************************************************
 */
__weak void I2C0_IRQ(void)
{
    I2C_Timeout_Handler(I2C0);

    I2C_ByteMode_Event_Handler(I2C0);
}
#endif

#if (defined(I2C1_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       I2C1_IRQ
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
                I2C1_IRQ();
 * @endcode     
 * @par         Modify
 *              __weak void I2C0_IRQ(void)
 *******************************************************************************
 */
__weak void I2C1_IRQ(void)
{
    I2C_Timeout_Handler(I2C1);

    I2C_ByteMode_Event_Handler(I2C1);
}
#endif

#if (defined(USB_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       USB interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void USB_IRQ(void)
{
    uint32_t   USBIRQ_Status;
    uint32_t   USBEPIRQ_Status;

    USBIRQ_Status = USB_GetITAllFlagStatus() & USB_GetITIEAllStatus();

    //====================================================================
    //Bus Event Relationship Flag
    if( (USBIRQ_Status & USB_IT_BUS)!=0)
    {
        //---------------------------------------------------------------------
        //Detect Bus Suspend 
        if(( USBIRQ_Status & USB_IT_BUS_SUSF)==USB_IT_BUS_SUSF)
        {
            USB_ClearITFlag( USB_IT_BUS_SUSF | USB_IT_BUS);

            // To do ......

        }
        else
        {
            //---------------------------------------------------------------------
            //Detect Bus Reset.
            if((USBIRQ_Status & USB_IT_BUS_RSTF) == USB_IT_BUS_RSTF)
            {
                USB_ClearITFlag(USB_IT_BUS_RSTF);

                //To do ......
            }
            //-----------------------------------------------------------------
            //Detect Bus Resume
            else if((USBIRQ_Status & USB_IT_BUS_RSMF)==USB_IT_BUS_RSMF)
            {
                USB_ClearITFlag(USB_IT_BUS_RSMF);

                //To do ......
            }
            //-----------------------------------------------------------------
            //Device wakeup by bus reset.
            else if((USBIRQ_Status & USB_IT_BUS_RWKF)==USB_IT_BUS_RWKF)
            {
                USB_ClearITFlag(USB_IT_BUS_RWKF);

                //To do ......
            }
        }
    }
    //=====================================================================
    //LPM ACK flag.
    else if( USBIRQ_Status & USB_IT_LPM)
    {
        if( USB_GetLPMbRemoteWake()!=0)
        {
            //-----------------------------------------------------
            // LPM allow remote wakeup

            //To do ......
        }
        else
        {
            //------------------------------------------------------
            // LPM no allow remote wakeup

            //To do ......
        }

        USB_ClearITFlag( USB_IT_LPM);
    }
    //=====================================================================
    //SOF flag
    else if( USBIRQ_Status & USB_IT_SOF)
    {
        USB_ClearITFlag( USB_IT_SOF);

        //To do......
    }
    //=======================================================================
    //Endpoint Relationship flag
    else
    {
        //--------------------------------------------------------
        //Endpoint 0 control
        if((USBIRQ_Status & USB_IT_EP1) == USB_IT_EP1)
        {
            USBEPIRQ_Status = USB_GetEndpointITFlagStatus(USB_EP0);

            //-----------------------------------------------------
            // Transmission done flag.
            if((USBEPIRQ_Status & USB_EP_ITFLAG_TXDONE)==USB_EP_ITFLAG_TXDONE)
            {
                USB_ClearEndpointFlag( USB_EP0 , USB_EP_FLAG_TXDONE);

                // To do ......
            }
            //-----------------------------------------------------
            // Receiving done flag.
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_RXDONE)==USB_EP_ITFLAG_RXDONE)
            {
                USB_ClearEndpointFlag( USB_EP0 , USB_EP_FLAG_RXDONE);

                // To do ......
            }
            //-----------------------------------
            // Transmission NAK flag
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_TXNAK)==USB_EP_ITFLAG_TXNAK)
            {
                USB_ClearEndpointFlag( USB_EP0 , USB_EP_FLAG_TXNAK);

                // To do ......
            }
            //-----------------------------------
            // Reciving NAK flag
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_RXNAK)==USB_EP_ITFLAG_RXNAK)
            {
                USB_ClearEndpointFlag( USB_EP0 , USB_EP_FLAG_RXNAK);

                //To do ......
            }
            //-----------------------------------
            // Transmission STALL flag
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_TXSTALL)==USB_EP_ITFLAG_TXSTALL)
            {
                USB_ClearEndpointFlag( USB_EP0 , USB_EP_FLAG_TXSTALL);

                //To do ......
            }
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_RXSTALL)==USB_EP_ITFLAG_RXSTALL)
            {
                USB_ClearEndpointFlag( USB_EP0 , USB_EP_FLAG_RXSTALL);

                //To do ......
            }
        }
        //----------------------------------------------------------
        //Endpoint 1 (If Endpoint is RX double buffer)
        if((USBIRQ_Status & USB_IT_EP1) == USB_IT_EP1)
        {
            USBEPIRQ_Status = USB_GetEndpointITFlagStatus(USB_EP1);

            //-----------------------------------------------------
            // RX Buffr0 receiving done flag.
            if((USBEPIRQ_Status & USB_EP_ITFLAG_DBUFFER0_RXDONE)==USB_EP_ITFLAG_DBUFFER0_RXDONE)
            {                     
                USB_ClearEndpointFlag( USB_EP1 , USB_EP_FLAG_DBUFFER0_RXDONE);

                // To do ......
            }
            //-----------------------------------------------------
            // RX Buffer1 receiving done flag.
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_DBUFFER1_TXDONE)==USB_EP_ITFLAG_DBUFFER1_TXDONE)
            {
                USB_ClearEndpointFlag( USB_EP1 , USB_EP_FLAG_DBUFFER1_RXDONE);

                // To do ......
            }
        }
        //----------------------------------------------------------
        //Endpoint 2 (If Endpoint is TX double buffer)
        if((USBIRQ_Status & USB_IT_EP2) == USB_IT_EP2)
        {
            USBEPIRQ_Status = USB_GetEndpointITFlagStatus(USB_EP2);

            //-----------------------------------------------------
            // TX Buffer0 transmission done.
            if((USBEPIRQ_Status & USB_EP_ITFLAG_DBUFFER0_TXDONE)==USB_EP_ITFLAG_DBUFFER0_TXDONE)
            {
                USB_ClearEndpointFlag( USB_EP2 , USB_EP_FLAG_DBUFFER0_TXDONE);

                // To do ......
            }
            //-----------------------------------------------------
            // RX Buffer1 transmission done.
            else if((USBEPIRQ_Status & USB_EP_ITFLAG_DBUFFER1_TXDONE)==USB_EP_ITFLAG_DBUFFER1_TXDONE)
            {
                USB_ClearEndpointFlag( USB_EP2 , USB_EP_FLAG_DBUFFER1_TXDONE);

                // To do ......
            }
        }
        //===========================================================
        //USB_EP3 ~ USB_EP7 refer to USB_EP1 ~ USB_EP2

    }
}
#endif

#if (defined(APX_Base) && defined(IRQHandler_Driver_Level_))
/**
 *******************************************************************************
 * @brief       APX interrupt function.
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
__weak void APX_IRQ(void)
{
    #if defined(MG32_3RD) || defined(MG32_4TH)
    // ------------------------------------------------------------------------
    // CCL0F
    if (APX_GetSingleFlagStatus(APX, APX_CCL0F) == DRV_Happened)
    {
        // CCL-0 output low-to-high detect flag. 
        // To do...
        
        APX_ClearFlag (APX, APX_CCL0F);
    }
    // CCL1F
    if (APX_GetSingleFlagStatus(APX, APX_CCL1F) == DRV_Happened)
    {
        // CCL-1 output low-to-high detect flag. 
        // To do...

        APX_ClearFlag (APX, APX_CCL1F);
    }
  
    #endif

    #if defined(MG32_4TH)
    // ------------------------------------------------------------------------
    // ASB0_TCF
    if (APX_GetSingleFlagStatus(APX, APX_ASB0_TCF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB0_TCF);
    }
    // ASB1_TCF
    if (APX_GetSingleFlagStatus(APX, APX_ASB1_TCF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB1_TCF);
    }
    // ASB2_TCF
    if (APX_GetSingleFlagStatus(APX, APX_ASB2_TCF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB2_TCF);
    }
    // ASB3_TCF
    if (APX_GetSingleFlagStatus(APX, APX_ASB3_TCF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB3_TCF);
    }
    // ------------------------------------------------------------------------
    // ASB0_TXF
    if (APX_GetSingleFlagStatus(APX, APX_ASB0_TXF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB0_TXF);
    }
    // ASB1_TXF
    if (APX_GetSingleFlagStatus(APX, APX_ASB1_TXF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB1_TXF);
    }
    // ASB2_TXF
    if (APX_GetSingleFlagStatus(APX, APX_ASB2_TXF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB2_TXF);
    }
    // ASB3_TXF
    if (APX_GetSingleFlagStatus(APX, APX_ASB3_TXF) == DRV_Happened)
    {
        // ASB channel-0 transmission complete flag.
        // To do...

        APX_ClearFlag (APX, APX_ASB3_TXF);
    }
    #endif
}
#endif

