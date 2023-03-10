#include "ROCKER.h"

uint16_t Rocker_Value_BUFF[NUMCHANNEL] = { 0 };
uint8_t L_DIR,R_DIR;

/****
		* @brief   ҡ�� GPIO ����			  
		* @param   ��
		* @return  ��    	
		* Sample usage:ROCKER_GPIO_Config(); 
		* note
    */
static void ROCKER_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    //����GPIOʱ��
    ROCKER_ADCLx_GPIO_APBxClockCMD(ROCKER_ADCLx_GPIO_CLK | ROCKER_ADCRx_GPIO_CLK,ENABLE);

    //GPIO���� ����
    GPIO_InitStruct.GPIO_Pin = ROCKER_ADCL1x_GPIO_PIN | ROCKER_ADCL2x_GPIO_PIN | ROCKER_ADCR3x_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;  			//ģ������
    GPIO_Init(ROCKER_ADCLx_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = ROCKER_ADCR1x_GPIO_PIN | ROCKER_ADCR2x_GPIO_PIN ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;  			//ģ������
    GPIO_Init(ROCKER_ADCRx_GPIO_PORT,&GPIO_InitStruct);
}

/*DMA����
typedef struct
{
  uint32_t DMA_PeripheralBaseAddr;      //�����ַ
  uint32_t DMA_MemoryBaseAddr;          //�洢����ַ
  uint32_t DMA_DIR;                     //���䷽��
  uint32_t DMA_BufferSize;              //������Ŀ
  uint32_t DMA_PeripheralInc;           //�����ַ����ģʽ
  uint32_t DMA_MemoryInc;               //�洢����ַ����ģʽ     
  uint32_t DMA_PeripheralDataSize;      //�������ݿ��
  uint32_t DMA_MemoryDataSize;          //�洢�����ݿ��
  uint32_t DMA_Mode;                    //ģʽѡ��
  uint32_t DMA_Priority;                //ͨ�����ȼ�
  uint32_t DMA_M2M;                     //�洢�����洢��ģʽ
}DMA_InitTypeDef;
*/

/****
	* @brief    ҡ�� DMA ���� 			  
	* @param   	��
	* @return   ��    	
	* Sample usage:ROCKER_DMA_Config(); 
    */
static void ROCKER_DMA_Config()
{
    DMA_InitTypeDef DMA_InitStruct;
    DMA_DeInit(ROCKER_DMAX_Channel);
    //����DMAʱ��
    ROCKER_DMAx_APBxClockCMD(ROCKER_DMAx_CLK,ENABLE);
    //��������
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&(ROCKER_ADCx->DR));     //�����ַ
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Rocker_Value_BUFF;            //�洢����ַ
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                 //������Ϊ���ݴ������Դ          
	DMA_InitStruct.DMA_BufferSize = NUMCHANNEL;                     //������Ŀ
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //�����ַ�Ĵ�������      
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;            //�ڴ��ַ�Ĵ�������          
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //���ݿ��Ϊ 16 λ 
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            //���ݿ��Ϊ 16 λ    
	DMA_InitStruct.DMA_Mode =  DMA_Mode_Circular;           //ѭ������ģʽ               
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;      	//�����ȼ�          
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;               //���赽�ڴ�;   
    DMA_Init(ROCKER_DMAX_Channel,&DMA_InitStruct);

    //����DMA
    DMA_Cmd(ROCKER_DMAX_Channel,ENABLE);
}

/****
	* @brief    ADC ���� 			  
	* @param   	��
	* @return   ��    	
	* Sample usage:ROCKER_ADCx_Config(); 
    */
static void ROCKER_ADCx_Config()
{
    ADC_InitTypeDef ADC_InitStruct;
    //����ADCʱ��
    ROCKER_ADCx_APBxClockCMD(ROCKER_ADCx_CLK,ENABLE);
    //��������
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;         //����ת��;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //�Ҷ���
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   //ת��������������ⲿ��������
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //����ģʽ
    ADC_InitStruct.ADC_NbrOfChannel = NUMCHANNEL;           //���й���ת���� ADC ͨ������Ŀ
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;               //��ͨ��
    ADC_Init(ROCKER_ADCx,&ADC_InitStruct);

    //���� ADC ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);       //8��Ƶ ADCCLK=72MHz/8=9MHz     108MHz/8 = 13

    //����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel1,1,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel2,2,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel3,3,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel4,4,ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ROCKER_ADCx,ROCKER_ADCx_Channel5,5,ADC_SampleTime_239Cycles5);

    //ʹ��ADC_DMA
    ADC_DMACmd(ROCKER_ADCx,ENABLE);

    //����ADC
    ADC_Cmd(ROCKER_ADCx,ENABLE);
    Delay_us(30);

    //У׼
    ADC_ResetCalibration(ROCKER_ADCx);                  //ADC��λУ׼
    while(ADC_GetResetCalibrationStatus(ROCKER_ADCx));  //�ȴ���λУ׼���
    ADC_StartCalibration(ROCKER_ADCx);                  //ADC��ʼУ׼  
    while(ADC_GetCalibrationStatus(ROCKER_ADCx));       //�ȴ�У׼���

    //ʹ��ָ���� ADC �����ת����������
    ADC_SoftwareStartConvCmd(ROCKER_ADCx,ENABLE);
}

/****
	* @brief    ADC ��ʼ��		  
	* @param   	��
	* @return   ��    	
	* Sample usage:ROCKER_ADCx_Config(); 
    */
void ROCKER_Init()
{
    ROCKER_GPIO_Config();
	ROCKER_DMA_Config();
	ROCKER_ADCx_Config(); 
}

/****
	* @brief    ADC ���ݴ���		  
	* @param   	Value   ���������
	* @return   ��    	
	* Sample usage:ROCKER_COORDINATE(&Value);
    */
void ROCKER_COORDINATE(ROCKER_Value *Value)
{
    Value->ROCKER_RY_Value =    (Rocker_Value_BUFF[2] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;
    Value->ROCKER_RX_Value =    (Rocker_Value_BUFF[3] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;
    Value->ROCKER_LY_Value =    (Rocker_Value_BUFF[0] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;
    Value->ROCKER_LX_Value =    (Rocker_Value_BUFF[1] - Y_ADC_MIN) * (Y_COORDINATE_MAX - Y_COORDINATE_MIN) / 
                                (ADC_RESOLUTION - Y_ADC_MIN) + Y_COORDINATE_MIN;  

    float voltage = (float)(Rocker_Value_BUFF[4] * 3.3 / ADC_RESOLUTION);       // �����ѹֵ
    Value->Electricity = voltage * 3 / BATTERY_RATED_VOLTAGE*100;             //�������  ����(R21(R1+R2))1/3��ѹ                                                          
}

void ROCKER_Driction()
{
    ROCKER_Value Value;
    ROCKER_COORDINATE(&Value);
    if(0 <= Value.ROCKER_RX_Value && Value.ROCKER_RX_Value <= 25) R_DIR = 0;    //��ҡ����
    if(75 <= Value.ROCKER_RX_Value && Value.ROCKER_RX_Value < 100) R_DIR = 1;   //��ҡ����
    if(0 <= Value.ROCKER_RY_Value && Value.ROCKER_RY_Value <= 25) R_DIR = 2;    //��ҡ��s
    if(75 <= Value.ROCKER_RY_Value && Value.ROCKER_RY_Value < 100) R_DIR = 3;    //��ҡ��x
    if(25 < Value.ROCKER_RY_Value && Value.ROCKER_RY_Value < 75) R_DIR = 4;      //��ҡ���м�

    if(0 <= Value.ROCKER_LX_Value && Value.ROCKER_LX_Value <= 25) L_DIR = 0;    //��ҡ����
    if(75 <= Value.ROCKER_LX_Value && Value.ROCKER_LX_Value < 100) L_DIR = 1;   //��ҡ����
    if(0 <= Value.ROCKER_LY_Value && Value.ROCKER_LY_Value <= 25) L_DIR = 2;    //��ҡ��s
    if(75 <= Value.ROCKER_LY_Value && Value.ROCKER_LY_Value < 100) L_DIR = 3;   //��ҡ��x
    if(25 < Value.ROCKER_LY_Value && Value.ROCKER_LY_Value < 75) L_DIR = 4;      //��ҡ���м�
}

/****
	* @brief    ADC ���ݷ���	  
	* @param   	��
	* @return   ��    	
	* Sample usage:ROCKER_DirSend(); 
    */
void ROCKERData_Send()
{
    uint8_t ROCKER_Buff[12] = "0";
    ROCKER_Value Value;
    ROCKER_COORDINATE(&Value);
    ROCKER_Buff[0] = 'R';
    ROCKER_Buff[1] = 'Y';
    ROCKER_Buff[2] = Value.ROCKER_RY_Value;
    ROCKER_Buff[3] = 'X';
    ROCKER_Buff[4] = Value.ROCKER_RX_Value;
    ROCKER_Buff[5] = 'L';
    ROCKER_Buff[6] = 'Y';
    ROCKER_Buff[7] = Value.ROCKER_LY_Value;
    ROCKER_Buff[8] = 'X';
    ROCKER_Buff[9] = Value.ROCKER_LX_Value;
    ROCKER_Buff[10] = '0';
    NRF24L01_TX_Mode();
	if(NRF24L01_TxPacket(ROCKER_Buff) == NRF24L01_TX_DS)
	{
		LED1_TOGGLE;
	}
	else
	{										   	
 		printf("ROCKER Send failed !\n");	
	}
}

