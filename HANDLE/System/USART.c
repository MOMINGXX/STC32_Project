#include "USART.h"

uint8_t Usart_RxHEX[RXHEX_MAX];
char Usart_RxCharacter[RXCHA_MAX];
uint8_t Usart_RxFlag;

/****
	* @brief	USART GPIO ����     			  
	* @param   	��
	* @return   ��  	
	* Sample usage:Usart_GPIO_Config();
    */
static void Usart_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //����GPIOʱ��
    SPECIFIE_USART_GPIO_APBxCLKCMD(SPECIFIE_USART_GPIO_CLK,ENABLE);
    //��������
    GPIO_InitStruct.GPIO_Pin = SPECIFIE_USART_TX_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;               //�������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPECIFIE_USART_TX_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SPECIFIE_USART_RX_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;           //��������
    GPIO_Init(SPECIFIE_USART_RX_GPIO_PORT,&GPIO_InitStruct);
}

/****
	* @brief	USART ����     			  
	* @param   	��
	* @return   ��  	
	* Sample usage:Usart_Config();
    */
static void Usart_Config()
{
    USART_InitTypeDef USART_InitStruct;
    //����USARTʱ��
    SPECIFIE_USART_APBxCLKCMD(SPECIFIE_USART_CLK,ENABLE);
    //��������
    USART_InitStruct.USART_BaudRate = SPECIFIE_USART_BAUDRATE;                      //������
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    //Ӳ������������
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;        //���� �� ���� ģʽ
    USART_InitStruct.USART_Parity = USART_Parity_No;                    //��У��
    USART_InitStruct.USART_StopBits = USART_StopBits_1;                 // 1 ֹͣλ
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;            // 8 ����λ
    USART_Init(SPECIFIE_USARTx,&USART_InitStruct);
 
    //���������ж�
    USART_ITConfig(SPECIFIE_USARTx,USART_IT_RXNE,ENABLE);

    //�������ڣ�ʹ�ܣ�
    USART_Cmd(SPECIFIE_USARTx,ENABLE);   
}

/****
	* @brief	NVIC ����      			  
	* @param   	��
	* @return   ��  	
	* Sample usage:Usart_NVIC_Config();
    */
static void Usart_NVIC_Config()
{
    NVIC_InitTypeDef NVIC_InitStruct;

    //���ȼ�������
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    //����NVIC����
    NVIC_InitStruct.NVIC_IRQChannel=SPECIFIE_USART_IRQChannel;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;        //��ռ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;               //�����ȼ�
    NVIC_Init(&NVIC_InitStruct);
}

/****
	* @brief	USART��ʼ��      			  
	* @param   	��
	* @return   ��  	
	* Sample usage:Usart_Init();
    */
void Usart_Init()
{
    Usart_GPIO_Config();
    Usart_Config();
    Usart_NVIC_Config();
}

/****
	* @brief	���ڷ���һ��8λ����      			  
	* @param   	USARTx  ѡ�񴮿ڻ񴮿�����      USART1, USART2, USART3, UART4 or UART5
    * @param   	Byte    ���͵�����
	* @return   ��  	
	* Sample usage:Usart_SendByte(SPECIFIE_USARTx,0x41);
    */
void Usart_SendByte(USART_TypeDef *USARTx,uint8_t Byte)
{
    USART_SendData(USARTx,Byte);
    while(RESET == USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
}

/****
	* @brief	���ڷ���һ��16λ����      			  
	* @param   	USARTx  ѡ�񴮿ڻ񴮿�����      USART1, USART2, USART3, UART4 or UART5
    * @param   	Byte    ���͵�����
	* @return   ��  	
	* Sample usage:Usart_SendHalfWorld(SPECIFIE_USARTx,0x4122);
    */
void Usart_SendHalfWorld(USART_TypeDef *USARTx,uint16_t Byte)
{
    uint8_t TempH,TempL;
    TempH = (Byte & 0xFF00) >> 8;
    TempL = Byte & 0xFF;
    Usart_SendByte(USARTx,TempH);
    Usart_SendByte(USARTx,TempL);
}

/****
	* @brief	���ڷ����ַ���    			  
	* @param   	USARTx  ѡ�񴮿ڻ񴮿�����      USART1, USART2, USART3, UART4 or UART5
    * @param   	String  Ҫ���͵��ַ���
	* @return   ��  	
	* Sample usage: Usart_SendByte(SPECIFIE_USARTx,0x4122);
    */
void Usart_SendString(USART_TypeDef *USARTx,char *String)
{
    while(*String != '\0')
    {
        Usart_SendByte(USARTx,*String++);
    }
}

/****
	* @brief	���ڷ�������   			  
	* @param   	USARTx  ѡ�񴮿ڻ񴮿�����      USART1, USART2, USART3, UART4 or UART5
    * @param   	Buff    ���͵������ַ
    * @param    Length  ����ĳ���
	* @return   ��  	
	* Sample usage: Usart_SendBuff(SPECIFIE_USARTx,arr,5);
    */
void Usart_SendBuff(USART_TypeDef *USARTx ,uint8_t *Buff, uint16_t Length)
{
    while(Length--)
    {
        Usart_SendByte(USARTx,*Buff++);
    }
}

/****
	* @brief	ƽ������  			  
    * @param   	X        ��ֵ
    * @param    Y        ָ����ֵ
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
	* @param   	USARTx  ѡ�񴮿ڻ񴮿�����      USART1, USART2, USART3, UART4 or UART5
    * @param   	Number  Ҫ���͵�����
    * @param    Length  ���ֵĳ���
	* @return   ��  	
	* Sample usage: Usart_SendNumber(SPECIFIE_USARTx,12345,5);
    */
void Usart_SendNumber(USART_TypeDef *USARTx,uint32_t Number,uint8_t Length)
{
    while(Length--)
    {
        Usart_SendByte(USARTx,Number / Usart_Pow(10,Length) % 10 + '0'); //23 2 3
    }
}

//printf�ض��� ��ӡ    
int fputc(int c,FILE *pf)
{
    if(c == '\n')
    {
        Usart_SendByte(SPECIFIE_USARTx,0x0D);
    }
    Usart_SendByte(SPECIFIE_USARTx,(uint8_t)c);
    return c;
}

//scanf�ض��� ����
int fgetc(FILE *pf)
{
	//�ȴ�������������
	while(RESET == USART_GetFlagStatus(SPECIFIE_USARTx,USART_FLAG_TXE));
	return (int)USART_ReceiveData(SPECIFIE_USARTx);
}

/****
	* @brief	���ڴ�ӡ 			  
	* @param   	format  �ַ�����������Ҫ��д�뵽�ַ��� str ���ı��������԰���Ƕ��� format ��ǩ��
    *                   format ��ǩ�ɱ����ĸ��Ӳ�����ָ����ֵ�滻������������и�ʽ��  
	* @return   ��  	
	* Sample usage: Usart_sprintf("Number=%d\r\n",125);
    */
void Usart_sprintf(char *format, ...)
{
    char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Usart_SendString(SPECIFIE_USARTx,String);
}

#ifdef RX_HEX
uint8_t Usart_GetRxFlag()
{
    if(Usart_RxFlag == 1)
    {
        Usart_RxFlag = 0 ;
        return 1;
    }
    return 0;
}

void SPECIFIE_USART_IRQHNADLER()
{
    static uint8_t RX_State = 0;
    static uint8_t RX_packet = 0;
    if( SET == USART_GetITStatus(SPECIFIE_USARTx,USART_IT_RXNE))
    {
        uint8_t RX_Data = USART_ReceiveData(SPECIFIE_USARTx);
        if(RX_State == 0)
        {
            if(RX_Data == 0xFF)
            {
                RX_State = 1;
                RX_packet = 0;
            }
        }
        else if(RX_State == 1)
        {
            Usart_RxHEX[RX_packet] = RX_Data;
            RX_packet++;
            if(RX_MAX <= RX_packet)
            {
                RX_State = 2;
            }
        }
        else if(RX_State == 2)
        {
            if(RX_Data == 0xFE)
            {
                RX_State = 0;
                Usart_RxFlag = 1 ;
            }
        }
        USART_ClearITPendingBit(SPECIFIE_USARTx,USART_IT_RXNE);
    }
}
#else //RX_CHARACTER
void SPECIFIE_USART_IRQHNADLER()
{
    static uint8_t RX_State = 0;
    static uint8_t RX_packet = 0;
    if( SET == USART_GetITStatus(SPECIFIE_USARTx,USART_IT_RXNE))
    {
        char RX_Data = USART_ReceiveData(SPECIFIE_USARTx);
        if(RX_State == 0)
        {
            if(RX_Data == '@' && Usart_RxFlag == 0)
            {
                RX_State = 1;
                RX_packet = 0;
            }
        }
        else if(RX_State == 1)
        {
            if(RX_Data == '\r')
            {
                RX_State = 2;
            }
            else 
            {
                Usart_RxCharacter[RX_packet] = RX_Data;
                RX_packet++;
            }
        }
        else if(RX_State == 2)
        {
            if(RX_Data == '\n')
            {
                RX_State = 0;
                Usart_RxCharacter[RX_packet] = '\0';
                Usart_RxFlag = 1 ;
            }
        }
        USART_ClearITPendingBit(SPECIFIE_USARTx,USART_IT_RXNE);
    }
}
#endif


