#include "includes.h"

int main(void)
{
	
	SysTick_Init();
	GPIO_Config();
	USART2_Config(); 
	//TIM3_PWM_Config();
	//I2C_Config();
	//CAN_Config();
	//ADC_Config();
	//EXTI_PB15_Config();		
	
	while (1)
	{
		;
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
			
// 			if(USART_RX_STA&0x8000)
// 			{					   
// 				len=USART_RX_STA&0x3f;//得到此次接收到的数据长度
// 				printf("\r\n您发送的消息为:\r\n\r\n");
// 				for(t=0;t<len;t++)
// 				{
// 					USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
// 					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
// 				}
// 				printf("\r\n\r\n");//插入换行
// 				USART_RX_STA=0;
// 			}