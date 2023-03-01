#ifndef __USART_H__
#define __USART_H__

#include "STC32G.h"
#include <stdio.h>
#include <stdarg.h>

#define sys_clk         24000000UL
#define BAUD            9600
#define BRT             (65536 - (sys_clk / BAUD / 4))

sbit USART_TX = P3^1;    
sbit USART_RX = P3^0; 

extern uint8_t RX1_DAT[10];
extern bit Flag1;
 
void Usart_Init();	
void Usart_SendByte(uint8_t Byte);
void Usart_sprintf(char *format, ...);
void Usart_SendString(uint8_t *String);
void Usart_SendBuff(uint8_t *Buff,uint16_t Len);
void Usart_SendNumber(uint32_t Number,uint8_t Length);

#endif   /* __USART_H__*/