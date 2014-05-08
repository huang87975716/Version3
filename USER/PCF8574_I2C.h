#ifndef __PCF8574_H__
#define __PCF8574_H__
	#include "stm32f10x.h"
	void I2C_PCF8574_Init(void);
	void I2C_PCF8574_ByteWrite(uint8_t WriteBuffer, uint8_t PCF8574_ADDRESS);
	uint8_t I2C_PCF8574_ByteRead(uint8_t PCF8574_ADDRESS);
	void I2C_PCF8574_WaitPCF8574StandbyState(uint8_t PCF8574_ADDRESS);
#endif
