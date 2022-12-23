#include "gpio.h"

void InitPinBase(Pin_Struct* PINX)
{
	GPIO_PinHighSpeedMode_Cmd(PINX, DISABLE);
	GPIO_PinInverse_Cmd(PINX, DISABLE);
	GPIO_PinOutputDrive_Select(PINX , PINX_OUTDrive_Level0);
	GPIO_PinInFilterDivider_Select(PINX , PINX_FilterDivider_Bypass);
}

void InitPinPPO(Pin_Struct* PINX)
{	
	GPIO_PinMode_Select(PINX, PINX_Mode_PushPull_O);
	GPIO_PinPUResister_Cmd(PINX, DISABLE);
	InitPinBase(PINX);
	GPIO_PinFunction_Select(PINX, 0);
}

void InitPinUsartTx(Pin_Struct* PINX)
{	
	GPIO_PinMode_Select(PINX, PINX_Mode_PushPull_O);
	GPIO_PinPUResister_Cmd(PINX, ENABLE);
	InitPinBase(PINX);
	GPIO_PinFunction_Select(PINX, ALTER_FUNC_PC0_TX0);
}

void InitPinUsartRx(Pin_Struct* PINX)
{	
	GPIO_PinMode_Select(PINX, PINX_Mode_OpenDrain_O);
	GPIO_PinPUResister_Cmd(PINX, ENABLE);
	InitPinBase(PINX);
	GPIO_PinFunction_Select(PINX, ALTER_FUNC_PC0_RX0);
}

void InitPinDI(Pin_Struct* PINX, PullupState_t Pullup_Mode)
{
	GPIO_PinMode_Select(PINX, PINX_Mode_Digital_I);
	GPIO_PinPUResister_Cmd(PINX, (FunctionalState)Pullup_Mode);
	InitPinBase(PINX);
	GPIO_PinFunction_Select(PINX, 0);
}

void GPIO_Config()
{
	BACKL_PIN = INITIAL_RESET;
	INDLED_PIN = INITIAL_RESET;
	DO_PIN = INITIAL_RESET;
	STALED_PIN = INITIAL_SET;
	BUZZER_PIN = INITIAL_RESET;
	REDE_PIN = INITIAL_RESET;
	InitPinDI(PINB(0), PULLUP_ENABLE);
	InitPinPPO(PINB(1));
	InitPinPPO(PINB(2));
	InitPinDI(PINB(3), PULLUP_ENABLE);
	InitPinPPO(PINB(8));
	InitPinPPO(PINB(9));
	InitPinPPO(PINB(10));
	InitPinPPO(PINB(11));
	InitPinUsartTx(PINC(0));
	InitPinUsartRx(PINC(1));
}


	