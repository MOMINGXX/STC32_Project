#include "SERVO.h"

uint8_t Servo_PWM = 3;

/****
	* @brief	�����������	  
	* @param   	��
	* @return   �� 	
	* Sample usage:SERVO_GPIO_Config();
    */
void SERVO_GPIO_Config()
{
	P1M1 &= ~0x80;
	P1M1 |= 0x80;		//P17 �������
}

void Timer3_Init()		//500΢��@24.000MHz
{
	T4T3M |= 0x02;			//��ʱ��ʱ��1Tģʽ
	T3L = 0x20;				//���ö�ʱ��ʼֵ
	T3H = 0xD1;				//���ö�ʱ��ʼֵ
	T4T3M |= 0x08;			//��ʱ��3��ʼ��ʱ
	ET3 = 1;
}

/****
	* @brief	�����ʼ�� 
	* @param   	��
	* @return   �� 	
	* Sample usage:SERVO_Init();
    */
void SERVO_Init()
{
	SERVO_GPIO_Config();
	//PWMA_Config();
	Timer3_Init();
}

/****
	* @brief	������ýǶ�
	* @param   	Angle	���ýǶ�
		@arg	0
		@arg	45
		@arg	90
		@arg	135
		@arg	180
	* @return   �� 	
	* Sample usage:SERVO_Init();
    */
void SERVO_SetAngle(uint8_t Angle)
{
	PWMA_SetCompare4(Angle / 180 * 2000 + 500);
}

void Time3_Routine() interrupt 19
{
	static uint8_t Count;
	Count++;
	Count %= 40;
	if(Servo_PWM > Count)
	{
		Servo=1;
	}
	else 
	{
		Servo=0;
	}
}