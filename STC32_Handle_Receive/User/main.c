#include "NRFDATA.h"

uint8_t KEY_BUFF[20];

void main()
{
	WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度
	
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
	Uart_SendCMD(Specify_Volume,0,20);		//初始音量20
	
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

