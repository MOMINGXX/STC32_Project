#include "BEEP.h"

/****
	* @brief	BEEP ��������	  
	* @param   	��
	* @return   �� 	
	* Sample usage:BEEP_GPIO_Config()();
    */
void BEEP_GPIO_Config()
{
	P3M1 &= ~0x20;
	P3M0 &= ~0x20;
}