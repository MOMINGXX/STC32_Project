#include "USART.h"

uint8_t DAT1;				//��Ž��յ��ַ�
uint8_t RX1_BUFF[10];		//���յ�����	������
uint8_t RX1_DAT[10];		//��Ž��յ�����
uint8_t RX1_COUNT=0;		//���ռ���
bit Flag1 = 0;				//��־λ

uint8_t RX2_BUFF[LENTH];		//���յ�����	������
uint8_t Flag3 = 0;				//��־λ

/****
	* @brief	������������	 ׼˫���  		  
	* @param   	��
	* @return   �� 	
	* Sample usage:Uart_GPIO_Config()��
    */
static void Uart_GPIO_Config()
{
    P3M1 &= ~0x03;   
    P3M0 &= ~0x03; 		//P30 P31˫��IO��
	
	P0M1 &= ~0x03;   
    P0M0 &= ~0x03; 		//P00 P01˫��IO��
}

/****
	* @brief	����1 ����	   		  
	* @param   	��
	* @return   �� 	
	* Sample usage:Uart_Config();
    */
static void Uart1_Config()	
{
    
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = BRT;			//���ö�ʱ��ʼֵ
	T2H = BRT >> 8;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ    
    IP |= 0x00;
    IPH |= 0x10;        //���ȼ�2
    ES = 1;         	//��������1�ж�
}

/****
	* @brief	����3 ����	   		  
	* @param   	��
	* @return   �� 	
	* Sample usage:Uart_Config();
    */
static void Uart3_Config()	
{
	S3CON = 0x10;			//8λ����,�ɱ䲨����
	T2x12 = 1;				//��ʱ��ʱ��1Tģʽ
	T2L = BRT;				//���ö�ʱ��ʼֵ
	T2H = BRT >> 8;			//���ö�ʱ��ʼֵ
	T2R = 1;				//��ʱ��2��ʼ��ʱ    
    IP3 |= 0x00;	
    IP3H |= 0x00;       	//���ȼ�
    ES3 = 1;         		//��������3�ж�
}

/****
	* @brief	���ڳ�ʼ��	   		  
	* @param   	��
	* @return   ��  	
	* Sample usage:Usart_Init();
    */
void Usartx_Init()	
{
    Uart_GPIO_Config();
    Uart1_Config();	
	Uart3_Config();
}

/****
	* @brief	���ڷ���һ���ֽ�	   		  
	* @param   	Byte	Ҫ���͵��ֽ�  
	* @return   ��  	
	* Sample usage:Uart_SendByte(0x45);  
    */
void Usartx_SendByte(USART_TypeDef USARTx,uint8_t Byte)
{
	switch(USARTx)
	{
		case USART1:
			SBUF = Byte;
			while(!(SCON & 0x02));	//�ȴ�������� TI��1
			SCON &= ~0x02;			//�����0
		break;
		case USART3:
			S3BUF = Byte;
			while(!(S3CON & 0x02));	//�ȴ�������� TI��1
			S3CON &= ~0x02;			//�����0
		break;
	}
}

/****
	* @brief	���ڷ���һ���ַ��� 
    * @param    String	Ҫ���͵��ַ��� 
	* @return   ��        	
	* Sample usage:Uart_SendString("ABCD"); 
    */
void Usartx_SendString(USART_TypeDef USARTx,uint8_t *String)
{
    while(*String != '\0')
    {
        Usartx_SendByte(USARTx,*String++);
    }
}

/****
	* @brief    ���ڷ�������
	* @param   	Buf     Ҫ���͵����� 
	* @param   	Len		���鳤��
	* @return   ��        	
	* Sample usage:Uart_SendString(arr,sizeof(arr)/sizeof(arr[0]));    
	*/
void Usartx_SendBuff(USART_TypeDef USARTx,uint8_t *Buff,uint16_t Len)
{
	while(Len--)
	{
		Usartx_SendByte(USARTx,*Buff++);
	}
}

/****
	* @brief	ƽ������  			  
    * @param   	X   ��ֵ
    * @param    Y   ָ����ֵ
	* @return   Result   x �� y ���ݵĽ��	
	* Sample usage: Usart_Pow(10,Length);
    */
static uint32_t Usartx_Pow(uint32_t X, uint32_t Y)
{
    //X^Y
    uint32_t Result = 1;
    while(Y--)
    {
        Result *= X;
    }
    return Result;
}

/****
	* @brief	���ڷ�������  			  
    * @param   	Number  Ҫ���͵�����
    * @param    Length  ���ֵĳ���
	* @return   ��  	
	* Sample usage: Usart_SendNumber(12345,5);
    */
void Usartx_SendNumber(USART_TypeDef USARTx,uint32_t Number,uint8_t Length)
{
    while(Length--)
    {
        Usartx_SendByte(USARTx,Number / Usartx_Pow(10,Length) % 10 + '0'); //23 2 3
    }
}

void Usartx_sprintf(USART_TypeDef USARTx,char *format, ...)
{
    char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Usartx_SendString(USARTx,String);
}

/****
	@brief      printf��ӡ
	@param   	c
	@return     c        	
	Sample usage:  printf("Hello\n"); 
****/
#if (PRINTF_SELECT == 1)
int8_t putchar(int8_t c)
{
	if(c == '\n')
	{
		Usartx_SendByte(USART1,0x0D);
	}
	Usartx_SendByte(USART1,c);
	return c;
}

#elif (PRINTF_SELECT == 3)

int8_t putchar(int8_t c)
{
	if(c == '\n')
	{
		Usartx_SendByte(USART3,0x0D);
	}
	Usartx_SendByte(USART3,c);
	return c;
}
#endif

void Uart1_Routine() interrupt 4
{
	static uint8_t i = 1;
	if(SCON & 0x01)
	{
		SCON &= ~0x01;
		DAT1 = SBUF;
		if(DAT1 != '#')				//'#'������־
		{
			RX1_BUFF[RX1_COUNT++] = DAT1++;
		}
		else
		{
			for(i=0;i<RX1_COUNT;i++)
			{
				RX1_DAT[i] = RX1_BUFF[i];
			}
			RX1_COUNT=0;
			Flag1=1;
		}
	}
}

static uint8_t Usart3_ReceivePacket(uint8_t Usart3_RxData,uint8_t *RX2_BUFF)
{
	static uint8_t RxState = 0;
	static uint8_t i = 1;
	switch(RxState)
	{
		case 0:
		if(0xA5 == Usart3_RxData)
		{
			RxState = 1;
			RX2_BUFF[0] = Usart3_RxData;
		}
		else RxState = 0;
		break;
		case 1:
		RX2_BUFF[i] = Usart3_RxData;
		i++;
		if(i >= LENTH)
		{
			i = 1;
			RxState = 0;
			return SUCCESS;
		}
		break;
		default:
			break;
	}
	return ERROR;
}

void Usart3_Routine() interrupt 17
{
	uint8_t Usart3_RxData = 0;
	
	if(S3CON & 0x01)
	{
		S3CON &= ~0x01;
		Usart3_RxData = S3BUF;
		Flag3 = Usart3_ReceivePacket(Usart3_RxData,RX2_BUFF);
	}
}



//void Uart3_Routine() interrupt 17
//{
//	static uint8_t RxState = 0;
//	static uint8_t pRxPacket = 0;
//	uint8_t RxData = 0;
//	
//	if(S3CON & 0x01)
//	{
//		S3CON &= ~0x01;
//		RxData = S3BUF;
//		if(0 == RxState)
//		{
//			if(0xA5 == RxData)
//			{
//				RxState = 1;
//				pRxPacket = 0 ;
//			}
//		}
//		else if(1 == RxState)
//		{
//			if(0x5A == RxData)
//			{
//				RxState = 2;
//			}
//			else
//			{
//				RX2_BUFF[pRxPacket] = RxData;
//				pRxPacket++;
//			}
//		}
//		else if (2 == RxState)
//		{
//			RxState = 0;
//			Flag3 = 1;
//		}
//	}
//}

