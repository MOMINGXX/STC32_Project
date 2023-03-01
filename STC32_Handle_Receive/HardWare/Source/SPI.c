#include "SPI.h"

static void SPI_GPIO_Config()
{
	P1M1 &= ~0x38;
    P1M0 &= ~0x38;      //P13 P14 P15Ϊ׼˫���  0011 1000

    P5M0 = 0x00; 
	P5M1 = 0x00; 		//P50Ϊ׼˫���
	
	SPI_CS = 1;
	SPI_SCK = 0;
}

static void SPI_Config()
{
	SPDAT = 0x00;			//��ʼ��SPI����
	SPSTAT = 0xC0;			//���SPI״̬λ  
    SPCTL = 0xD3;          //����SS-ʹ��SPI-��λ����-����ģʽ-ʱ�ӿ���ʱΪ�͡�������(��1������)����
}

void SPI_Init()
{
    SPI_GPIO_Config();
    #if HARD
    SPI_Config();
    #endif
}

/****
	* @brief	SPI ���� ���� һ���ֽ�����   		  
	* @param	Byte	���͵�����
	* @return   ByteReceive ���յ����� 	
	* Sample usage:SOFT_SPI_Config();
    */
#if SOFT
uint8_t SPI_Send_ReceiveByte(uint8_t Byte)
{
	uint8_t i, ByteReceive = 0x00;
	
	for (i = 0; i < 8; i ++)
	{
		SPI_MOSI = (Byte & (0x80 >> i));
		SPI_SCK = 1;
		if (SPI_MISO == 1){ByteReceive |= (0x80 >> i);}
		SPI_SCK = 0;
	}
	return ByteReceive;
}

#elif HARD
uint8_t SPI_Send_ReceiveByte(uint8_t Byte)
{
    SPDAT = Byte;
    while(!(SPSTAT & 0x80));		//�ȴ��������SPIF=0
    SPSTAT &= ~0x3F;				//������ɺ���SPIF=1��WCOL=1�����־
	return SPDAT;
}
#endif

/****
	* @brief	SPI ����һ���ֽ�����   		  
	* @param	ByteSend	���͵�����
    * @return   ��
	* Sample usage:SPI_SendByte(1);
    */
void SPI_SendByte(uint8_t Byte)
{
    SPDAT = Byte;
    while(!(SPSTAT & 0x80)); 		//�ȴ��������SPIF=0
    SPSTAT &= ~0x3F;         		//������ɺ���SPIF=1��WCOL=1�����־
}

/****
	* @brief	SPI ���� ���� һ���ֽ�����   		  
	* @param	��
	* @return   SPDAT ���յ����� 	
	* Sample usage:SPI_ReceiveByte();
    */
uint8_t SPI_ReceiveByte()
{
    SPDAT = 0xff;
    while(!(SPSTAT & 0x80));		//�ȴ��������SPIF=0
    SPSTAT &= ~0x3F;        		//������ɺ���SPIF=1��WCOL=1�����־
    return SPDAT;
}

