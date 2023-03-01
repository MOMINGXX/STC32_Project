#include <STC32G.H>
#include "oled.h"
#include "NRF24L01.h"
#include "TIME.h"
#include "USART.h"
#include "MOTOR.h"


void main()
{
	WTST = 0;  //���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
    EAXFR = 1; //��չ�Ĵ���(XFR)����ʹ��
    CKCON = 0; //��߷���XRAM�ٶ�
	
	Usart_Init();
	NRF24L01_Init();
	MOTOR_Init();
	OLED_Init();
	//EA = 1;
	OLED_ColorTurn(0);
	OLED_DisplayTurn(0);
	OLED_ShowString(1,0,"HELLO!",16);
	//NRF24L01_Check_detection();

	PWMA_SetCompare4(150);
	while(1)
	{
		MOTOR_ForWard();
	}
}

