#ifndef __GLOBAL_VALUES_H__
#define __GLOBAL_VALUES_H__
#include "stm32f10x.h"
#include "protocol.h"
	unsigned short int CCR1_Val = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	extern unsigned short USART_RX_STA;
	unsigned char len=0;	
	unsigned char t=0;	
	unsigned int temp;
	extern unsigned char  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
	extern unsigned short int	TIM5CH1_CAPTURE_VAL;	//输入捕获值	
	


	// 局部变量，用于存从flash读到的电压值			 
	float ADC_ConvertedValueLocal; 
	
	unsigned char I2CValue1 = 0xFF;//I2C addressed 0x40
	unsigned char I2CValue2 = 0xEF;//I2c addressed 0x42, for StartLED is connected to the p4 pin;
	
	unsigned char IDOfPCB = 0;
	unsigned char RunMode = 0;
	unsigned char I2CStatus = 0;
	PROTOCOL_t gU2RecvBuff;
#endif