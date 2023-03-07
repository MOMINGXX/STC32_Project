#include "NRFDATA.h"

uint8_t KEY_BUFF[20];

void main()
{
	WTST = 0;  //���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
    EAXFR = 1; //��չ�Ĵ���(XFR)����ʹ��
    CKCON = 0; //��߷���XRAM�ٶ�
	
	Usartx_Init();
	NRF24L01_Init();
	MOTOR_Init();
	OLED_Init();
	HC595_Init();
	KEY_Init();
	DHT11_GPIO_Config();
	Ultrasonic_Init();
	EA = 1;
	OLED_ShowString(1,0,"HELLO!",16);
	NRF24L01_Check_detection();
	
	while(1)
	{
//		Bluetooth_Mode();
//		Wireless_Mode();
		Mode_Option();
	}
}

