#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#include "stm32f10x.h"                  // Device header
#include "SOFT_SPI.h"
#include "USART.h"
#include "Delay.h"

/* ����������Ҫ��ȫһ�²��ܹ�ͨ�� */
#define NRF24L01_TX_ADR_WIDTH 	   5  	//�����ַ���
#define NRF24L01_TX_PLOAD_WIDTH    20   //��������ͨ����Ч���ݿ��0~32Byte 

#define NRF24L01_RX_ADR_WIDTH      5
#define NRF24L01_RX_PLOAD_WIDTH    20

#define NRF24L01_CHANAL            25	//Ƶ��ѡ�� 

#define NRF24L01_R_REGISTER        0x00    // ���Ĵ�����5λ�洢��ӳ���ַ
#define NRF24L01_W_REGISTER        0x20    // д�Ĵ�����5λ�洢��ӳ���ַ�������ڶϵ�����ģʽ��ִ��
#define NRF24L01_R_RX_PAYLOAD      0x61    // ��ȡRX���ء�1-32���ֽڡ���������ʼ�մ��ֽ�0��ʼ����Ч�غɽ��ڶ�ȡ���FIFO��ɾ���� ����RXģʽ
#define NRF24L01_W_TX_PAYLOAD      0xA0    // д��TX���ء�1-32�ֽڡ�д����ʼ�մ��ֽ�0��ʼ������TXģʽ
#define NRF24L01_FLUSH_TX          0xE1    // ˢ��TX FIFO������TXģʽ
#define NRF24L01_FLUSH_RX          0xE2    // ˢ��RX FIFO������RXģʽ���ڴ���ȷ���ڼ䲻Ӧִ�У�ȷ�ϰ�������ɣ���
#define NRF24L01_REUSE_TX_PL       0xE3    // ����PTX�豸����������͵���Ч���ء� ֻҪCEΪ�ߣ��ͻ��ظ��������ݰ�����ִ��W_TX_PAYLOAD��FLUSH TX֮ǰ��TX��Ч�������ô��ڻ״̬�� �ڰ������ڼ䣬���ü����ͣ��TX��Ч�غ�����
#define NOP                        0xFF    // û�в����� �������ڶ�ȡSTATUS�Ĵ���

#define NRF24L01_CONFIG            0x00    // ���üĴ���
#define NRF24L01_EN_AA             0x01    // ���á��Զ�ȷ�ϡ����ܣ����ô˹�������nRF2401����
#define NRF24L01_EN_RXADDR         0x02    // ����RX��ַ
#define NRF24L01_SETUP_AW          0x03    // ��ַ��ȵ����ã��������ݹܵ�ͨ�ã�
#define NRF24L01_SETUP_RETR        0x04    // �Զ��ش�������
#define NRF24L01_RF_CH             0x05    // ��ƵƵ��
#define NRF24L01_RF_SETUP          0x06    // ��Ƶ���üĴ���
#define NRF24L01_STATUS            0x07    // ״̬�Ĵ�������MOSI������ʩ�ӵ�SPIָ���ֲ��У�STATUS�Ĵ�����MISO�����ϴ����Ƴ���
#define NRF24L01_OBSERVE_TX        0x08    // ����۲�Ĵ���
#define NRF24L01_CD                0x09    // �ز����
#define NRF24L01_RX_ADDR_P0        0x0A    // ���յ�ַ���ݹܵ�0����󳤶�Ϊ5���ֽڡ�
#define NRF24L01_RX_ADDR_P1        0x0B    // ���յ�ַ���ݹܵ�1����󳤶�Ϊ5���ֽڡ�
#define NRF24L01_RX_ADDR_P2        0x0C    // ���յ�ַ���ݹܵ�2��ֻ������ֽڿ������ã���λ�ֽڵ���RX_ADDR_P1[39:8]
#define NRF24L01_RX_ADDR_P3        0x0D    // ���յ�ַ���ݹܵ�3��ֻ������ֽڿ������ã���λ�ֽڵ���RX_ADDR_P1[39:8]
#define NRF24L01_RX_ADDR_P4        0x0E    // ���յ�ַ���ݹܵ�4��ֻ������ֽڿ������ã���λ�ֽڵ���RX_ADDR_P1[39:8]
#define NRF24L01_RX_ADDR_P5        0x0F    // ���յ�ַ���ݹܵ�5��ֻ������ֽڿ������ã���λ�ֽڵ���RX_ADDR_P1[39:8]
#define NRF24L01_TX_ADDR           0x10    // ���͵�ַ��������PTX�豸�����������������ǿ��ShockBurstTM��PTX�豸����RX_ADDR_P0����Ϊ���ڴ˵�ַ�Դ����Զ�ȷ�ϡ�
#define NRF24L01_RX_PW_P0          0x11    // ���ݹܵ�0�е�RX��Ч�����е��ֽ�����1��32���ֽڣ�
#define NRF24L01_RX_PW_P1          0x12    // ���ݹܵ�1�е�RX��Ч�����е��ֽ�����1��32���ֽڣ�
#define NRF24L01_RX_PW_P2          0x13    // ���ݹܵ�2�е�RX��Ч�����е��ֽ�����1��32���ֽڣ�
#define NRF24L01_RX_PW_P3          0x14    // ���ݹܵ�3�е�RX��Ч�����е��ֽ�����1��32���ֽڣ�
#define NRF24L01_RX_PW_P4          0x15    // ���ݹܵ�4�е�RX��Ч�����е��ֽ�����1��32���ֽڣ�
#define NRF24L01_RX_PW_P5          0x16    // ���ݹܵ�1�е�RX��Ч�����е��ֽ�����1��32���ֽڣ�
#define NRF24L01_FIFO_STATUS       0x17    // FIFO״̬�Ĵ���
#define NRF24L01_MAX_RT            0x10    //�ﵽ����ط������жϱ�־λ
#define NRF24L01_TX_DS		       0x20    //��������жϱ�־λ	  
#define NRF24L01_RX_DR		       0x40    //���յ������жϱ�־λ

//SPI
#define NRF24L01_SPIx                       SPI2
#define NRF24L01_SPIx_CLK                   RCC_APB1Periph_SPI2
#define NRF24L01_SPIx_APBxClockCMD          RCC_APB1PeriphClockCmd

//GPIO
#define NRF24L01_GPIO_CLK                   RCC_APB2Periph_GPIOB
#define NRF24L01_GPIO_APBxClockCMD          RCC_APB2PeriphClockCmd

#define NRF24L01_GPIO_PORT                  GPIOB
#define NRF24L01_CE_GPIO_PIN                GPIO_Pin_6
#define NRF24L01_IRQ_GPIO_PIN               GPIO_Pin_8
//#define NRF24L01_CSN_GPIO_PIN               GPIO_Pin_12
//#define NRF24L01_SCK_GPIO_PIN               GPIO_Pin_13
//#define NRF24L01_MISO_GPIO_PIN              GPIO_Pin_14
//#define NRF24L01_MOSI_GPIO_PIN              GPIO_Pin_15

/* extern uint8_t NRF24L01_RX_BUF[NRF24L01_RX_PLOAD_WIDTH];		//�������ݻ���
extern uint8_t NRF24L01_TX_BUF[NRF24L01_TX_PLOAD_WIDTH];		//�������ݻ��� */

void NRF24L01_Init(void);  // GPIO��ʼ��
void NRF24L01_RX_Mode();
void NRF24L01_TX_Mode();
uint8_t NRF24L01_Check();
uint8_t NRF24L01_TxPacket(uint8_t *TxBuff);
uint8_t NRF24L01_RxPacket(uint8_t *RxBuff);
void NRF24L01_Check_detection();

#endif

