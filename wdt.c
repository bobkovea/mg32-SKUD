#include "wdt.h"

//----------------------------------------------------------------------------------------
// Функция запускает WDT, время от ~7 мс до ~32 секунд
//----------------------------------------------------------------------------------------
void wdt_enable(IWDT_DIVS_TypeDef divider)
{
    UnProtectModuleReg(IWDTprotect); // разблокировать изменения в регистрах IWDT
    IWDT_Divider_Select(divider); // изменить предделитель IWDT                             
    IWDT_Cmd(ENABLE); // запустить IWDT                                            
    ProtectModuleReg(IWDTprotect); // разблокировать изменения в регистрах IWDT
}
//----------------------------------------------------------------------------------------
// Функция перезапускает сторожевой таймер
//----------------------------------------------------------------------------------------
void wdt_reset(void)
{
    IWDT_RefreshCounter();                    
}

//----------------------------------------------------------------------------------------
// Функция отключает WDT
//----------------------------------------------------------------------------------------
void wdt_disable(void)
{
    UnProtectModuleReg(IWDTprotect); // разблокировать изменения в регистрах IWDT
    IWDT_Cmd(DISABLE); // остановить IWDT       
    ProtectModuleReg(IWDTprotect); // разблокировать изменения в регистрах IWDT
}


// 		События (2 китайских предупреждения и перезагрузка)

//    while(IWDT_GetSingleFlagStatus(IWDT_EW1F) == DRV_UnHappened);   // Wait IWDT early wakeup-1 happened
//    IWDT_ClearFlag(IWDT_EW1F);                                      // Clear EW1F flag 
//    
//    while(IWDT_GetSingleFlagStatus(IWDT_EW0F) == DRV_UnHappened);   // Wait IWDT early wakeup-0 happened
//    IWDT_ClearFlag(IWDT_EW0F);                                      // Clear EW0F flag
//    
//    while(IWDT_GetSingleFlagStatus(IWDT_TF) == DRV_UnHappened);     // Wait IWDT timer timeout happened
//    IWDT_ClearFlag(IWDT_TF);                                        // Clear TF flag



// как включить прерывания IWDT???




