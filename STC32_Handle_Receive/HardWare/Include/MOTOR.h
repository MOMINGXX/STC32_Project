#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <STC32G.H>
#include "PWM.h"

//����������ʹ�ܶ�����
sbit L298N_ENA = P2^0;
sbit L298N_ENB = P2^1;

//�������������������
sbit L298N_IN1 = P2^2;
sbit L298N_IN2 = P2^3;
sbit L298N_IN3 = P2^6;
sbit L298N_IN4 = P2^7;

#define Left_moto_go      {L298N_IN1=1,L298N_IN2=0;}  		//������ǰ��
#define Left_moto_back    {L298N_IN1=0,L298N_IN2=1;} 		//��ߵ�����ת
#define Left_moto_Stop    {L298N_IN1=0,L298N_IN2=0;}        //��ߵ��ͣת                     
#define Right_moto_go     {L298N_IN3=1,L298N_IN4=0;}		//�ұߵ����ǰ��
#define Right_moto_back   {L298N_IN3=0,L298N_IN4=1;}		//�ұߵ�������
#define Right_moto_Stop   {L298N_IN3=0,L298N_IN4=0;}      	//�ұߵ��ͣת 

void MOTOR_Init();
void MOTOR_ForWard();
void MOTOR_BackWard();
void MOTOR_TurnLeft();
void MOTOR_Turnright();
void MOTOR_Stop();

#endif /*__MOTOR_H__*/