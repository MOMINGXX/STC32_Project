#include "TIME.h"

void TIMEx_Init()
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xEA;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;            	//开启定时器中断
}

//void Timer1_Routine() interrupt 1
//{
//    
//}