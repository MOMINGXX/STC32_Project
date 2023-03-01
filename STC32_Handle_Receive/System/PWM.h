#ifndef __PWM_H__
#define __PWM_H__

#include <STC32G.H>

#define PWMB_Period			(2000 - 1)
#define PWMB_Prescaler		(240 - 1)

void PWMB_Config();
void PWMB_SetCompare1(uint16_t Duty);
void PWMB_SetCompare2(uint16_t Duty);
void PWMA_SetCompare4(uint16_t Duty);

#endif /*__PWM_H__*/