#include "TIME.h"

/****
	* @brief    ��ʱ���ж� ����			  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMEx_NVIC_Config(); 
    */
static void TIMEx_NVIC_Config()
{
    NVIC_InitTypeDef NVIC_InitStruct;
    //�жϷ�������
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //��������
    NVIC_InitStruct.NVIC_IRQChannel = TIMEx_IRQChannel;      //�ж�ͨ��
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;             //�ж�ͨ��ʹ��
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;          //�����ȼ�
    NVIC_Init(&NVIC_InitStruct);
}

/****
	* @brief    ��ʱ�� ����			  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMEx_Config(); 
    */
static void TIMEx_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    //������ʱ��ʱ��
    TIMEx_APBxClockCmd(TIMEx_CLK,ENABLE);
    //ѡ��Ϊ�ڲ�ʱ�ӣ�Ĭ���ڲ�ʱ�ӣ�
    TIM_InternalClockConfig(TIME_x);
    //��������
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        //ʱ�ӷ�Ƶ 1��Ƶ
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    //����ģʽ     ���ϼ���
    TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;                   //ARR   �Զ���װ
    TIM_TimeBaseInitStruct.TIM_Prescaler = 540 - 1;                 //PSC   Ԥ��Ƶ
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;               //�ظ�������
    TIM_TimeBaseInit(TIME_x,&TIM_TimeBaseInitStruct);

    TIM_ClearFlag(TIME_x,TIM_IT_Update);

    TIM_ITConfig(TIME_x,TIM_IT_Update,ENABLE);      //��ʱ��ʹ�ܸ����ж�

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIME_x,ENABLE); 
}

/****
	* @brief    ��ʱ�� ��ʼ��		  
	* @param   	��
	* @return   ��    	
	* Sample usage:TIMEx_Init(); 
    */
void TIMEx_Init()
{
    TIMEx_Config();
    TIMEx_NVIC_Config();
}


