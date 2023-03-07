#include "MP3_TF_16P.h"

static uint8_t Send_Buf[10] = {0} ; 

/****
	* @brief	��У��   			  
	* @param   	Str     ���յ�ָ���ַ
    * @param    Len     ָ���	
	* @return   ��	
	* Sample usage: DoSum(Send_buf,6);
    */
static void DoSum(uint8_t *Str,uint8_t Len)
{
    uint16_t xorsum = 0;
    uint8_t i = 0;
    for(i=0;i<Len;i++)
    {
        xorsum += Str[i];
    }
    xorsum = 0 - xorsum;
    *(Str + i) = (uint8_t)(xorsum >> 8);
    *(Str + i + 1) = (uint8_t)(xorsum & 0x00ff);
}

/****
	* @brief	����ָ��			
	* @param    Len     ָ���	
	* @return   ��	
	* Sample usage: Send_Cmd(6);
    */
static void Send_Cmd(uint8_t Len)
{
    uint8_t i = 0;
    Usartx_SendByte(USART1,0x7E);        //��ʼ
    for(i=0;i<Len;i++)
    {
        Usartx_SendByte(USART1,Send_Buf[i]);     //����
    }
    Usartx_SendByte(USART1,0xEF);        //����
}

/****
	* @brief	��ģ�鷢��ָ��	
    * @param    CMD         ����ָ��    ���� ��ͣ...
    * @param 	feedback	�����    0x00 ������  0x01 ����
	* @param    dat         ָ������	0 ~ 0xffff
    * @return   ��	
	* Sample usage: Uart_SendCMD(Specify_Music ,0x00,36);
    */
void Uart_SendCMD(uint8_t CMD ,uint8_t feedback ,uint16_t dat)
{
    Send_Buf[0] = 0xff; //�����ֽ� 
    Send_Buf[1] = 0x06; //����
    Send_Buf[2] = CMD; //����ָ��
    Send_Buf[3] = feedback;//�Ƿ���Ҫ����
    Send_Buf[4] = (uint8_t)(dat >> 8);//datah 
    Send_Buf[5] = (uint8_t)(dat); //datal 
    DoSum(&Send_Buf[0],6); //У��
    Send_Cmd(8); 
}

/****
	* @brief	����ָ���ļ���ָ������ 
    * @param    CMD         ����ָ��    ���� ��ͣ...
    * @param 	feedback	�����    0x00 ������  0x01 ����
    * @param    Folder		ָ���ļ���  0-99
	* @param    dat         ָ������	0 ~ 0xff
    * @return   ��	
	* Sample usage:Uart_SendFolder(Specify_Folder,0x00,2,6);
    */
void Uart_SendFolder(uint8_t CMD,uint8_t feedback,uint8_t Folder,uint8_t dat) 
{
	Send_Buf[0] = 0xff; //�����ֽ� 
	Send_Buf[1] = 0x06; //����
	Send_Buf[2] = CMD; //����ָ��
	Send_Buf[3] = feedback;//�Ƿ���Ҫ����
	Send_Buf[4] = (uint8_t)(Folder);
	Send_Buf[5] = (uint8_t)(dat); 
	DoSum(&Send_Buf[0],6); //У��
	Send_Cmd(8);  //���ʹ�֡����
}
