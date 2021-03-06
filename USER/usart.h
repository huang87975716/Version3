#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>

void USART2_Config(void);
int fputc(int ch, FILE *f);
void USART2_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void EchoToMaster(unsigned char *ptr);

#endif /* __USART_H */
