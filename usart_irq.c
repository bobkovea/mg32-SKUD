#include "MG32x02z__Common_DRV.h"
#include "MG32x02z_URT_DRV.h"

void URT0_IRQ(void);

__weak void URT_Rx_Callback(void) {
	
}

__weak void URT_Tx_Callback(void) {
	
}

//void URT0_IRQHandler(void) {
//	URT0_IRQ();
//}

void URT0_IRQ(void)
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
            URT_ClearITFlag(URT0,URT_IT_CALC);
        }
        
        URT_ClearITFlag(URT0,URT_IT_UG);
    }
    if((URT_ITFlag & URT_IT_RX) == URT_IT_RX)
    {
        //---when RX Data Register have data---//
		
		URT_Rx_Callback();
		URT_ClearITFlag(URT0,URT_IT_RX);

    }
    if((URT_ITFlag & URT_IT_TX) == URT_IT_TX)
    {
        // To do ......
		URT_Tx_Callback();
        
        URT_ClearITFlag(URT0,URT_IT_TX);          // Write TXData auto clear TX flag.
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
//        if((URT_ITFlag & URT_IT_TUDR) == URT_IT_TUDR)
//        {
//            //To do......
//            URT_ClearITFlag(URT0,URT_IT_TUDR);
//        }
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
