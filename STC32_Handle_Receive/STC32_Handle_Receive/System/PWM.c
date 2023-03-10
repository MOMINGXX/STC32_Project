#include "PWM.h"

/****
	* @brief	PWMB����	  ���PWM
	* @param   	��
	* @return   �� 	
	* Sample usage:PWMB_Config();
    */
void PWMB_Config()
{
	PWMB_PS = 0x00;			//ѡ��ͨ��5 P20   ͨ��6 P21
	
	PWMB_CCER1 = 0x00;		//�Ƚ�ʹ�ܼĴ���		����
	PWMB_CCMR1 = 0x60;		//�Ƚ�ģʽ�Ĵ���		PWMģʽ1 ���ϼ���
	PWMB_CCMR2 = 0x60;		//�Ƚ�ģʽ�Ĵ���		PWMģʽ1 ���ϼ���
	PWMB_CCER1 = 0x11;		//�Ƚ�ʹ�ܼĴ���		�����Ƚ���� ����ߵ�ƽ
	
	PWMB_PSCRH = (uint8_t)(PWMB_Prescaler >> 8);	//Ԥ��Ƶ����8λ
	PWMB_PSCRL = (uint8_t)PWMB_Prescaler;			//Ԥ��Ƶ����8λ
	PWMB_ARRH = (uint8_t)(PWMB_Period >> 8);		//�Զ���װ�ؼĴ�����8λ
	PWMB_ARRL = (uint8_t)PWMB_Period	;			//�Զ���װ�ؼĴ�����8λ
	PWMB_CCR5H = 0;		//�ȽϼĴ�����8λ
	PWMB_CCR5L = 0;		//�ȽϼĴ�����8λ
	PWMB_CCR6H = 0;		//�ȽϼĴ�����8λ
	PWMB_CCR6L = 0;		//�ȽϼĴ�����8λ
	
	PWMB_ENO = 0x05;		//���ʹ�ܼĴ���		ʹ��PWM5 PWM6���
	PWMB_BKR = 0x80;		//�����ʹ��
	PWMB_CR1 = 0x01;		//���ƼĴ��� ʹ�ܼ���
}

/****
	* @brief	PWMA����	���PWM	  
	* @param   	��
	* @return   �� 	
	* Sample usage:PWMA_Config();
    */
void PWMA_Config()
{
	PWMA_PS = 0x00;			//ѡ��ͨ��4 P16 P17
	
	PWMA_CCER2 = 0x00;		//�Ƚ�ʹ�ܼĴ���		����
	PWMA_CCMR4 = 0x60;		//�Ƚ�ģʽ�Ĵ���		PWMģʽ1 ���ϼ���
	PWMA_CCER2 = 0x40;		//�Ƚ�ʹ�ܼĴ���		�����Ƚ���� ����ߵ�ƽ
	
	PWMA_PSCRH = (uint8_t)(PWMA_Prescaler >> 8);	//Ԥ��Ƶ����8λ
	PWMA_PSCRL = (uint8_t)PWMA_Prescaler;			//Ԥ��Ƶ����8λ
	PWMA_ARRH = (uint8_t)(PWMA_Period >> 8);		//�Զ���װ�ؼĴ�����8λ
	PWMA_ARRL = (uint8_t)PWMA_Period	;			//�Զ���װ�ؼĴ�����8λ
	PWMA_CCR4H = 0;		//�ȽϼĴ�����8λ
	PWMA_CCR4L = 0;		//�ȽϼĴ�����8λ
	
	PWMA_ENO = 0x80;		//���ʹ�ܼĴ���		ʹ��PWM5 PWM6���
	PWMA_BKR = 0x80;		//�����ʹ��
	PWMA_CR1 = 0x01;		//���ƼĴ��� ʹ�ܼ���
}

/****
	* @brief	PWMB ͨ��5 ռ�ձ�����
	* @param   	Duty	���õ�ռ�ձ� 
	* @return   �� 	
	* Sample usage:PWMB_SetCompare5(100);
    */
void PWMB_SetCompare5(uint16_t Duty)
{
	PWMB_CCR5H = (uint8_t)(Duty >> 8);	//�ȽϼĴ�����8λ	ռ�ձ�
	PWMB_CCR5L = (uint8_t)Duty;			//�ȽϼĴ�����8λ
}

/****
	* @brief	PWMB ͨ��6 ռ�ձ�����
	* @param   	Duty	���õ�ռ�ձ� 
	* @return   �� 	
	* Sample usage:PWMB_SetCompare5(100);
    */
void PWMB_SetCompare6(uint16_t Duty)
{
	PWMB_CCR6H = (uint8_t)(Duty >> 8);	//�ȽϼĴ�����8λ	ռ�ձ�
	PWMB_CCR6L = (uint8_t)Duty;			//�ȽϼĴ�����8λ
}

/****
	* @brief	PWMA ͨ��4 ռ�ձ�����
	* @param   	Duty	���õ�ռ�ձ� 
	* @return   �� 	
	* Sample usage:PWMA_SetCompare5(100);
    */
void PWMA_SetCompare4(uint16_t Duty)
{
	PWMA_CCR4H = (uint8_t)(Duty >> 8);	//�ȽϼĴ�����8λ	ռ�ձ�
	PWMA_CCR4L = (uint8_t)Duty;			//�ȽϼĴ�����8λ
}