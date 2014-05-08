#include "includes.h"
PROTOCOL_t gU2RecvBuff[2];
int main(void)
{
	SysTick_Init();
	GPIO_Config();
	
	/* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	USART2_Config(); 
	//TIM3_PWM_Config();
	//I2C_Config();
	//CAN_Config();
	ADC1_Config();
	//EXTI_PB15_Config();	
	printf("\r\n串口测试\r\n\r\n");
	//USART_SendData(USART2, USART_RX_BUF[t]);//向串口2发送数据，未测试；
	while (1)
	{
		for(i=0;i<11;i++)
		{
			ADC_ConvertedValueLocal = (float)ADC_ConvertedValue[i]/4096*2.5; // 读取转换的AD
			Delay_us(100);                             // 延时 
			//printf("0x%04X ", ADC_ConvertedValue[i]);  
			printf("-->%fV", ADC_ConvertedValueLocal); ;
		}
		printf("\r \n");
		GPIO_SetBits(GPIOA, GPIO_Pin_All & (~(GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 \
																			| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_13 | GPIO_Pin_14)));	
		GPIO_SetBits(GPIOB, GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7) ) );
		GPIO_SetBits(GPIOC, GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5) )); 
		GPIO_SetBits(GPIOD, GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1) ) );
		GPIO_SetBits(GPIOE, GPIO_Pin_All);			
		Delay_us(500);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_All & (~(GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 \
																			| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_13 | GPIO_Pin_14)));	
		GPIO_ResetBits(GPIOB, GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7) ) );
		GPIO_ResetBits(GPIOC, GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5) )); 
		GPIO_ResetBits(GPIOD, GPIO_Pin_All & ( ~ (GPIO_Pin_0 | GPIO_Pin_1) ) );
		GPIO_ResetBits(GPIOE, GPIO_Pin_All);
		Delay_us(1000);
	}
}




// 			LED1 (ON) ;
// 			Delay_us(1);
// 			LED1 (OFF);
// 			GPIO5( ON );				
// 			Delay_us(500);    
// 			GPIO5( OFF );
// 			TIM_SetCompare1(TIM3,TIM_GetCapture1(TIM3)+100);
// 			if(TIM_GetCapture1(TIM3)==900)TIM_SetCompare1(TIM3,600);	
			
			//for(i=0;i<=399;i++)
			//{
				//CCR1_Val = 600 + i;
				//TIM3_PWM_Init ();
				//for(j=0;j<10000;j++);
			//}
			//for(i=0;i<=399;i++)
			//{
				//CCR1_Val = 999 - i;
				//TIM3_PWM_Init ();
				//for(j=0;j<10000;j++);
			//}		

			//printf("\r\n this is a printf demo \r\n");
			//USART1_printf(USART1, "\r\n This is a USART1_printf demo \r\n");
			//USART1_printf(USART1, "\r\n ("__DATE__ " - " __TIME__ ") \r\n");
			
