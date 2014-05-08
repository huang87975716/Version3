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
	#include "adc.h"
	#include "PCF8574_I2C.h"
	
	u16 CCR1_Val = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	extern u16 USART_RX_STA;
	u8 len=0;	
	u8 t=0;	
	unsigned int temp;
	extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
	extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
	
	// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����flash
	extern __IO u16 ADC_ConvertedValue[11];

	// �ֲ����������ڴ��flash�����ĵ�ѹֵ			 
	float ADC_ConvertedValueLocal;  
#endif
