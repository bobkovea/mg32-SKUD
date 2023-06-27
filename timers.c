#include "timers.h"

void TIM_Config()
{
	TM_TimeBaseInitTypeDef TM_TimeBase_InitStruct;
    TM_TimeBaseStruct_Init(&TM_TimeBase_InitStruct);
	
	// TM_READ_GERKON
    TM_TimeBase_InitStruct.TM_Period = TM_READ_GERKON_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_READ_GERKON_PRESCALER - 1;
    TM_TimeBase_Init(TM_READ_GERKON, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_READ_GERKON, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_READ_GERKON, ENABLE); // включаем общие прерывания таймера
	
	// TM_PROTECTION_DELAY
    TM_TimeBase_InitStruct.TM_Period = TM_PROTECTION_DELAY_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_PROTECTION_DELAY_PRESCALER - 1;
    TM_TimeBase_Init(TM_PROTECTION_DELAY, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_PROTECTION_DELAY, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_PROTECTION_DELAY, ENABLE); // включаем общие прерывания таймера

	// TM_MUTE_SOUND
    TM_TimeBase_InitStruct.TM_Period = TM_MUTE_SOUND_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_MUTE_SOUND_PRESCALER - 1;
    TM_TimeBase_Init(TM_MUTE_SOUND, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_MUTE_SOUND, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_MUTE_SOUND, ENABLE); // включаем общие прерывания таймера
	
	// TM_READ_KEY
    TM_TimeBase_InitStruct.TM_Period = TM_READ_KEY_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_READ_KEY_PRESCALER - 1;
    TM_TimeBase_Init(TM_READ_KEY, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_READ_KEY, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_READ_KEY, ENABLE); // включаем общие прерывания таймера

	// TM_INDICATION
    TM_TimeBase_InitStruct.TM_Period = TM_INDICATION_PERIOD - 1; 
    TM_TimeBase_InitStruct.TM_Prescaler = TM_INDICATION_PRESCALER - 1;
    TM_TimeBase_Init(TM_INDICATION, &TM_TimeBase_InitStruct);
	TM_IT_Config(TM_INDICATION, TMx_TIE_IE, ENABLE); // включаем прерывание таймера по переполнению
	TM_ITEA_Cmd(TM_INDICATION, ENABLE); // включаем общие прерывания таймера
		
	// TM_READ_KEY
	NVIC_EnableIRQ(TM1x_IRQn);
	NVIC_SetPriority(TM1x_IRQn, 0); // программный one-wire не должен прерываться

	// TM_INDICATION
	NVIC_EnableIRQ(TM3x_IRQn);
	NVIC_SetPriority(TM3x_IRQn, 2);
	
	// TM_MUTE_SOUND
	NVIC_EnableIRQ(TM10_IRQn); 
	NVIC_SetPriority(TM10_IRQn, 3);
	
	// TM_READ_GERKON и TM_PROTECTION_DELAY
	NVIC_EnableIRQ(TM0x_IRQn); 
	NVIC_SetPriority(TM0x_IRQn, 4); 
}

//----------------------------------------------------------------------------------------
// Обработчики прерываний
//----------------------------------------------------------------------------------------
void TM0x_IRQHandler(void)
{
	// прерывание по переполнению таймера 00 (только оно разрешено)
	if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm00_b0)
	{
		TIM00_Callback();
		TM_ClearFlag (TM00, TMx_TOF);
	}		
	// прерывание по переполнению таймера 01 (только оно разрешено)
	else if(__DRV_EXIC_GET_ID12_SOURCE() & EXIC_SRC3_ID12_tm01_b0)
	{
		TIM01_Callback();
		TM_ClearFlag (TM01, TMx_TOF);		
	}
}

void TM10_IRQHandler(void)
{
	// прерывание по переполнению таймера 10 (только оно разрешено)
	TIM10_Callback();
	TM_ClearFlag (TM10, TMx_TOF);
}

void TM1x_IRQHandler(void)
{
	// прерывание по переполнению таймера 16 (только оно разрешено)
	TIM16_Callback();
	TM_ClearFlag (TM16, TMx_TOF);
}

void TM3x_IRQHandler(void)
{
	// прерывание по переполнению таймера 36 (только оно разрешено)
	TIM36_Callback();
	TM_ClearFlag (TM36, TMx_TOF);

}

