#include "MG32x02z_TM_DRV.h"
#include "MG32x02z_EXIC_DRV.H"

 void TM00_IRQ(void);
 void TM01_IRQ(void);
 void TM10_IRQ(void);
 void TM16_IRQ(void);
 
__weak void TIM00_Callback(void) {
 
 }

__weak void TIM01_Callback(void) {
 
 }

__weak void TIM10_Callback(void) {
 
 }

 __weak void TIM16_Callback(void) {
 
 }
 
// void TM0x_IRQHandler(void) {
//	 if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm00_b0 )
//		TM00_IRQ();
//	 if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm01_b0)
//		TM01_IRQ();
//}
// 
// void TM10_IRQHandler(void) {
//		TM10_IRQ();
//}

 
void TM00_IRQ(void)
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
		
        TIM00_Callback();
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

void TM01_IRQ(void)
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
		
        TIM01_Callback();
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



void TM10_IRQ(void)
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
		
        TIM10_Callback();
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

void TM16_IRQ(void)
{

    // 2nd / Main counter
    if (TM_GetSingleFlagStatus(TM16, TMx_TUF2) == DRV_Happened)
    {
        // 2nd Timer underflow flag
        // To do...
        
        TM_ClearFlag (TM16, TMx_TUF2);
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
		
        TIM16_Callback();
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