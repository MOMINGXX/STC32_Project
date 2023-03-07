#ifndef __MP3_TF_16P_H__
#define __MP3_TF_16P_H__

#include "USART.h"

#define Next_Song  					0x01
#define Last_Song  					0x02
#define Specify_Music  				0x03		//ָ����Ŀ 1-2999 
#define Add_Volume 					0x04
#define Reduce_Volume 				0x05
#define Specify_Volume  			0x06		//����  0-30
#define Specify 					0x07		//ָ��	EQ0/1/2/3/4/5
#define Ring_Specify_play 			0x08		//��ָ����Ŀ����
#define Specify_play  				0x09		//ָ������ 1/2/3/4/5(U/SD/AUX/SLEEP/FLASH)
#define Sleep  						0x0A		//˯��
#define Module_Reset  				0x0C		//ģ�鸴λ
#define Play  						0x0D
#define Suspended  					0x0E		//��ͣ
#define Specify_Folder 		    	0x0F		//ָ���ļ���  1-10(��Ҫ�Լ��趨) 
#define Full_Loop 					0x11		//ȫ��ѭ������	[1:ѭ������][0:ֹͣѭ������] 
#define Designated_MP3_Folder  		0x12		//ָ��MP3�ļ���	0--9999 
#define Call_Waiting  				0x13		//�岥���		0--9999 
#define Designated_15Folder  		0x14		//֧��15�ļ���
#define Stop_Slots  				0x15		//ֹͣ�岥�����ű���
#define Stop_Song  					0x16		//ָ���ļ���ѭ������ 
#define Specify_Folder_play 		0x17		//ָ���ļ���ѭ������
#define Random_Broadcast 			0x18		//�������
#define Loop 						0x19		//ѭ������ 
#define Start_Close_DAC  			0x1A		//�����͹ر� DAC

void Uart_SendCMD(uint8_t CMD ,uint8_t feedback ,uint16_t dat);
void Uart_SendFolder(uint8_t CMD,uint8_t feedback,uint8_t Folder,uint8_t dat);

#endif 
