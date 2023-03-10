#include "WS2812.h"

float RGB_R,RGB_G,RGB_B;//HSVתRGB����ɫ
#define LedNum 		14   //�Ƶĸ���
uint8_t buf_R[LedNum] = {0};//��ɫ����
uint8_t buf_G[LedNum] = {0};
uint8_t buf_B[LedNum] = {0};

/****
	* @brief	WS2812��������
	* @param   	��
	* @return   ��	
	* Sample usage:WS2812_GPIO_Config();
    */
void WS2812_GPIO_Config()
{
	P5M1 &= 0xF7;
	P5M0 |= ~0xF7;		//P53 �������
}

/****
	* @brief	WS2812д0
	* @param   	��
	* @return   ��	
	* Sample usage:WS2812_RGB_Write1();
    */
void WS2812_RGB_Write0()
{
	WS2812_PIN = 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	WS2812_PIN = 0;
}

/****
	* @brief	WS2812д1
	* @param   	��
	* @return   ��	
	* Sample usage:WS2812_RGB_Write1();
    */
void WS2812_RGB_Write1()
{
	WS2812_PIN = 1;;
	_nop_(); _nop_(); _nop_(); _nop_(); 
    _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); 
	WS2812_PIN = 0;;
}

/****
	* @brief	WS2812��λ
	* @param   	��
	* @return   ��	
	* Sample usage:WS2812_RGB_Reset();
    */
void WS2812_RGB_Reset()
{
	unsigned long i;
	WS2812_PIN = 0;;
	_nop_();_nop_();_nop_();
	i = 478UL;
	while (i) i--;
}

/****
	* @brief	д��һ���ֽ�
	* @param   	Byte	д����ֽ�
	* @return   ��	
	* Sample usage:WS2812_RGB_Write_Byte(100);
    */
void WS2812_RGB_Write_Byte(uint8_t Byte)
{
	uint8_t i;

	for(i = 0; i < 8; i++)
	{
		if(Byte & 0x80)
		{
			WS2812_RGB_Write1();
		}
		else
		{
			WS2812_RGB_Write0();
		}
		Byte <<= 1;
	}
}

/****
	* @brief	������ɫ
	* @param   	Green	Green��ɫ 
	* @param   	Red		Red��ɫ 
	* @param   	Blue	Blue��ɫ 
	* @return   ��	
	* Sample usage:WS2812_RGB_SetColor(100,220,100);
    */
void WS2812_RGB_SetColor(uint8_t Green,uint8_t Red,uint8_t Blue)
{
	WS2812_RGB_Write_Byte(Green);
	WS2812_RGB_Write_Byte(Red);
	WS2812_RGB_Write_Byte(Blue);
}

/****
	* @brief	��ɫ
	* @param   	Num		����
	* @return   ��	
	* Sample usage:WS2812_RGB_White(100);
    */
void WS2812_RGB_White(uint8_t Num)
{
	 uint8_t i;
	for(i = 0; i < Num; i++)
	{
		WS2812_RGB_SetColor(0xFF, 0xFF, 0xFF);
	}
}

/****
	* @brief	��ɫ
	* @param   	Num		����
	* @return   ��	
	* Sample usage:WS2812_RGB_Red(100);
    */
void WS2812_RGB_Red(uint8_t Num)
{
	 uint8_t i;
	for(i = 0; i < Num; i++)
	{
		WS2812_RGB_SetColor(0, 0xFF, 0);
	}
}

/****
	* @brief	��ɫ
	* @param   	Num		����
	* @return   ��	
	* Sample usage:WS2812_RGB_Green(100);
    */
void WS2812_RGB_Green(uint8_t Num)
{
	 uint8_t i;
	for(i = 0; i < Num; i++)
	{
		WS2812_RGB_SetColor(0xFF, 0, 0);
	}
}

/****
	* @brief	��ɫ
	* @param   	Num		����
	* @return   ��	
	* Sample usage:WS2812_RGB_Blue(100);
    */
void WS2812_RGB_Blue(uint8_t Num)
{
	 uint8_t i;
	for(i = 0; i < Num; i++)
	{
		WS2812_RGB_SetColor(0, 0, 0xFF);
	}
}

/****
	* @brief	�����ɫ
	* @param   	Num		����
	* @return   ��	
	* Sample usage:RGB_RandomColor(100);
    */
void RGB_RandomColor(uint8_t Num)
{
	uint8_t i;
	uint8_t xdata Red,Green,Blue; 
	//srand((int)time(0)); // �����������
	Red = rand() % 255; //�����������һ���ֽڵķ�Χ��
	Green = rand() % 255;
	Blue = rand() % 255;
	for(i = 0; i < Num; i++)
	{
		WS2812_RGB_SetColor(Red,Green,Blue); 
	}
}

/****
	* @brief	RGB��ɫ
	* @param   	R		R��ɫ 
	* @param   	G		G��ɫ 
	* @param   	B		B��ɫ 
	* @return   RGB��ɫ 	
	* Sample usage:Color(100,220,100);
    */
unsigned long Color(unsigned char R, unsigned char G, unsigned char B)
{
	return ((unsigned long)R << 16) | ((unsigned long)G <<  8) | B;
}

/****
	* @brief	��ɫ����24λ����ַ� 
	* @param   	num		RGB����
	* @param   	c		RGB��ɫ 
	* @return   �� 	
	* Sample usage:Wheel(100);
    */
void SetPixelColor(uint8_t num,uint32_t c)
{
	uint8_t i;
	for(i=0;i<LedNum;i++)
	{
		buf_R[num] = (uint8_t)(c>>16);
		buf_G[num] = (uint8_t)(c>>8);
		buf_B[num] = (uint8_t)(c);
	}
	for(i=0;i<LedNum;i++)
	{
		WS2812_RGB_SetColor(buf_G[i],buf_R[i],buf_B[i]);
	}
}

/****
	* @brief	��ɫ�㷨  
	* @param   	WheelPos	λ��
	* @return   RGB��ɫ 	
	* Sample usage:Wheel(100);
    */
uint32_t Wheel(uint8_t WheelPos)
{
	WheelPos = 255 - WheelPos;
	if(WheelPos < 85) 
	{
		return Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if(WheelPos < 170) 
	{

		WheelPos -= 85;
		return Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

/****
	* @brief	�ʺ�  
	* @param   	wait	��ʱʱ��
	* @return   �� 	
	* Sample usage:Rainbow(100);
    */
void Rainbow(uint16_t wait)
{
	uint16_t i, j;
 
	for(j=0; j<256; j++) 
	{
		for(i=0; i<LedNum; i++)
		{
			SetPixelColor(i, Wheel((i+j) & 255));
		}
		WS2812_RGB_Reset();
		Delay_ms(wait);
	}
}

/****
	* @brief	�ʺ���ȷֲ�  
	* @param   	wait	��ʱʱ��
	* @return   �� 	
	* Sample usage:RainbowCycle(100);
    */
void RainbowCycle(uint16_t wait) 
{
	uint16_t i, j;
 
	for(j=0;j<256*5;j++) 	//   ������������ɫ��5��ѭ��	
	{ 
		for(i=0;i<LedNum;i++) 
		{
			SetPixelColor(i, Wheel(((i * 256 / LedNum) + j) & 255));
		}
		WS2812_RGB_Reset();
		Delay_ms(wait);
	}
}

/****
	* @brief	������  
	* @param   	c		RGB��ɫ
	* @param   	wait	��ʱʱ��
	* @return   �� 	
	* Sample usage:TheaterChase(Color(0,0,255),100);
    */
void TheaterChase(uint32_t c, uint16_t wait) 
{
	int16_t j,q;
	uint16_t i;
	for (j=0; j<255*5; j++) 			// ��10��ѭ��
	{  
		for (q=0; q < 3; q++) 
		{
			for (i=0; i<LedNum; i=i+3)
			{
				SetPixelColor(i+q, c);    // ��ÿһ������������
			}
			WS2812_RGB_Reset();
			Delay_ms(wait);
 
			for (i=0; i<LedNum; i=i+3) 
			{
				SetPixelColor(i+q, 0);        //t  ��ÿһ�����������عص�
			}
			WS2812_RGB_Reset();
		}
	}
}

/****
	* @brief	���вʺ�Ч����Ϸ��ʽ���е�	  
	* @param   	wait	��ʱʱ��
	* @return   �� 	
	* Sample usage:TheaterChaseRainbow();
    */
void TheaterChaseRainbow(uint16_t wait) 
{
	int16_t j,q;
	uint16_t i;
	for (j=0; j < 256; j++)		 //  ��������ѭ������256ɫ
	{     
		for (q=0; q < 3; q++)
		{
			for (i=0; i < LedNum; i=i+3) 
			{
				SetPixelColor(i+q, Wheel( (i+j) % 255));    //��ÿһ������������
			}
			WS2812_RGB_Reset();
			Delay_ms(wait);
	 
			for (i=0; i < LedNum; i=i+3)
			{
				SetPixelColor(i+q, 0);        //��ÿһ�����������عص�
			}
		}
	}
}

//RGBת����HSV���㷨:
void hsv_to_rgb(int h,int s,int v,float *R,float *G,float *B)
{
    float C = 0,X = 0,Y = 0,Z = 0;
    int i=0;
    float H=(float)(h);
    float S=(float)(s)/100.0;
    float V=(float)(v)/100.0;
    if(S == 0)
        *R = *G = *B = V;
    else
    {
        H = H/60;
        i = (int)H;
        C = H - i;
 
        X = V * (1 - S);
        Y = V * (1 - S*C);
        Z = V * (1 - S*(1-C));
        switch(i)
				{
            case 0 : *R = V; *G = Z; *B = X; break;
            case 1 : *R = Y; *G = V; *B = X; break;
            case 2 : *R = X; *G = V; *B = Z; break;
            case 3 : *R = X; *G = Y; *B = V; break;
            case 4 : *R = Z; *G = X; *B = V; break;
            case 5 : *R = V; *G = X; *B = Y; break;
        }
    }
    *R = *R *255;
    *G = *G *255;
    *B = *B *255;
}

