#include "KEY.h"

//uint8_t Key_KeyNum;
//uint16_t count=0;

//void Timer0_Init()		//1����@24.000MHz
//{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
//	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
//	TMOD |= 0x01;		//���ö�ʱ��ģʽ
//	TL0 = 0x66;		//���ö�ʱ��ʼֵ
//	TH0 = 0xFC;		//���ö�ʱ��ʼֵ
//	TF0 = 0;		//���TF0��־
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
//   *@brief	��ȡ����������
//   *@param	��
//   *@retval	���°����ļ��룬��Χ��0~8���ް�������ʱ����0
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


