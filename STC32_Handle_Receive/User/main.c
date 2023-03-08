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
	SERVO_Init();
	
	EA = 1;
	OLED_ShowString(1,0,"HELLO!",16);
	NRF24L01_Check_detection();
	HC595_SendData(0x00);
	Servo_PWM = 3;
	Uart_SendCMD(Specify_Volume,0,20);		//��ʼ����20
	
	while(1)
	{
//		printf("%f\n",Ultrasonic_GetDistance());
//		Delay_s(1);
		Avoid_Mode();
//		Key_Play_Mode();
//		Rocker_Key_Mode();
//		Bluetooth_Mode();
//		Wireless_Mode();
//		Mode_Option();
	}
}

