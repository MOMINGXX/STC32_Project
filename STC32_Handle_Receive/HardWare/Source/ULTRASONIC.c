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
	P0M1 &= ~0x0C;
	P0M0 &= ~0x0C;			//P02 P03 Ϊ׼˫���
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
uint16_t Ultrasonic_GetDistance()
{
	uint16_t Time = 0;
	uint16_t Distance = 0;
	Ultrasonic_Start();
	Echo = 1;
	while(!Echo);		//�ȴ��͵�ƽ����
	TR1 = 1;
	while(Echo);		//�ȴ��ߵ�ƽ����
	TR1 = 0;
	
	Time = TH1*256+TL1;
	TH1=0;
	TL1=0;
	
	Distance = Time *1.7/100;		//�������  mm
	return Distance;
}

