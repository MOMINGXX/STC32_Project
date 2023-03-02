#include "SERVO.h"

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

/****
	* @brief	�����ʼ�� 
	* @param   	��
	* @return   �� 	
	* Sample usage:SERVO_Init();
    */
void SERVO_Init()
{
	SERVO_GPIO_Config();
	PWMA_Config();
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