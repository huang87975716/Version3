#include "matrix_motor.h"
#include "stm32f10x.h"

void SetRankValue(unsigned char LowPortValue, unsigned char HighPortValue)
{
	if( (LowPortValue&0x01) != 0x01) GPIO_SetBits(GPIOA,GPIO_Pin_0);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	
	if( (LowPortValue&0x02) != 0x02) GPIO_SetBits(GPIOA,GPIO_Pin_4);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
	if( (LowPortValue&0x04) != 0x04) GPIO_SetBits(GPIOA,GPIO_Pin_5);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	
	if( (LowPortValue&0x08) != 0x08) GPIO_SetBits(GPIOA,GPIO_Pin_6);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	
	if( (LowPortValue&0x10) != 0x10) GPIO_SetBits(GPIOA,GPIO_Pin_7);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	
	if( (LowPortValue&0x20) != 0x20) GPIO_SetBits(GPIOC,GPIO_Pin_4);
	else GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	
	if( (LowPortValue&0x40) != 0x40) GPIO_SetBits(GPIOC,GPIO_Pin_5);
	else GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	
	if( (LowPortValue&0x80) != 0x80) GPIO_SetBits(GPIOB,GPIO_Pin_0);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	
	if( (HighPortValue&0x01) != 0x01) GPIO_SetBits(GPIOB,GPIO_Pin_1);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	
	if( (HighPortValue&0x02) != 0x02) GPIO_SetBits(GPIOB,GPIO_Pin_10);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	
	if( (HighPortValue&0x04) != 0x04) GPIO_SetBits(GPIOB,GPIO_Pin_11);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_11);
}

void SetLineValue(unsigned char LowPortValue, unsigned char HighPortValue)
{
	if( (LowPortValue&0x01) != 0x01) GPIO_SetBits(GPIOA,GPIO_Pin_10);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_10);
	
	if( (LowPortValue&0x02) != 0x02) GPIO_SetBits(GPIOA,GPIO_Pin_9);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_9);
	
	if( (LowPortValue&0x04) != 0x04) GPIO_SetBits(GPIOA,GPIO_Pin_8);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	
	if( (LowPortValue&0x08) != 0x08) GPIO_SetBits(GPIOC,GPIO_Pin_9);
	else GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	
	if( (LowPortValue&0x10) != 0x10) GPIO_SetBits(GPIOC,GPIO_Pin_8);
	else GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	
	if( (LowPortValue&0x20) != 0x20) GPIO_SetBits(GPIOC,GPIO_Pin_7);
	else GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	
	if( (LowPortValue&0x40) != 0x40) GPIO_SetBits(GPIOC,GPIO_Pin_6);
	else GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	
	if( (LowPortValue&0x80) != 0x80) GPIO_SetBits(GPIOB,GPIO_Pin_15);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
	if( (HighPortValue&0x01) != 0x01) GPIO_SetBits(GPIOB,GPIO_Pin_14);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	
	if( (HighPortValue&0x02) != 0x02) GPIO_SetBits(GPIOB,GPIO_Pin_13);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
	if( (HighPortValue&0x04) != 0x04) GPIO_SetBits(GPIOB,GPIO_Pin_12);
	else GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
