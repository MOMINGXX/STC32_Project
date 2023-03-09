#include "DHT11.h"

/****
	* @brief	DHT11��������	  
	* @param   	��
	* @return   �� 	
	* Sample usage:DHT11_GPIO_Config();
    */
void DHT11_GPIO_Config()
{
	P3M1 &= ~0x10;
	P3M1 &= ~0x10;		//P34 Ϊ׼˫���
}

/****
	* @brief	DHT11 ����     			  
	* @param   	��
	* @return   �� 	
	* Sample usage: DHT11_Reset();
    */
static void DHT11_Reset()
{
	unsigned long i;
    DHT11_DATA = 1;
    i = 178UL;
	while (i) i--;		//��ʱ30us
    DHT11_DATA = 0;
    i = 119998UL;
	while (i) i--;		//��ʱ20ms
    DHT11_DATA = 1;
    i = 178UL;
	while (i) i--;		//��ʱ30us
}

/****
	* @brief	DHT11 ��ȡ����״̬    			  
	* @param   	��
	* @return   0 / 1  	
	* Sample usage:DHT11_Init();
    */
static uint8_t DHT11_Read_Bit()
{
	unsigned long i;
    while(DHT11_DATA);           	//�ȴ��͵�ƽ ��ʼ��������
    while(!DHT11_DATA);          	//�ȴ��ߵ�ƽ
    i = 358UL;
	while (i) i--;					//��ʱ60us
    if(DHT11_DATA)
    {
        return 1;
    }
    return 0;
} 

/****
	* @brief	DHT11 ��ȡ����   			  
	* @param   	��
	* @return   Byte    ��ȡ������  	
	* Sample usage:DHT11_Read_Byte();
    */
static uint8_t DHT11_Read_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
    for(i = 0; i < 8; i++)
    {
        Byte <<= 1;
        Byte |= DHT11_Read_Bit();
    }
	return Byte;
}

/****
	* @brief	DHT11 ��ȡ��ʪ������   			  
	* @param   	Data    �洢��ȡ����ʪ������     	
	* Sample usage:DHT11_Read_Data(&TempH,&TempL,&HumiH,&HumiL);
    */
void DHT11_Read_Data(DHT11_Data *DATA)
{
	uint8_t i;
    uint8_t Buff[5];
	DHT11_Reset();
	if(DHT11_DATA == 0)
	{
		while(DHT11_DATA == 0);    //�ȴ����� 
		for(i=0;i<5;i++)
		{
			Buff[i] = DHT11_Read_Byte();
		}
		if(Buff[4] == Buff[0] + Buff[1] + Buff[2] + Buff[3])
		{
			DATA->HumiH = Buff[0];
			DATA->HumiL = Buff[1];
			DATA->TempH = Buff[2];
			DATA->TempL = Buff[3];
		}
	}
}



