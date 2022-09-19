

/**
 ******************************************************************************
 *
 * @file        MG32x02z__IRQHandler.c
 * @brief       The demo IRQHandler C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.21
 * @date        2022/01/24
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


/* Wizard menu ---------------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


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
            __weak SPI_HandleTypeDef        mSPI;
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
                __weak SDT_HandleTypeDef    mSDT;
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
        __weak SPI_HandleTypeDef        mSPI;
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
            __weak CCL_HandleTypeDef 	mCCL0;
            __weak CCL_HandleTypeDef 	mCCL1;
            __weak SDT_HandleTypeDef 	mSDT;
        #endif
        // --------------------------------------------------------------------
    #endif
    // ------------------------------------------------------------------------
    
#endif

/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Exported variables --------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */


/* External vairables --------------------------------------------------------*/
void IncTick(void);             // (Driver level) Please reference 
                                // "MG32x02z__Common_DRV.c" file in 'Driver' option.
                                
void MID_IncTick(void);         // (Middleware level) Please reference 
                                // "MG32x02z_Common_MID.c" file in 'Driver' option.
/* USER CODE BEGIN Private includes */
// to do ...
/* USER CODE END Private includes */




/**
 *******************************************************************************
 * @brief	    An NMI can be signalled by a peripheral or triggered by software. 
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
 * @brief	    A supervisor call (SVC) is an exception that is triggered by the 
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
 * @brief	    PendSV is an interrupt-driven request for system-level service. 
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
 * @brief	    If the device implements the SysTick timer, a SysTick exception 
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
 * @brief	    WWDT: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    SYS: An interrupt, or IRQ, is an exception signalled by a 
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
    #if defined(MG32x02z_SYS_IWDT_IRQ_)
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
    #endif
    // ------------------------------------------------------------------------
    // PW ISR
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_SYS_PW_IRQ_)
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
    #endif
    // ------------------------------------------------------------------------
    // RTC ISR
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_SYS_RTC_IRQ_)
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
    #endif
    // ------------------------------------------------------------------------
    // CSC ISR
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_SYS_CSC_IRQ_)
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
    #endif
    // ------------------------------------------------------------------------
    // APB ISR
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_SYS_APB_IRQ_)
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
    #endif
    // ------------------------------------------------------------------------
    // MEM ISR
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_SYS_MEM_IRQ_)
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
    #endif
    // ------------------------------------------------------------------------
    // EMB ISR
    // ------------------------------------------------------------------------
    #if (defined(MG32_3RD) || defined(MG32_1ST))
        #if defined(MG32x02z_SYS_EMB_IRQ_)
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
    #endif
    
    /* USER CODE BEGIN SYS_IRQ 1 */
    // to do...
    /* USER CODE END SYS_IRQ 1 */

}

#endif

/**
 *******************************************************************************
 * @brief	    EXINT0: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    EXINT1: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    EXINT2: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    EXINT3: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    COMP: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    DMA: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    ADC: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    DAC: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    TM0x: An interrupt, or IRQ, is an exception signalled by a 
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
    #if defined(MG32x02z_TM0x_TM00_IRQ_)
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


            /* USER CODE END TM00_IRQ 1 */
        }
    #endif

    // ------------------------------------------------------------------------
    // TM01 ISR
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_TM0x_TM01_IRQ_)
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
    #endif

    /* USER CODE BEGIN TM0x_IRQ 1 */
    // to do...
    /* USER CODE END TM0x_IRQ 1 */
}
#endif

/**
 *******************************************************************************
 * @brief	    TM10: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    TM1x: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    TM20: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    TM2x: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    TM3x: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    URT0: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    URT123: An interrupt, or IRQ, is an exception signalled by a 
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
    //  MG32_4TH : MG32F02V032, UD8F
    // ------------------------------------------------------------------------
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
    // ------------------------------------------------------------------------
    // URT2 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_1ST : MG32F02A132, MG32F02A072, MA862
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_URT123_URT2_IRQ_) 
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
    #if defined(MG32x02z_URT123_URT3_IRQ_) 
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
 * @brief	    URT4x: An interrupt, or IRQ, is an exception signalled by a 
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
    //  MG32_4TH : MG32F02V032, UD8F
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_URT4x_URT4_IRQ_) 
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
    #endif
    
    // ------------------------------------------------------------------------
    // URT5 ISR
    // ------------------------------------------------------------------------
    // Apply MCU 
    //  MG32_3RD : MG32F02A128, MG32F02A064, MG32F02U128, MG32F02U064
    // ------------------------------------------------------------------------
    #if defined(MG32x02z_URT4x_URT5_IRQ_)
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
    #if defined(MG32x02z_URT4x_URT6_IRQ_)
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
    #if defined(MG32x02z_URT4x_URT7_IRQ_)
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
 * @brief	    SPI0: An interrupt, or IRQ, is an exception signalled by a 
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
        MID_SPI_IRQHandler(&mSPI);
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
 * @brief	    I2C0: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    I2Cx: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    USB: An interrupt, or IRQ, is an exception signalled by a 
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
 * @brief	    APX: An interrupt, or IRQ, is an exception signalled by a 
 *              peripheral, or generated by a software request. 
 * @details     APX handles port ASB, SDT or CCLx interrupt.
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
        else 
        {
            MID_APX_SDT_IRQHandler(&mSDT);            
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






