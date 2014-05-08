#include "PCF8574_I2C.h"
/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 *          |  PB6-I2C1_SCL		|
 *          |  PB7-I2C1_SDA   |
**********************************************************************************/

#define I2C_Speed              50000
/*
 * ��������I2C_GPIO_Config
 * ����  ��I2C1 I/O����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* ʹ���� I2C1 �йص�ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);  
    
  /* PB6-I2C1_SCL��PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 * ��������I2C_Configuration
 * ����  ��I2C ����ģʽ����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void I2C_Mode_Config(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  I2C_DeInit(I2C1);
	/* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;//��STM32��Ϊ�ӻ�ʱ���I2C��ַ������ΪSTM32Ϊ��������������Ϊ0
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* ʹ�� I2C1 */
  I2C_Cmd(I2C1, ENABLE);

  /* I2C1 ��ʼ�� */
  I2C_Init(I2C1, &I2C_InitStructure);

	/*����1�ֽ�1Ӧ��ģʽ*/
	I2C_AcknowledgeConfig(I2C1, ENABLE);    
}

/*
 * ��������I2C_PCF8574_Init
 * ����  ��I2C ����(PCF8574)��ʼ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void I2C_PCF8574_Init(void)
{
  I2C_GPIO_Config(); 
  I2C_Mode_Config();
}


/*
 * ��������I2C_PCF8574_ByteWrite
 * ����  ��дһ���ֽڵ�I2C PCF8574��
 * ����  ��-pBuffer ������ָ��
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
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
 * ��������I2C_PCF8574_BufferRead
 * ����  ����PCF8574�����ȡһ�����ݡ� 
 * ����  ��-pBuffer ��Ŵ�PCF8574��ȡ�����ݵĻ�����ָ�롣
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
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
 * ��������I2C_PCF8574_WaitPCF8574StandbyState
 * ����  ��Wait for PCF8574 Standby state 
 * ����  ����
 * ���  ����
 * ����  ����
 * ����  �� 
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

/******************** (C) COPYRIGHT 2011 ����Ƕ��ʽ���������� ********************/