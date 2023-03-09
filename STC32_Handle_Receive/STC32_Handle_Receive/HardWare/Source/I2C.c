#include "I2C.h"

/****
	* @brief	I2C_SCL ����д��0 / 1     			  
	* @param   	BitValue    д��� 0 / 1 
	* @return   ��  	
	* Sample usage:IIC_SCL(1);
    */
static void I2C_SCL(uint8_t BitValue)
{
    I2C_SCL_PIN = BitValue;
    //Delay10us();
}

/****
	* @brief	I2C_SDA ����д��0 / 1     			  
	* @param   	BitValue    д��� 0 / 1 
	* @return   ��  	
	* Sample usage:IIC_SDA(1);
    */
static void I2C_SDA(uint8_t BitValue)
{
    I2C_SDA_PIN = BitValue;
    //Delay10us();
}

/****
	* @brief	I2C_SDA ��ȡ����״̬    			  
	* @param   	��
	* @return   BitValue    ��ȡ��״̬ 0 / 1 	
	* Sample usage:IIC_R_SDA();
    */
static uint8_t I2C_R_SDA()
{
    uint8_t BitValue;
    BitValue = I2C_SDA_PIN;
    //Delay10us();
    return BitValue;
}

/****
	* @brief	���� I2C   			  
	* @param   	��		   	
	* @return   ��
	* Sample usage:I2C_Start()
    */
void I2C_Start()
{
    I2C_SDA(1);
    I2C_SCL(1);
    I2C_SDA(0);
    I2C_SCL(0);
}

/****
	* @brief	ֹͣ I2C   			  
	* @param   	��		   	
	* @return   ��
	* Sample usage:I2C_Start()
    */
void I2C_Stop()
{
    I2C_SDA(0);
    I2C_SCL(1);
    I2C_SDA(1);
}

/****
	* @brief	I2C ��������    			  
	* @param   	Byte    ���͵����� 
	* @return   ��  	
	* Sample usage:I2C_Write_Byte(0x01);
    */
void I2C_Write_Byte(uint8_t Byte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        I2C_SDA(Byte & (0x80 >> i));
        I2C_SCL(1);
        I2C_SCL(0);
    }
}

/****
	* @brief	I2C ��������    			  
	* @param   	��
	* @return   Byte    ���յ�����  	
	* Sample usage:I2C_Receive_Byte();
    */
uint8_t I2C_Receive_Byte()
{
    uint8_t i = 0;
    uint8_t Byte = 0x00;
    I2C_SDA(1);
    for(i = 0; i < 8; i++)
    {
        I2C_SCL(1);
		if(I2C_R_SDA()){Byte|=(0x80>>i);}
		I2C_SCL(0);
    }
    return Byte;
}

/****
	* @brief	I2C ����Ӧ��   			  
	* @param   	Ack     ���͵�Ӧ��   0 / 1
	* @return   �� 	
	* Sample usage:I2C_SendAck(1);
    */
void I2C_Send_Ack(uint8_t Ack)
{
    I2C_SDA(Ack);
    I2C_SCL(1);
    I2C_SCL(0);
}

/****
	* @brief	I2C ����Ӧ��   			  
	* @param   	��
	* @return   Ack 	���յ�Ӧ��  0 / 1
	* Sample usage:I2C_Receive_Ack();
    */
uint8_t I2C_Receive_Ack()
{
    uint8_t Ack = 0;
    I2C_SDA(1);
    I2C_SCL(1);
    Ack = I2C_R_SDA();
    I2C_SCL(0);
    return Ack;
}
