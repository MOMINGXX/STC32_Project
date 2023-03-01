#include "USART.h"

uint8_t DAT1;				//存放接收的字符
uint8_t RX1_BUFF[10];		//接收的数据	缓冲区
uint8_t RX1_DAT[10];		//存放接收的数据
uint8_t RX1_COUNT=0;		//接收计数
bit Flag1 = 0;				//标志位

/****
	* @brief	串口引脚配置	 准双向口  		  
	* @param   	无
	* @return   无 	
	* Sample usage:GPIO_Config()；
    */
static void GPIO_Config()
{
    //P30双向IO口
    P3M0 &= 0x01;   
    P3M1 &= 0x01; 

    //P31双向IO口
    P3M0 &= 0x02;   
    P3M1 &= 0x02; 
}

/****
	* @brief	串口 配置	   		  
	* @param   	无
	* @return   无 	
	* Sample usage:Uart_Config();
    */
static void Uart_Config()	
{
    
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = BRT;			//设置定时初始值
	T2H = BRT >> 8;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时    
    IP |= 0x00;
    IPH |= 0x10;        //优先级2
    ES = 1;         //开启总中断 及 串口1中断
}

/****
	* @brief	串口初始化	   		  
	* @param   	无
	* @return   无  	
	* Sample usage:Usart_Init();
    */
void Usart_Init()	
{
    GPIO_Config();
    Uart_Config();	
}

/****
	* @brief	串口发送一个字节	   		  
	* @param   	Byte	要发送的字节  
	* @return   无  	
	* Sample usage:Uart_SendByte(0x45);  
    */
void Usart_SendByte(uint8_t Byte)
{
    SBUF = Byte;
    while(!(SCON & 0x02));	//等待发送完毕 TI置1
    SCON &= ~0x02;			//软件置0
}

/****
	* @brief	串口发送一个字符串 
    * @param    String	要发送的字符串 
	* @return   无        	
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
	* @brief    串口发送数组
	* @param   	Buf     要发送的数组 
	* @param   	Len		数组长度
	* @return   无        	
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
	* @brief	平方计算  			  
    * @param   	X   基值
    * @param    Y   指数的值
	* @return   Result   x 的 y 次幂的结果	
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
	* @brief	串口发送数字  			  
    * @param   	Number  要发送的数字
    * @param    Length  数字的长度
	* @return   无  	
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
	@brief      printf打印
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
		if(DAT1 != '#')				//'#'结束标志
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

