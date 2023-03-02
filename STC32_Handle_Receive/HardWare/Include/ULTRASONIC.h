#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include <STC32G.H>

sbit Trig = P0^2;
sbit Echo = P0^3;

void Ultrasonic_Init();
uint16_t Ultrasonic_GetDistance();

#endif /*__ULTRASONIC_H__*/