#include "KEY.h"

uint8_t Key_KeyNum;

/****
	* @brief	������������	  
	* @param   	��
	* @return   �� 	
	* Sample usage:KEY_GPIO_Config();
    */
static void KEY_GPIO_Config()
{
	P0M0 &= ~0x70; 
	P0M1 &= ~0x70; 		//P04 P05 P06 Ϊ׼˫���
}

/****
	* @brief	��ʱ��0����	 20ms / 24Mhz
	* @param   	��
	* @return   �� 	
	* Sample usage:TIME0_Config();
    */
static void TIME0_Config()		
{
	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0xC0;				//���ö�ʱ��ʼֵ
	TH0 = 0x63;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;            	//������ʱ���ж�
}

/****
	* @brief	������ʼ��
	* @param   	��
	* @return   �� 	
	* Sample usage:KEY_Init();
    */
void KEY_Init()
{
	KEY_GPIO_Config();
	BEEP_GPIO_Config();
	TIME0_Config();
}

/****
	* @brief	���ذ���ֵ
	* @param   	��
	* @return   Temp 	����ֵ	
	* Sample usage:key();
    */
uint8_t key()
{
	uint8_t Temp;
	Temp=Key_KeyNum;
	Key_KeyNum=0;
	return Temp;
}

/****
    * @brief	��ȡ����������
    * @param	��
    * @retval	���°����ļ��룬��Χ��0~8���ް�������ʱ����0
	* Sample usage:key_GetState();
    */
static uint8_t  key_GetState()
{
	uint8_t  keynumber=0;
	
	if(KEY1 == 0){keynumber=1;}
	if(KEY2 == 0){keynumber=2;}
	if(KEY3 == 0){keynumber=3;}
	
	return keynumber;
}	

/****
    * @brief	���ڶ�ʱ��ÿ20ms����Ƿ��а�������
    * @param	��
    * @retval	��
	* Sample usage:Key_Loop();
    */
static void Key_Loop()
{
	static uint8_t NowState,LastState;
	LastState=NowState;
	NowState=key_GetState();
	if(LastState==1 && NowState==0)
	{
		Key_KeyNum=1;
	}
	if(LastState==2 && NowState==0)
	{
		Key_KeyNum=2;
	}
	if(LastState==3 && NowState==0)
	{
		Key_KeyNum=3;
	}
}

/****
    * @brief	��ʱ���жϺ��� ÿ20ms����Ƿ��а�������
    * @param	��
    * @retval	��
    */
void Time0_Routine() interrupt 1
{
	Key_Loop();
}
