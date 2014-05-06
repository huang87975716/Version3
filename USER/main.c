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
	//ADC_Config();
	//EXTI_PB15_Config();	
	printf("\r\n您发送的消息为:\r\n\r\n");
	//USART_SendData(USART2, USART_RX_BUF[t]);//向串口2发送数据
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
			
