#include "SERVO.h"

/****
	* @brief	舵机引脚配置	  
	* @param   	无
	* @return   无 	
	* Sample usage:SERVO_GPIO_Config();
    */
void SERVO_GPIO_Config()
{
	P1M1 &= ~0x80;
	P1M1 |= 0x80;		//P17 推挽输出
}

/****
	* @brief	舵机初始化 
	* @param   	无
	* @return   无 	
	* Sample usage:SERVO_Init();
    */
void SERVO_Init()
{
	SERVO_GPIO_Config();
	PWMA_Config();
}

/****
	* @brief	舵机设置角度
	* @param   	Angle	设置角度
		@arg	0
		@arg	45
		@arg	90
		@arg	135
		@arg	180
	* @return   无 	
	* Sample usage:SERVO_Init();
    */
void SERVO_SetAngle(uint8_t Angle)
{
	PWMA_SetCompare4(Angle / 180 * 2000 + 500);
}