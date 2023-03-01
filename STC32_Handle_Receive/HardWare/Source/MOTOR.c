#include "MOTOR.h"

void MOTOR_GPIO_Config()
{
	P2M1 &= ~0xCf;
    P2M0 &= ~0xCf;		//P20 P21 P22 P23Ϊ׼˫���
	
	P1M1 &= ~0x80;
    P1M0 &= ~0x80;		//P20 P21 P22 P23Ϊ׼˫���
}

void MOTOR_Init()
{
    MOTOR_GPIO_Config();
	PWMB_Config();
}

/****
    *@brief		ǰ��
    *@param		��
    *@retval	��
*****/
void MOTOR_ForWard()
{
	Left_moto_go;
	Right_moto_go ;
	PWMB_SetCompare1(65);
	PWMB_SetCompare2(20);
}

/****
    *@brief		����
    *@param		��
    *@retval	��
*****/
void MOTOR_BackWard()
{
	Left_moto_back;
	Right_moto_back;
}

/****
    *@brief		��ת
    *@param		��
    *@retval	��
*****/
void MOTOR_TurnLeft()
{
	Left_moto_back;
	Right_moto_go;
}

/****
    *@brief		��ת
    *@param		��
    *@retval	��
*****/
void MOTOR_Turnright()
{
	Right_moto_back;
	Left_moto_go;
}

/****
    *@brief		ֹͣ
    *@param		��
    *@retval	��
*****/
void MOTOR_Stop()
{
	Right_moto_Stop;
	Left_moto_Stop;
}

