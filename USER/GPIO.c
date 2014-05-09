#include "GPIO.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*
	RankRight_1 -- PA4  
	RankRight_2 -- PE7
	RankRight_3 -- PE8
	RankRight_4 -- PE9
	RankRight_5 -- PE10
	RankRight_6 -- PB10
	RankRight_7 -- PB11
	RankRight_8 -- PB13
	RankRight_9 -- PB15
	RankRight_10 -- PB12
	RankRight_11 -- PB14
	
	LineRight_1 -- PC11
	LineRight_2 -- PD4
	LineRight_3 -- PE3
	LineRight_4 -- PE2
	LineRight_5 -- PE5
	LineRight_6 -- PE4
	LineRight_7 -- PC13
	LineRight_8 -- PE6
	LineRight_9 -- PC15
	LineRight_10 -- PC14
	LineRight_11 -- PA0

	RankContrary_1 -- PD8
	RankContrary_2 -- PD10
	RankContrary_3 -- PD12
	RankContrary_4 -- PD14
	RankContrary_5 -- PC6
	RankContrary_6 -- PC8
	RankContrary_7 -- PA8
	RankContrary_8 -- PA10
	RankContrary_9 -- PA12
	RankContrary_10 -- IO_Ext_5
	RankContrary_11 -- IO_Ext_6
	
	LineContrary_1 -- PC12
	LineContrary_2 -- PC10
	LineContrary_3 -- PA15
	LineContrary_4 -- PA11
	LineContrary_5 -- PA9
	LineContrary_6 -- PC9
	LineContrary_7 -- PC7
	LineContrary_8 -- PD15
	LineContrary_9 -- PD13
	LineContrary_10 -- PD11
	LineContrary_11 -- PD9
	*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB \
													| RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE );
													
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & (~(GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 \
																									| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_13 | GPIO_Pin_14)) ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 \
																									| GPIO_Pin_7) ) ;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 \
																									| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5) ) ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1) ) ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//I2C GPIO
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
