#include "NRF24L01.h"

/* uint8_t NRF24L01_RX_BUF[NRF24L01_RX_PLOAD_WIDTH];		//�������ݻ���
uint8_t NRF24L01_TX_BUF[NRF24L01_TX_PLOAD_WIDTH];		//�������ݻ��� */
const uint8_t NRF24L01_TX_ADDRESS[NRF24L01_TX_ADR_WIDTH] = {0x00,0xc2,0xc2,0xc2,0xc2};  // ����һ����̬���͵�ַ
const uint8_t NRF24L01_RX_ADDRESS[NRF24L01_RX_ADR_WIDTH] = {0x00,0xc2,0xc2,0xc2,0xc2};

static void NRF24L01_GPIO_Config()
{
	P1M0 &= ~0x40; 
	P1M1 &= ~0x40; 		//P16Ϊ׼˫��� 

    P3M0 &= ~0x08; 
	P3M1 &= ~0x08; 		//P33Ϊ׼˫��� 

	NRF24L01_CE = 1;
}

void NRF24L01_Init()
{
    NRF24L01_GPIO_Config();
    SPI_Init();
}

static uint8_t NRF24L01_WriteReg(uint8_t Reg,uint8_t Data)
{
    uint8_t Status;
    SPI_CS = 0;
    Status = SPI_Send_ReceiveByte(Reg);
    SPI_Send_ReceiveByte(Data);
    SPI_CS = 1;
    return Status;
}

static uint8_t NRF24L01_ReadReg(uint8_t Reg)
{
    uint8_t Data;
    SPI_CS = 0;
    SPI_Send_ReceiveByte(Reg);
    Data = SPI_Send_ReceiveByte(NRF24L01_NOP);
    SPI_CS = 1;
    return Data;
}

static uint8_t NRF24L01_WriteBuff(uint8_t Reg,uint8_t *Buff,uint8_t Len)
{
    uint8_t Status;
    uint8_t i;
    SPI_CS = 0;
    Status = SPI_Send_ReceiveByte(Reg);
    for(i = 0; i < Len; i++)
    {
        SPI_Send_ReceiveByte(*Buff++);
    }
    SPI_CS = 1;
    return Status;
}

static uint8_t NRF24L01_ReadBuff(uint8_t Reg,uint8_t *Buff,uint8_t Len)
{
    uint8_t Status;
    uint8_t i;
    SPI_CS = 0;
    SPI_Send_ReceiveByte(Reg);
    for(i = 0; i < Len; i++)
    {
        *Buff++ = SPI_Send_ReceiveByte(NRF24L01_NOP);
    }
    SPI_CS = 1;
    return Status;
}

uint8_t NRF24L01_Check()
{
	uint8_t Tx_Buff[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
	uint8_t Rx_Buff[5] = { 0 };
	uint8_t i; 
	 
	//д��5���ֽڵĵ�ַ
	NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_TX_ADDR,Tx_Buff,5);
	//����д��ĵ�ַ 
	NRF24L01_ReadBuff(NRF24L01_TX_ADDR,Rx_Buff,5); 
	 
	//�Ƚ�             
	for(i = 0; i < 5; i++)
	{
		if(Tx_Buff[i] != Rx_Buff[i])
		break;
	} 
	       
	if(i != 5)
		return ERROR ;        //MCU��NRF24L01����ʧ��
	else
		return SUCCESS ;      //MCU��NRF24L01��������
}

/****
	* @brief    NRF24L01 ���ý���ģʽ  
	* @param   	��
    * @return   ��
	* Sample usage:NRF24L01_RX_Mode();
    */
void NRF24L01_RX_Mode()
{
	NRF24L01_CE = 0;

    NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_RX_ADDR_P0,(uint8_t*)NRF24L01_RX_ADDRESS,NRF24L01_RX_ADR_WIDTH);//дRX�ڵ��ַ
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  //NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_SETUP_RETR,0x1A);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_CH,NRF24L01_CHANAL);      //����RFͨ��Ƶ��    
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RX_PW_P0,NRF24L01_RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��      
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_SETUP,0x0f); //����TX�������,0db����,2Mbps,���������濪��   
    
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_CONFIG, 0x0f);  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
 
	NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,0xff);	//��������жϱ�־λ
	   
    NRF24L01_CE = 1;
}  

/****
	* @brief    NRF24L01 ���÷���ģʽ
	* @param   	��
    * @return   ��
	* Sample usage:NRF24L01_TX_Mode();
    */
void NRF24L01_TX_Mode()
{  
	NRF24L01_CE = 0;

    NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_TX_ADDR,(uint8_t*)NRF24L01_TX_ADDRESS,NRF24L01_TX_ADR_WIDTH);    //дTX�ڵ��ַ 

    NRF24L01_WriteBuff(NRF24L01_W_REGISTER + NRF24L01_RX_ADDR_P0,(uint8_t*)NRF24L01_RX_ADDRESS,NRF24L01_RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK   

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_SETUP_RETR,0x1A);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_CH,NRF24L01_CHANAL);       //����RFͨ��ΪCHANAL

    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	
    NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�

	NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,0xff);	//��������жϱ�־λ
	
	Delay_ms(150);
    /*CE���ߣ����뷢��ģʽ*/	
    NRF24L01_CE = 1;
}

/****
	* @brief    NRF24L01 ����һ������	  
    * @return   TxBuff    �����͵������׵�ַ
    * @return   NRF24L01_TX_DS  �������
    *           NOP     �������
	* Sample usage:NRF24L01_TxPacket(Buff);
    */
uint8_t NRF24L01_TxPacket(uint8_t *TxBuff)
{
	uint8_t Status;
	NRF24L01_CE = 0;
    NRF24L01_WriteBuff(NRF24L01_W_TX_PAYLOAD,TxBuff,NRF24L01_TX_PLOAD_WIDTH); //д���ݵ� BUFF  32���ֽ�
    NRF24L01_CE = 1;

    while(RESET != NRF24L01_IRQ);                 //�ȴ��������
    Status = NRF24L01_ReadReg(NRF24L01_STATUS);     //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,Status);  //���TX_DS��MAX_RT�жϱ�־
	if(Status & NRF24L01_MAX_RT)                   //�ﵽ����ط�����
	{
		NRF24L01_WriteReg(NRF24L01_FLUSH_TX,0xFF); //���TX FIFO�Ĵ��� 
		return NRF24L01_MAX_RT; 
	}
	if(Status & NRF24L01_TX_DS)//�������
	{
		return NRF24L01_TX_DS;
	}
	return 0xFF;                 //����ԭ����ʧ��
} 

/****
	* @brief    NRF24L01 ����һ������	  
    * @return   RxBuff  �����յ������׵�ַ
    * @return   0  �յ�����
    *           1  û�յ��κ�����
	* Sample usage:NRF24L01_RxPacket(Buff);
    */
uint8_t NRF24L01_RxPacket(uint8_t *RxBuff)
{
	uint8_t Status; 
	if(RESET == NRF24L01_IRQ)
	{
		/*��ȡStatus�Ĵ�����ֵ  */               
		Status = NRF24L01_ReadReg(NRF24L01_STATUS);
		//printf("Status:0x%x\n",Status);
		/* ����жϱ�־*/      
		NRF24L01_WriteReg(NRF24L01_W_REGISTER + NRF24L01_STATUS,Status);

		/*�ж��Ƿ���յ�����*/
		if(Status & NRF24L01_RX_DR)                                 //���յ�����
		{
			NRF24L01_ReadBuff(NRF24L01_R_RX_PAYLOAD,RxBuff,NRF24L01_RX_PLOAD_WIDTH);//��ȡ����
			NRF24L01_WriteReg(NRF24L01_FLUSH_RX,0xFF);               //���RX FIFO�Ĵ���
			return 0; 
		}
	}
	return 1;                    //û�յ��κ�����
}

/****
	* @brief    ���NRF24L01�Ƿ����  ����ӡ��Ϣ
	* @param   	��
    * @return   ��
	* Sample usage:NRF24L01_Check_detection();
    */
void NRF24L01_Check_detection()
{
	while(NRF24L01_Check() != SUCCESS)
	{
		printf("NRF24L01_Check failed !");
		printf("\n");
		Delay_ms(1000);
	}
	printf("NRF24L01_Check succeed !");
	printf("\n");
}
