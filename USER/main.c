#include "includes.h"
#include <stdbool.h>

#define TRUE 1;
#define FALSE 0;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_Speed              100000

#define SCL_H         GPIOB->BSRR = GPIO_Pin_7
#define SCL_L         GPIOB->BRR  = GPIO_Pin_7 
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_6
#define SDA_L         GPIOB->BRR  = GPIO_Pin_6

#define SCL_read      GPIOB->IDR  & GPIO_Pin_7
#define SDA_read      GPIOB->IDR  & GPIO_Pin_6


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/**/
void I2C_delay(void)
{        
   u8 i=150; //????????        ,??????5????
   while(i) 
   { 
     i--; 
   } 
}

bool I2C_Start(void)
{
        SDA_H;
        SCL_H;
        I2C_delay();
        if(!SDA_read)return FALSE;        //SDA?????????,??
        SDA_L;
        I2C_delay();
        if(SDA_read) return FALSE;        //SDA??????????,??
        SDA_L;
        I2C_delay();
        return TRUE;
}

void I2C_Stop(void)
{
        SCL_L;
        I2C_delay();
        SDA_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        SDA_H;
        I2C_delay();
}

void I2C_Ack(void)
{        
        SCL_L;
        I2C_delay();
        SDA_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        SCL_L;
        I2C_delay();
}

void I2C_NoAck(void)
{        
        SCL_L;
        I2C_delay();
        SDA_H;
        I2C_delay();
        SCL_H;
        I2C_delay();
        SCL_L;
        I2C_delay();
}

bool I2C_WaitAck(void)          //???:=1?ACK,=0?ACK
{
        SCL_L;
        I2C_delay();
        SDA_H;                        
        I2C_delay();
        SCL_H;
        I2C_delay();
        if(SDA_read)
        {
      SCL_L;
      return FALSE;
        }
        SCL_L;
        return TRUE;
}

void I2C_SendByte(u8 SendByte) //????????//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
                SCL_H;
        I2C_delay();
    }
    SCL_L;
}

u8 I2C_ReceiveByte(void)  //????????//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;                                
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
          SCL_H;
      I2C_delay();        
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}

bool I2C_FRAM_BufferWrite(u8 Buffer, u8 FRAM_ADDRESS)
{


    if (!I2C_Start()) return FALSE;
    I2C_SendByte(FRAM_ADDRESS);//??????+??? 
    if (!I2C_WaitAck())
        {
                I2C_Stop(); 
                return FALSE;
        }
    I2C_SendByte(Buffer);   //??????      
        I2C_WaitAck();        
          
        I2C_Stop();

        return TRUE;
}


//??1???         
bool I2C_FRAM_BufferRead(u8* pBuffer, u8 FRAM_ADDRESS)
{                
        
        if (!I2C_Start()) return FALSE;

    I2C_SendByte(FRAM_ADDRESS | 0x01);
    I2C_WaitAck();

      *pBuffer = I2C_ReceiveByte();
      I2C_NoAck();

    I2C_Stop();
    return TRUE;
}


int main(void)
{
	unsigned char readbyte = 0x00;
	unsigned char temp_readbyte = 0x00;
	unsigned char sucess = 0;
	SysTick_Init();
	GPIO_Config();
	USART2_Config(); 
	//TIM3_PWM_Config();
	//I2C_Config();
	//CAN_Config();
	//ADC_Config();
	//EXTI_PB15_Config();		

	GPIO_SetBits(GPIOE, GPIO_Pin_15);
	
	Delay_us(1000);
	
	GPIO_ResetBits(GPIOE, GPIO_Pin_15);
	
	sucess = I2C_FRAM_BufferWrite( 0xFF, 0x40 );
	
	while (1)
	{
		temp_readbyte = readbyte;
		sucess = I2C_FRAM_BufferRead( &readbyte, 0x40 );
		
		Delay_us(100);
		
		if (temp_readbyte != readbyte)
		{	
			sucess = I2C_FRAM_BufferWrite( 0x00, 0x42 );
			Delay_us(500);		
			sucess = I2C_FRAM_BufferWrite( 0xFF, 0X42 );
			Delay_us(500);
		}
		
		
// 		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)) 
// 		{
// 			GPIO_ResetBits(GPIOE, GPIO_Pin_15);
// 			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
// 			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
// 			GPIO_ResetBits(GPIOC, GPIO_Pin_12);
// 			GPIO_ResetBits(GPIOD, GPIO_Pin_8);			
// 			Delay_us(5000);
// 		}
// 		else
// 		{
// 			GPIO_SetBits(GPIOE, GPIO_Pin_15);
// 			GPIO_SetBits(GPIOA, GPIO_Pin_4);
// 			GPIO_SetBits(GPIOC, GPIO_Pin_11);
// 			GPIO_SetBits(GPIOC, GPIO_Pin_12);
// 			GPIO_SetBits(GPIOD, GPIO_Pin_8);
// 		}
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
