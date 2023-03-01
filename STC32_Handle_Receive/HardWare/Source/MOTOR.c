#include "MOTOR.h"

void MOTOR_GPIO_Config()
{
	P2M1 &= ~0xCf;
    P2M0 &= ~0xCf;		//P20 P21 P22 P23为准双向口
	
	P1M1 &= ~0x80;
    P1M0 &= ~0x80;		//P20 P21 P22 P23为准双向口
}

void MOTOR_Init()
{
    MOTOR_GPIO_Config();
	PWMB_Config();
}

/****
    *@brief		前进
    *@param		无
    *@retval	无
*****/
void MOTOR_ForWard()
{
	Left_moto_go;
	Right_moto_go ;
	PWMB_SetCompare1(65);
	PWMB_SetCompare2(20);
}

/****
    *@brief		回退
    *@param		无
    *@retval	无
*****/
void MOTOR_BackWard()
{
	Left_moto_back;
	Right_moto_back;
}

/****
    *@brief		左转
    *@param		无
    *@retval	无
*****/
void MOTOR_TurnLeft()
{
	Left_moto_back;
	Right_moto_go;
}

/****
    *@brief		右转
    *@param		无
    *@retval	无
*****/
void MOTOR_Turnright()
{
	Right_moto_back;
	Left_moto_go;
}

/****
    *@brief		停止
    *@param		无
    *@retval	无
*****/
void MOTOR_Stop()
{
	Right_moto_Stop;
	Left_moto_Stop;
}

