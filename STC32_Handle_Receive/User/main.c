#include <STC32G.H>
#include "ULTRASONIC.h"
#include "HC595.h"
#include "oled.h"
#include "NRF24L01.h"
#include "KEY.h"
#include "USART.h"
#include "DHT11.h"
#include "MOTOR.h"

uint16_t DATA;

void main()
{
	WTST = 0;  //���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
    EAXFR = 1; //��չ�Ĵ���(XFR)����ʹ��
    CKCON = 0; //��߷���XRAM�ٶ�
	
	Usart_Init();
//	NRF24L01_Init();
//	MOTOR_Init();
	OLED_Init();
//	HC595_Init();
//	KEY_Init();
//	DHT11_GPIO_Config();
	Ultrasonic_Init();
	//EA = 1;
	OLED_ShowString(1,0,"HELLO!",16);
	//NRF24L01_Check_detection();
	while(1)
	{
		DATA = Ultrasonic_GetDistance();
		OLED_ShowNum(1,2,DATA,4,16);
		OLED_ShowNum(1,6,100,4,16);
		Delay_s(1);
	}
}

