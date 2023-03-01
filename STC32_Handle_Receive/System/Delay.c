#include "Delay.h"

#if (SYS_CLK == 24000000)

/****
	* @brief	�ӳ�1΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay1us(); �ӳ�1us
	*/
void Delay1us()		
{
    uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 4UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�5΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay5us(); �ӳ�5us
	*/
void Delay5us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 28UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�10΢��
	* @param	��	
	* @return	��        	
	* Sample usage:  Delay10us(); �ӳ�10us
	*/
void Delay10us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 58UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�15΢��
	* @param	��	
	* @return	��        	
	* Sample usage:  Delay15us(); �ӳ�15us
	*/
void Delay15us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 88UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�20΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay20us(); �ӳ�20us
	*/
void Delay20us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 118UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�50΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay50us(); �ӳ�50us
	*/
void Delay50us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 298UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�100΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay100us();
	*/
void Delay100us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 598UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�1����
	* @param	��	
	* @return	��        	
	* Sample usage:  Delay1ms(); �ӳ�1ms
	*/
void Delay1ms()
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 5998UL;
	while (i) i--;
}

#elif (SYS_CLK == 12000000)		//12MHz

/****
	* @brief	�ӳ�1΢��
	* @param	��	
	* @return 	��        	
	* Sample usage:Delay1us(); �ӳ�1us
	*/
void Delay1us()		//@12.000
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 1UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�5΢��
	* @param	��	
	* @return 	��        	
	* Sample usage:Delay5us(); �ӳ�5us
	*/
void Delay5us()		//@12.000
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 13UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�10΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay10us(); �ӳ�10us
	*/
void Delay10us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 28UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�20΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay20us(); �ӳ�20us
	*/
void Delay20us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 58UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�15΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay15us(); �ӳ�15us
	*/
void Delay15us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 43UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�50΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay100us(); �ӳ�50us
	*/
void Delay50us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 148UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�100΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay100us(); �ӳ�100us
	*/
void Delay100us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 298UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�1����
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay1ms(); �ӳ�1ms
	*/
void Delay1ms()	
{
	uint32_t i;
	_nop_();
	_nop_();
	_nop_();
	i = 2998UL;
	while (i) i--;
}

#else //11059200MHz

/****
	* @brief	�ӳ�1΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay1us(); �ӳ�1us
	*/
void Delay1us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 1UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�5΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay5us(); �ӳ�5us
	*/
void Delay5us()	
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 12UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�10΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay10us(); �ӳ�10us
	*/
void Delay10us()		
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 26UL;
	while (i) i--;
}

/****
	* @brief    �ӳ�15΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay15us(); �ӳ�15us
	*/
void Delay15us()		
{
	uint32_t i;
	_nop_();
	i = 40UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�20΢��
	* @param	��	
	* @return	��        	
	* Sample usage:Delay20us(); �ӳ�20us
	*/
void Delay20us()		
{
	uint32_t i;
	i = 54UL;
	while (i) i--;
}

/****
	* @brief    �ӳ�50΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay100us(); �ӳ�50us
	*/
void Delay50us()	
{
	uint32_t i;
	i = 137UL;
	while (i) i--;
}

/****
	* @brief    �ӳ�100΢��
	* @param	��	
	* @return   ��        	
	* Sample usage:Delay100us(); �ӳ�100us
	*/
void Delay100us()		
{
	uint32_t i;
	_nop_();
	i = 275UL;
	while (i) i--;
}

/****
	* @brief	�ӳ�1����
	* @param	��	
	* @return	��        	
	* Sample usage:  Delay1ms(); �ӳ�1ms
	*/
void Delay1ms()
{
	uint32_t i;
	_nop_();
	_nop_();
	i = 2763UL;
	while (i) i--;
}

#endif


/****
	* @brief	΢�뼶��ʱ
	* @param	xus	��ʱʱ��		
	* @return	��        	
	* Sample usage:Delay_us(1); 
	*/
void Delay_us(uint16_t xus)
{
	while(xus--)
	{
		Delay1us();
	}
}

/****
	* @brief	�ӳ�time����
	* @param	xms	�ӳ�ʱ��(1-65535)	
	* @return	��        	
	* Sample usage:Delay(1000); �ӳ�1s
	*/
void Delay_ms(uint16_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}

/****
	* @brief	�뼶��ʱ
	* @param	xs	��ʱʱ��		
	* @return	��        	
	* Sample usage:Delay_s(1); 
	*/
void Delay_s(uint16_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
}