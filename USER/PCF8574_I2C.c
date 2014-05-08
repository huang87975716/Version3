#include "PCF8574_I2C.h"
/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 *          |  PB6-I2C1_SCL		|
 *          |  PB7-I2C1_SDA   |
**********************************************************************************/

#define I2C_Speed              50000
/*
 * 函数名：I2C_GPIO_Config
 * 描述  ：I2C1 I/O配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* 使能与 I2C1 有关的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);  
    
  /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 * 函数名：I2C_Configuration
 * 描述  ：I2C 工作模式配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_Mode_Config(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  I2C_DeInit(I2C1);
	/* I2C 配置 */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;//当STM32作为从机时候的I2C地址，本例为STM32为主机，可以设置为0
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* 使能 I2C1 */
  I2C_Cmd(I2C1, ENABLE);

  /* I2C1 初始化 */
  I2C_Init(I2C1, &I2C_InitStructure);

	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(I2C1, ENABLE);    
}

/*
 * 函数名：I2C_PCF8574_Init
 * 描述  ：I2C 外设(PCF8574)初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void I2C_PCF8574_Init(void)
{
  I2C_GPIO_Config(); 
  I2C_Mode_Config();
}


/*
 * 函数名：I2C_PCF8574_ByteWrite
 * 描述  ：写一个字节到I2C PCF8574中
 * 输入  ：-pBuffer 缓冲区指针
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */
void I2C_PCF8574_ByteWrite(uint8_t WriteBuffer, uint8_t PCF8574_ADDRESS)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));  

  /* Send PCF8574 address for write */
  I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the byte to be written */
  I2C_SendData(I2C1, WriteBuffer); 
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
}


/*
 * 函数名：I2C_PCF8574_BufferRead
 * 描述  ：从PCF8574里面读取一块数据。 
 * 输入  ：-pBuffer 存放从PCF8574读取的数据的缓冲区指针。
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */
uint8_t I2C_PCF8574_ByteRead(uint8_t PCF8574_ADDRESS)
{  
  uint8_t ReadBuffer;
	//*((u8 *)0x4001080c) |=0x80; 
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); // Added by Najoua 27/08/2008
    
    
  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send PCF8574 address for read */
  I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
	/* Test on EV7 and clear it */
	if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))  
	{      
		/* Read a byte from the PCF8574 */
		ReadBuffer = I2C_ReceiveData(I2C1);      
	}

	/* Disable Acknowledgement */
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	
	/* Send STOP Condition */
	I2C_GenerateSTOP(I2C1, ENABLE);   

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C1, ENABLE);
	
	return ReadBuffer;
}


/*
 * 函数名：I2C_PCF8574_WaitPCF8574StandbyState
 * 描述  ：Wait for PCF8574 Standby state 
 * 输入  ：无
 * 输出  ：无
 * 返回  ：无
 * 调用  ： 
 */
void I2C_PCF8574_WaitPCF8574StandbyState(uint8_t PCF8574_ADDRESS)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(I2C1, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(I2C1, I2C_Register_SR1);
    /* Send PCF8574 address for write */
    I2C_Send7bitAddress(I2C1, PCF8574_ADDRESS, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(I2C1, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(I2C1, I2C_FLAG_AF);
    /* STOP condition */    
  I2C_GenerateSTOP(I2C1, ENABLE); // Added by Najoua 27/08/2008
}

/******************** (C) COPYRIGHT 2011 迷你嵌入式开发工作室 ********************/
