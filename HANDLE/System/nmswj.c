#include "nmswj.h"

//向上位机发送欧拉角
//详情参考匿名通讯协议
void SEND_OULA_ANGLE(short row,short pit,short yaw)
{
	u8 i;
	u8 sumcheck = 0;
	u8 addcheck = 0;
	u8 buf[13]={0};
	
	buf[0]=0xAA;
	buf[1]=0xFF;
	buf[2]=0x03;
	buf[3]=0x07;
	
	buf[4]=(u8)row;
	buf[5]=(u8)(row>>8);
	
	buf[6]=(u8)pit;
	buf[7]=(u8)(pit>>8);

	buf[8]=(u8)yaw;
	buf[9]=(u8)(yaw>>8);
	
	buf[10]=0x00;
	
	for(i=0; i < (buf[3]+4); i++)
	{
		sumcheck += buf[i]; //从帧头开始，对每一字节进行求和，直到DATA区结束
		addcheck += sumcheck; //每一字节的求和操作，进行一次sumcheck的累加
	}
	buf[11]=sumcheck;
	buf[12]=addcheck;
	
	Usart_SendBuff(USART1,buf,13);
	
}