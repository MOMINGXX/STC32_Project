#include <STC32G.H>
#include "oled.h"
#include "NRF24L01.h"
#include "TIME.h"
#include "USART.h"
#include "MOTOR.h"


void main()
{
	WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度
	
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

