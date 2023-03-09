#include "NRFDATA.h"

uint8_t i,tbuff[4];

void main()
{
	WTST = 0;  //���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
    EAXFR = 1; //��չ�Ĵ���(XFR)����ʹ��
    CKCON = 0; //��߷���XRAM�ٶ�
	
	Usartx_Init();
	NRF24L01_Init();
	MOTOR_Init();
	HC595_Init();
	KEY_Init();
	DHT11_GPIO_Config();
	Ultrasonic_Init();
	SERVO_Init();
	WS2812_GPIO_Config();
	
	HC595_SendData(0x00);
	Uart_SendCMD(Specify_Volume,0,20);		//��ʼ����20
	
	EA = 1;
	
	NRF24L01_Check_detection();
	while(1)
	{
		Mode_Option();
	}
}

