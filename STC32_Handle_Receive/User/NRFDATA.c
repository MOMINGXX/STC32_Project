#include "NRFDATA.h"

uint8_t ROCKER_RxBuf[10] = " 0 ";//摇杆接收数据缓冲区
uint8_t MPU6050_RxBuf[20];	//陀螺仪接收数据缓冲区
uint8_t KEY_RxBuf[16];		//按键接收数据缓冲区
uint8_t Mode_TxBuf[4];		//模式接收缓冲区
uint8_t Mode = 2;

void Bluetooth_Mode()
{
	static Mode_Flag = 2;
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

void Wireless_Mode()
{
	uint8_t PWM1,PWM2;			//PWM1 左  PWM2 右
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(ROCKER_RxBuf) == RESET)
	{	
		PWM1 = PWM2 = (100 - ROCKER_RxBuf[2]);
		PWMB_SetCompare5(PWM1);
		PWMB_SetCompare6(PWM2);
		if(ROCKER_RxBuf[7] < 100 && ROCKER_RxBuf[7] >= 55)
		{
			MOTOR_BackWard();
		}
		else if(ROCKER_RxBuf[7] <= 45 && ROCKER_RxBuf[7] >= 0)
		{
			MOTOR_ForWard();
		}
		else if(ROCKER_RxBuf[9] < 100 && ROCKER_RxBuf[9] >= 55)
		{
			MOTOR_TurnLeft();
		}
		else if(ROCKER_RxBuf[9] <= 45 && ROCKER_RxBuf[9] >= 0)
		{
			MOTOR_Turnright();
		}
		else if(ROCKER_RxBuf[9] < 55 && ROCKER_RxBuf[9] > 45)
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
	}
//	else printf("ROCKER Receive failed !\n"); 
}

void Key_Play_Mode()
{
	static uint8_t Volume = 20;
	Uart_SendCMD(Specify_Volume,0,Volume);		//初始音量20
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(KEY_RxBuf) == RESET)
	{
		if(5 == KEY_RxBuf[8])
		{
			Uart_SendCMD(Play,0,0);
		}
		else if(8 == KEY_RxBuf[11])
		{
			Uart_SendCMD(Suspended,0,0);
		}
		else if(6 == KEY_RxBuf[9])
		{
			Uart_SendCMD(Last_Song,0,0);
		}
		else if(7 == KEY_RxBuf[10])
		{
			Uart_SendCMD(Next_Song,0,0);
		}
		else if(9 == KEY_RxBuf[12])
		{
			Volume ++;
			if(Volume >= 30)
			{
				Volume = 30;
			}
			Uart_SendCMD(Add_Volume,0,Volume);
		}
		else if(10 == KEY_RxBuf[13])
		{
			Volume --;
			if(Volume >= 30)
			{
				Volume = 0;
			}
			Uart_SendCMD(Reduce_Volume,0,Volume);
		}
		else if(11 == KEY_RxBuf[14])
		{
			Uart_SendCMD(Random_Broadcast,0,0);
		}
	}
}

void Gravity_Mode()
{
	
}

void Rocker_Key_Mode()
{
	static uint8_t PWM = 35;
	NRF24L01_RX_Mode();
	Delay_ms(6);
	if(NRF24L01_RxPacket(KEY_RxBuf) == RESET)
	{
		if(5 == KEY_RxBuf[8])
		{
			MOTOR_ForWard();
		}
		else if(8 == KEY_RxBuf[11])
		{
			MOTOR_BackWard();
		}
		else if(6 == KEY_RxBuf[9])
		{
			MOTOR_TurnLeft();
		}
		else if(7 == KEY_RxBuf[10])
		{
			MOTOR_Turnright();
		}
		else if(10 == KEY_RxBuf[13])
		{
			PWM  ++;
			if(PWM >= 100)
			{
				PWM = 100;
			}
		}
		else if(11 == KEY_RxBuf[14])
		{
			PWM  --;
			if(PWM > 100)
			{
				PWM = 0;
			}
		}
		
		else if(9 == KEY_RxBuf[12])
		{
			MOTOR_Stop();	
			PWMB_SetCompare5(0);
			PWMB_SetCompare6(0);
		}
	}
}

void Avoid_Mode()
{
	
}

void Ws2812_Mode()
{

}

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

void Mode_Option()
{
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
	switch(Mode)
    {
        case BLUETOOTH_MODE:
        Bluetooth_Mode();
        break;
        case ROCKER_MODE:
        Wireless_Mode();
        break;
        case PLAY_MODE:
        Key_Play_Mode();
        break;
        case GRAVITY_MODE:
        Gravity_Mode();
        break;
        case KEY_MODE:
        Rocker_Key_Mode();
        break;
        case AVOID_MODE:
        Avoid_Mode();
        break;
        case WS2812_MODE:
        Ws2812_Mode();
        break;
        default:
            break;
    }
}

