#include "HC595.h"

/****
	* @brief	HC595��������	  
	* @param   	��
	* @return   �� 	
	* Sample usage:HC595_GPIO_Config();
    */
static void HC595_GPIO_Config()
{
	P4M1 &= ~0xE0;
    P4M0 &= ~0xE0;      //P45 P46 P47�������
}

/****
	* @brief	HC595��ʼ�� 
	* @param   	��
	* @return   �� 	
	* Sample usage:HC595_Init();
    */
void HC595_Init()
{
    HC595_GPIO_Config();
}

/****
	* @brief	HC595��������
	* @param   	Data	���͵�����
	* @return   �� 	
	* Sample usage:HC595_SendData(0x00);
    */
void HC595_SendData(uint8_t Data)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if( RESET != (Data << i) & 0x80) 
        {
			HC595_SER = 1;
        }
        else
        {
            HC595_SER = 0;
        }
        HC595_PCLK = 0;
        HC595_PCLK = 1;
    }
    HC595_SRCLR = 0;
    HC595_SRCLR = 1;
}
