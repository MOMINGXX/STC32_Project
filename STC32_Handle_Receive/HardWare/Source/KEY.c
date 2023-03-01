#include "KEY.h"

//uint8_t Key_KeyNum;
//uint16_t count=0;

//void Timer0_Init()		//1毫秒@24.000MHz
//{
//	AUXR &= 0x7F;		//定时器时钟12T模式
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0x66;		//设置定时初始值
//	TH0 = 0xFC;		//设置定时初始值
//	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
//	EA=1;
//	ET0=1;
//}

//unsigned char key()
//{
//	uint8_t Temp;
//	Temp=Key_KeyNum;
//	Key_KeyNum=0;
//	return Temp;
//}

///**
//   *@brief	获取独立按键码
//   *@param	无
//   *@retval	按下按键的键码，范围：0~8，无按键按下时返回0
//   **/
//unsigned char key_GetState()
//{
//	unsigned char keynumber=0;
//	
//	if(Key1 == 0){keynumber=1;}
//	if(Key2 == 0){keynumber=2;}
//	if(Key3 == 0){keynumber=3;}
//	if(Key4 == 0){keynumber=4;}
//	if(Key5 == 0){keynumber=5;}
//	if(Key6 == 0){keynumber=6;}
//	if(Key7 == 0){keynumber=7;}
//	if(Key8 == 0){keynumber=8;}
//	
//	return keynumber;
//}	

//void Key_Loop()
//{
//	static uint8_t NowState,LastState;
//	LastState=NowState;
//	NowState=key_GetState();
//	if(LastState==1 && NowState==0)
//	{
//		Key_KeyNum=1;
//	}
//	if(LastState==2 && NowState==0)
//	{
//		Key_KeyNum=2;
//	}
//	if(LastState==3 && NowState==0)
//	{
//		Key_KeyNum=3;
//	}
//	if(LastState==4 && NowState==0)
//	{
//		Key_KeyNum=4;
//	}
//	if(LastState==5 && NowState==0)
//	{
//		Key_KeyNum=5;
//	}
//	if(LastState==6 && NowState==0)
//	{
//		Key_KeyNum=6;
//	}
//	if(LastState==7 && NowState==0)
//	{
//		Key_KeyNum=7;
//	}
//	if(LastState==8 && NowState==0)
//	{
//		Key_KeyNum=8;
//	}
//}


