#ifndef __DELAY_H__
#define __DELAY_H__

#include "STC32G.h"

#define SYS_CLK 24000000L
#ifndef SYS_CLK 
#define SYS_CLK 11059200L
#endif

void Delay_us(uint16_t xus);
void Delay_ms(uint16_t xms);
void Delay_s(uint16_t xs);

//�ӳ�1΢��
void Delay1us();
//�ӳ�5΢��
void Delay5us();
//�ӳ�10΢��
void Delay10us();
//�ӳ�15΢��
void Delay15us();
//�ӳ�20΢��
void Delay20us();
//�ӳ�50΢��
void Delay50us();	
//�ӳ�100΢��
void Delay100us();	
//�ӳ�1����
void Delay1ms();			

#endif   /* __DELAY_H__*/