#include "MODEDATA.h"

int main()
{
	//��ģ���ʼ��
	OLED_Init();
	LED_Init();
	KEY_Init();
	Usart_Init();
	ROCKER_Init();
	MPU6050_Init();
	NRF24L01_Init();
	
	NRF24L01_Check_detection();		//���NRF24L01�Ƿ���������
	while(1)
	{
 		KEY_SCAN();
		Mode_Option();
	}
}
