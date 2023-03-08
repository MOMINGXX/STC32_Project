#include "ULTRASONIC.h"

bit Flag = 0;

/****
	* @brief	��������������    			  
	* @param   	��
	* @return   ��    	
	* Sample usage:ULTRASONIC_GPIO_Config();
	* @note 
    */
static void ULTRASONIC_GPIO_Config()
{
	P0M1 &= ~0x04;
	P0M0 &= ~0x04;			//P02 Ϊ׼˫���
	
	P3M1 &= ~0x08;
	P3M0 &= ~0x08;			//P33 Ϊ׼˫���
}

/****
	* @brief	��ʱ��1����     			  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMER1_Config()();
	* @note 
    */
static void TIMER1_Config()		//24.000MHz
{
	AUXR |= 0x40;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;			//���ö�ʱ��ģʽ
	TL1 = 0;				//���ö�ʱ��ʼֵ
	TH1 = 0;				//���ö�ʱ��ʼֵ
	TF1 = 0;				//���TF1��־
	TR1 = 1;				//��ʱ��1��ʼ��ʱ
}

/****
	* @brief	��������ʼ��      			  
	* @param   	��
	* @return   ��    	
	* Sample usage:Ultrasonic_Init();
	* @note 
    */
void Ultrasonic_Init()
{
	Trig = 0;
	Echo = 0;
	ULTRASONIC_GPIO_Config();
	TIMER1_Config();	
}

/****
	* @brief	����������     			  
	* @param   	��
	* @return   ��    	
	* Sample usage:Ultrasonic_Start();
	* @note 
    */
static void Ultrasonic_Start()
{
	unsigned long i;
	Trig = 0;
	_nop_();
	Trig = 1;
	i = 58UL;
	while (i) i--;		//��ʱ10us
	Trig = 0;
}

/****
	* @brief	�������������		  
	* @param   	��
	* @return   ��    	
	* Sample usage:Ultrasonic_GetDistance();
    */
float Ultrasonic_GetDistance()
{
	uint8_t i = 0;
	uint16_t Time = 0;
	float Distance = 0;
	float Sum = 0;
	while(i != 5)
	{
		Ultrasonic_Start();
		Echo = 1;
		while(!Echo);		//�ȴ��͵�ƽ����
		TR1 = 1;
		while(Echo);		//�ȴ��ߵ�ƽ����
		TR1 = 0;
		i ++;
		Time = TH1*256+TL1;
		TH1=0;
		TL1=0;
		Distance = (float)Time * 0.0008;		//�������  cm
		Sum += Distance;
	}
	Distance = Sum / 5.0;
	return Distance;
}


