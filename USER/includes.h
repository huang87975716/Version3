#ifndef __INCLUDES_H__
	#define __INCLUDES_H__
	#include "stm32f10x.h"
	#include "gpio.h"
	#include "SysTick.h"
	//#include "exti.h"
	#include "usart.h"
	#include "stdio.h"
	#include "pwm_output.h"
	#include "timer.h"
	#include "matrix_motor.h"
	#include "protocol.h"
	
	u16 CCR1_Val = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	extern u16 USART_RX_STA;
	u8 len=0;	
	u8 t=0;	
	unsigned int temp;
	extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
	extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值	
#endif
