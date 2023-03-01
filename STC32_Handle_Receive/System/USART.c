#include "USART.h"

uint8_t DAT1;				//��Ž��յ��ַ�
uint8_t RX1_BUFF[10];		//���յ�����	������
uint8_t RX1_DAT[10];		//��Ž��յ�����
uint8_t RX1_COUNT=0;		//���ռ���
bit Flag1 = 0;				//��־λ

/****
	* @brief	������������	 ׼˫���  		  
	* @param   	��
	* @return   �� 	
	* Sample usage:GPIO_Config()��
    */
static void GPIO_Config()
{
    //P30˫��IO��
    P3M0 &= 0x01;   
    P3M1 &= 0x01; 

    //P31˫��IO��
    P3M0 &= 0x02;   
    P3M1 &= 0x02; 
}

/****
	* @brief	���� ����	   		  
	* @param   	��
	* @return   �� 	
	* Sample usage:Uart_Config();
    */
static void Uart_Config()	
{
    
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = BRT;			//���ö�ʱ��ʼֵ
	T2H = BRT >> 8;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ    
    IP |= 0x00;
    IPH |= 0x10;        //���ȼ�2
    ES = 1;         //�������ж� �� ����1�ж�
}

/****
	* @brief	���ڳ�ʼ��	   		  
	* @param   	��
	* @return   ��  	
	* Sample usage:Usart_Init();
    */
void Usart_Init()	
{
    GPIO_Config();
    Uart_Config();	
}

/****
	* @brief	���ڷ���һ���ֽ�	   		  
	* @param   	Byte	Ҫ���͵��ֽ�  
	* @return   ��  	
	* Sample usage:Uart_SendByte(0x45);  
    */
void Usart_SendByte(uint8_t Byte)
{
    SBUF = Byte;
    while(!(SCON & 0x02));	//�ȴ�������� TI��1
    SCON &= ~0x02;			//�����0
}

/****
	* @brief	���ڷ���һ���ַ��� 
    * @param    String	Ҫ���͵��ַ��� 
	* @return   ��        	
	* Sample usage:Uart_SendString("ABCD"); 
    */
void Usart_SendString(uint8_t *String)
{
    while(*String != '\0')
    {
        Usart_SendByte(*String++);
    }
}

/****
	* @brief    ���ڷ�������
	* @param   	Buf     Ҫ���͵����� 
	* @param   	Len		���鳤��
	* @return   ��        	
	* Sample usage:Uart_SendString(arr,sizeof(arr)/sizeof(arr[0]));    
	*/
void Usart_SendBuff(uint8_t *Buff,uint16_t Len)
{
	while(Len--)
	{
		Usart_SendByte(*Buff++);
	}
}

/****
	* @brief	ƽ������  			  
    * @param   	X   ��ֵ
    * @param    Y   ָ����ֵ
	* @return   Result   x �� y ���ݵĽ��	
	* Sample usage: Usart_Pow(10,Length);
    */
static uint32_t Usart_Pow(uint32_t X, uint32_t Y)
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
void Usart_SendNumber(uint32_t Number,uint8_t Length)
{
    while(Length--)
    {
        Usart_SendByte(Number / Usart_Pow(10,Length) % 10 + '0'); //23 2 3
    }
}

void Usart_sprintf(char *format, ...)
{
    char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Usart_SendString(String);
}

/****
	@brief      printf��ӡ
	@param   	c
	@return     c        	
	Sample usage:  printf("Hello\n"); 
****/
int8_t putchar(int8_t c)
{
	if(c == '\n')
	{
		Usart_SendByte(0x0D);
	}
	Usart_SendByte(c);
	return c;
}

void Uart1_Routine() interrupt 4
{
	static uint8_t i=0;
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

