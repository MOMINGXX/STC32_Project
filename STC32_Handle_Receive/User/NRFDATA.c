#include "NRFDATA.h"

uint8_t ROCKER_RxBuf[10] = " 0 ";	//ҡ�˽������ݻ�����
uint8_t MPU6050_RxBuf[20];			//�����ǽ������ݻ�����
uint8_t KEY_RxBuf[16];				//�����������ݻ�����
uint8_t Mode_TxBuf[4];				//ģʽ���ջ�����
uint8_t MODE_STOP[6];				//ģʽ���ջ�����

//��ģʽ��־λ
uint8_t MP_FLAG = 0;	
uint8_t ROC_FLAG = 0;
uint8_t PLAY_FLAG = 0;
uint8_t KEY_FLAG = 0;
uint8_t WL_FLAG = 0;
uint8_t AVP_FLAG = 0;

/****
	* @brief	����ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:Bluetooth_Mode();
    */
void Bluetooth_Mode()
{
	static Mode_Flag = 1;
	if(Flag3)
	{
		if(0x15 == RX2_BUFF[13])
		{
			Mode_Flag = 0;
		}
		if(0x10 == RX2_BUFF[14])
		{
			Mode_Flag = 1;
		}
		if(0x0F == RX2_BUFF[15])
		{
			Mode_Flag = 2;
		}
		Usartx_SendBuff(USART1,RX2_BUFF,19);
		Flag3 = 0;
	}
	switch(Mode_Flag)
	{
		case 0:
			APP_ROCKER_Mode();
			break;
		case 1:
			APP_KEY_Mode();
			break;
		case 2:
			APP_MP3Play_Mode();
			break;
	}
}

/****
	* @brief	ҡ��ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:Wireless_Mode();
    */
void Wireless_Mode()
{
	uint8_t PWM1,PWM2;			//PWM1 ��  PWM2 ��
	NRF24L01_RX_Mode();		//����ģʽ
	Delay_ms(6);
	/*�жϽ��ճɹ���� */
	if(NRF24L01_RxPacket(ROCKER_RxBuf) == RESET)	
	{	
		PWM1 = PWM2 = (100 - ROCKER_RxBuf[2]);					//��ҡ��ֵ
		PWMB_SetCompare5(PWM1);
		PWMB_SetCompare6(PWM2);
		if(ROCKER_RxBuf[7] < 100 && ROCKER_RxBuf[7] >= 55)		//��ҡ������
		{
			MOTOR_BackWard();
		}
		else if(ROCKER_RxBuf[7] <= 45 && ROCKER_RxBuf[7] >= 0)	//��ҡ������
		{
			MOTOR_ForWard();
		}
		else if(ROCKER_RxBuf[9] < 100 && ROCKER_RxBuf[9] >= 55)	//��ҡ������
		{
			MOTOR_TurnLeft();
		}
		else if(ROCKER_RxBuf[9] <= 45 && ROCKER_RxBuf[9] >= 0)	//��ҡ������
		{
			MOTOR_Turnright();
		}
		else if(ROCKER_RxBuf[9] < 55 && ROCKER_RxBuf[9] > 45)	//��ҡ������/�����м�
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		} 
		/*�ֱ��˳���ģʽ���� "STOP" */
		else if('S' == ROCKER_RxBuf[0] && 'T' == ROCKER_RxBuf[1] && 'O' == ROCKER_RxBuf[2] && 'P' == ROCKER_RxBuf[3])
		{
			ROC_FLAG = 1;
		}
		printf("PWM:%d\n",PWM1); 
	}
//	else printf("ROCKER Receive failed !\n"); 
}

/****
	* @brief	�ֱ��������Ʋ���ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:Key_Play_Mode();
    */
void Key_Play_Mode()
{
	static uint8_t Volume;
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(KEY_RxBuf) == RESET)
	{
		if(5 == KEY_RxBuf[6])
		{
			Uart_SendCMD(Play,0,0);
		}
		else if(8 == KEY_RxBuf[9])
		{
			Uart_SendCMD(Suspended,0,0);
		}
		else if(6 == KEY_RxBuf[7])
		{
			Uart_SendCMD(Last_Song,0,0);
		}
		else if(7 == KEY_RxBuf[8])
		{
			Uart_SendCMD(Next_Song,0,0);
		}
		else if(9 == KEY_RxBuf[10])
		{
			Uart_SendCMD(Random_Broadcast,0,0);
		}
		else if(10 == KEY_RxBuf[11])
		{
			/*������*/
			Volume ++;
			if(Volume >= 30)
			{
				Volume = 30;
			}
			Uart_SendCMD(Add_Volume,0,Volume);
		}
		else if(11 == KEY_RxBuf[12])
		{
			/*������ */
			Volume --;
			if(Volume >= 30)
			{
				Volume = 0;
			}
			Uart_SendCMD(Reduce_Volume,0,Volume);
		}
		/*�ֱ��˳���ģʽ���� "STOP" */
		else if('S' == KEY_RxBuf[0] && 'T' == KEY_RxBuf[1] && 'O' == KEY_RxBuf[2] && 'P' == KEY_RxBuf[3])
		{
			PLAY_FLAG = 1;
		}
		printf("Key:%d\n",KEY_RxBuf[5]); 
	}
}

/****
	* @brief	������ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:Gravity_Mode();
	* note		����ֵƯ������ ��ģʽ����
    */
void Gravity_Mode()
{
	static uint8_t PWM = 35;
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(MPU6050_RxBuf) == RESET)
	{
		PWM = (100 - ROCKER_RxBuf[2]);
		PWMB_SetCompare5(PWM);
		PWMB_SetCompare6(PWM);
		if(MPU6050_RxBuf[3] <= 40)		
		{
			MOTOR_ForWard();
		}
		else if(MPU6050_RxBuf[3] >= 60)	
		{
			MOTOR_BackWard();
		}
		else if(MPU6050_RxBuf[3] > 40 && MPU6050_RxBuf[3] < 60)
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
		else if(MPU6050_RxBuf[5] <= 40)
		{
			MOTOR_TurnLeft();
		}
		else if(MPU6050_RxBuf[5] >= 60)
		{
			MOTOR_Turnright();
		}
		else if(MPU6050_RxBuf[5] > 40 && MPU6050_RxBuf[5] < 60)
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
		else if('S' == MPU6050_RxBuf[0] && 'T' == MPU6050_RxBuf[1] && 'O' == MPU6050_RxBuf[2] && 'P' == MPU6050_RxBuf[3])
		{
			MP_FLAG = 1;
		}
		printf("Roll:%d\n",MPU6050_RxBuf[5]); 
	}
}

/****
	* @brief	�ֱ���������ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:Rocker_Key_Mode();
    */
void Rocker_Key_Mode()
{
	static uint8_t PWM = 0;
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(KEY_RxBuf) == RESET)
	{
		if(5 == KEY_RxBuf[6])
		{
			MOTOR_ForWard();
		}
		else if(8 == KEY_RxBuf[9])
		{
			MOTOR_BackWard();
		}
		else if(6 == KEY_RxBuf[7])
		{
			MOTOR_TurnLeft();
		}
		else if(7 == KEY_RxBuf[8])
		{
			MOTOR_Turnright();
		}
		else if(10 == KEY_RxBuf[11])
		{
			PWM  ++;
			if(PWM >= 100)
			{
				PWM = 100;
			}
		}
		else if(11 == KEY_RxBuf[12])
		{
			PWM  --;
			if(PWM > 100)
			{
				PWM = 0;
			}
		}
		
		else if(9 == KEY_RxBuf[10])
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
		else if('S' == KEY_RxBuf[0] && 'T' == KEY_RxBuf[1] && 'O' == KEY_RxBuf[2] && 'P' == KEY_RxBuf[3])
		{
			KEY_FLAG = 1;
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
		PWMB_SetCompare5(PWM);
		PWMB_SetCompare6(PWM);
		printf("PWM:%d\n",PWM); 
	}
}

/****
	* @brief	����ģʽ
	* @param   	��
	* @return   ��    	
	* Sample usage:Avoid_Mode()();
	* @note 
    */
void Avoid_Mode()
{
	static float Distance_Middle = 0.0;		//�м����
	static float Distance_Left = 0.0;		//������
	static float Distance_Right = 0.0;		//�Ҳ����
	PWMB_SetCompare5(35);
	PWMB_SetCompare6(35);
	Servo_PWM = 3;			//������ת���м�
	Delay_ms(500);
	Distance_Middle = Ultrasonic_GetDistance();			//����Ҳ����
	Delay_ms(2);
	if(Distance_Middle <= 15)
	{
		MOTOR_Stop();			//ֹͣ
		
		Servo_PWM = 1;		//������ת���Ҳ�
		Delay_s(1);
		Distance_Right = Ultrasonic_GetDistance();		//����Ҳ����
		Delay_ms(2);
		
		Servo_PWM = 3;		//������ת�м�
		Delay_s(1);

		Servo_PWM = 5;		//������ת�����
		Delay_ms(1600);
		Distance_Left = Ultrasonic_GetDistance();		//���������
		Delay_ms(2);
	}
	if(Distance_Middle > 15)		//ǰ���������15cm  ǰ��
	{
		MOTOR_ForWard();
	}
	else if(Distance_Right >= Distance_Left && Distance_Right > 15)	
	{
		//���Ҿ����������� ���Ҵ���15cmʱ  ��תһ��ʱ��ͣ��
		MOTOR_Turnright();
		Delay_s(1);
		MOTOR_Stop();
	}
	else if(Distance_Right <= Distance_Left && Distance_Left > 15)		
	{
		//�����������Ҿ��� ���Ҵ���15cmʱ  ��תһ��ʱ��ͣ��
		MOTOR_TurnLeft();
		Delay_s(1);
		MOTOR_Stop();
	}
	else 
	{
		MOTOR_BackWard();
		Delay_s(1);
		MOTOR_Stop();
	}
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(ROCKER_RxBuf) == RESET)
	{	
		if('S' == ROCKER_RxBuf[0] && 'T' == ROCKER_RxBuf[1] && 'O' == ROCKER_RxBuf[2] && 'P' == ROCKER_RxBuf[3])
		{
			AVP_FLAG = 1;
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
	}
	printf("Distance:%d\n",Distance_Middle); 
}

/****
	* @brief	WS2812ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:Ws2812_Mode();
    */
void Ws2812_Mode()
{
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(Mode_TxBuf) == RESET)
	{
		if('A' == Mode_TxBuf[2])
		{
			RGB_RandomColor(14);
		}
		else if('E' == Mode_TxBuf[2])
		{
			RainbowCycle(100);
		}
		else if('T' == Mode_TxBuf[2])
		{
			TheaterChase(Color(0,121,255),100);
		}
		else if('W' == Mode_TxBuf[2])
		{
			WS2812_RGB_White(14);
		}
		else if('R' == Mode_TxBuf[2])
		{
			WS2812_RGB_Red(14);
		}
		else if('G' == Mode_TxBuf[2])
		{
			WS2812_RGB_Green(14);
		}
		else if('B' == Mode_TxBuf[2])
		{
			WS2812_RGB_Blue(14);
		}
		else if('C' == Mode_TxBuf[2])
		{
			TheaterChaseRainbow(100);
		}
		else if('S' == Mode_TxBuf[0] && 'T' == Mode_TxBuf[1] && 'O' == Mode_TxBuf[2] && 'P' == Mode_TxBuf[3])
		{
			WL_FLAG = 1;
		}
		else 
		{
			WS2812_RGB_Reset();
			WS2812_RGB_SetColor(0, 0, 0);
		}
		printf("Key:%c\n",Mode_TxBuf[2]); 
	}
}

/****
	* @brief	APPģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:APP_ROCKER_Mode();
    */
void APP_ROCKER_Mode()
{
//	uint8_t PWM1,PWM2;
//	PWM1 = PWM2 = RX2_BUFF[1];
//	if(RX2_BUFF[0] <= 45 && RX2_BUFF[0] >= 0)
//	{
//		PWM1 = RX2_BUFF[0] * 2;			//0 - 100
//	}
//	else if(RX2_BUFF[0] <= 100 && RX2_BUFF[0] > 55)
//	{
//		PWM2 = (RX2_BUFF[0] - 55) * 2;		// 0 - 98
//	}
//	if(RX2_BUFF[2] <= 100 && RX2_BUFF[2] >= 45)
//	{
//		MOTOR_ForWard();
//		PWMB_SetCompare5(PWM1);
//		PWMB_SetCompare6(PWM2);
//	}
//	else if(RX2_BUFF[2] >= 60 && RX2_BUFF[2] <= 100)
//	{
//		MOTOR_BackWard();
//		PWMB_SetCompare5(PWM1);
//		PWMB_SetCompare6(PWM2);
//	}
//	else MOTOR_Stop();
//	if(RX2_BUFF[3] <= 100 && RX2_BUFF[3] >= 45)
//	{
//		MOTOR_TurnLeft();
//		PWMB_SetCompare5(PWM1);
//		PWMB_SetCompare6(PWM2);
//	}
//	else if(RX2_BUFF[3] >= 0 && RX2_BUFF[3] <= 45)
//	{
//		MOTOR_Turnright();
//		PWMB_SetCompare5(PWM1);
//		PWMB_SetCompare6(PWM2);
//	}
//	else MOTOR_Stop();	
}

/****
	* @brief	APP����ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:APP_KEY_Mode();
    */
void APP_KEY_Mode()
{
	static uint8_t PWM = 35;
	if(Flag3)
	{
		if(0x16 == RX2_BUFF[1])
		{
			PWM  ++;
			if(PWM >= 100)
			{
				PWM = 100;
			}
		}
		if(0x18 == RX2_BUFF[2])
		{
			PWM  --;
			if(PWM > 100)
			{
				PWM = 0;
			}
		}
		PWMB_SetCompare5(PWM);
		PWMB_SetCompare6(PWM);
		if(0x0A == RX2_BUFF[3])
		{
			MOTOR_ForWard();
		}
		else if(0x0B == RX2_BUFF[4])
		{
			MOTOR_BackWard();
		}
		else if(0x0C == RX2_BUFF[5])
		{
			MOTOR_TurnLeft();
		}
		else if(0x0D == RX2_BUFF[6])
		{
			MOTOR_Turnright();
		}
		else if(0x0E == RX2_BUFF[7])
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
		Flag3 = 0;
	}
}

/****
	* @brief	APP�������Ʋ���ģʽ
	* @param   	��
	* @return   ��	
	* Sample usage:APP_MP3Play_Mode();
    */
void APP_MP3Play_Mode()
{
	static uint8_t Volume = 20;
	if(Flag3)
	{
		if(0x16 == RX2_BUFF[1])
		{
			Volume ++;
			if(Volume >= 30)
			{
				Volume = 30;
			}
			Uart_SendCMD(Add_Volume,0,Volume);
		}
		else if(0x18 == RX2_BUFF[2])
		{
			Volume --;
			if(Volume >= 30)
			{
				Volume = 0;
			}
			Uart_SendCMD(Reduce_Volume,0,Volume);
		}
		if(0x11 == RX2_BUFF[8])
		{
			Uart_SendCMD(Play,0,0);
		}
		else if(0x17 == RX2_BUFF[9])
		{
			Uart_SendCMD(Suspended,0,0);
		}
		else if(0x12 == RX2_BUFF[10])
		{
			Uart_SendCMD(Next_Song,0,0);
		}
		else if(0x13 == RX2_BUFF[11])
		{
			Uart_SendCMD(Last_Song,0,0);
		}
		else if(0x14 == RX2_BUFF[12])
		{
			Uart_SendCMD(Random_Broadcast,0,0);
		}
		Flag3 = 0;
	}
}

/****
	* @brief	ģʽѡ��
	* @param   	��
	* @return   ��	
	* Sample usage:Mode_Option();
    */
void Mode_Option()
{
	static uint8_t Mode = 1;
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(Mode_TxBuf) == RESET)
	{
		if('L' == Mode_TxBuf[0] && 'Y' == Mode_TxBuf[1])
		{
			Mode = 1;
		}
		else if('R' == Mode_TxBuf[0] && 'Y' == Mode_TxBuf[1])
		{
			Mode = 2;
		}
		else if('M' == Mode_TxBuf[0] && 'P' == Mode_TxBuf[1])
		{
			Mode = 3;
		}
		else if('G' == Mode_TxBuf[0] && 'R' == Mode_TxBuf[1])
		{
			Mode = 4;
		}
		else if('K' == Mode_TxBuf[0] && 'Y' == Mode_TxBuf[1])
		{
			Mode = 5;
		}
		else if('B' == Mode_TxBuf[0] && 'Z' == Mode_TxBuf[1])
		{
			Mode = 6;
		}
		else if('W' == Mode_TxBuf[0] && 'L' == Mode_TxBuf[1])
		{
			Mode = 7;
		}
	}
	else
	{
		Mode = 1;
	}
	if(BLUETOOTH_MODE == Mode)			//����
	{
		Bluetooth_Mode();
	}
	else if(ROCKER_MODE == Mode) 		//�ֱ�ҡ�˿���
	{
		while(1)
		{
			Wireless_Mode();
			if(1 == ROC_FLAG)
			{
				Mode = 1;
				break;
			}
		}
	}
	else if(PLAY_MODE == Mode)  		//�ֱ��������Ʋ���
	{
		while(1)
		{
			Key_Play_Mode();
			if(1 == PLAY_FLAG)
			{
				Mode = 1;
				break;
			}
		}
	}
	else if(GRAVITY_MODE == Mode)  		//������
	{
		while(1)
		{
			Gravity_Mode();
			if(1 == MP_FLAG)
			{
				Mode = 1;
				break;
			}
		}
	}
	else if(KEY_MODE == Mode) 			//�ֱ���������
	{
		while(1)
		{
			Rocker_Key_Mode();
			if(1 == KEY_FLAG)
			{
				Mode = 1;
				break;
			}
		}
	}
	else if(AVOID_MODE == Mode) 		//����������
	{
		while(1)
		{
			Avoid_Mode();
			if(1 == AVP_FLAG)
			{
				Mode = 1;
				break;
			}
		}
	}
	else if(WS2812_MODE == Mode) 		//�ʵ�
	{
		while(1)
		{
			Ws2812_Mode();
			if(1 == WL_FLAG)
			{
				Mode = 1;
				break;
			}
		}
	}
	MP_FLAG = 0;
	ROC_FLAG = 0;
	PLAY_FLAG = 0;
	KEY_FLAG = 0;
	WL_FLAG = 0;
	AVP_FLAG = 0;
}

