#include "MPU6050.h"

/****
	* @brief    ���ᴫ���� д����			  
	* @param   	RegAddress  �Ĵ�����ַ
    * @param   	Data        д�������
	* @return   ��    	
	* Sample usage:MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
    */
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
    IIC_Start();
    IIC_SendByte(MPU6050_ADDR);
	IIC_ReceiveAck();
    IIC_SendByte(RegAddress);
    IIC_ReceiveAck();
    IIC_SendByte(Data);
    IIC_ReceiveAck();
    IIC_Stop();
}

/****
	* @brief    ���ᴫ���� ��ȡ����		  
	* @param   	RegAddress  �Ĵ�����ַ
	* @return   Data        ��ȡ������   	
	* Sample usage:MPU6050_ReadReg(MPU6050_PWR_MGMT_1);
    */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data = 0;
    IIC_Start();
    IIC_SendByte(MPU6050_ADDR);
	IIC_ReceiveAck();
    IIC_SendByte(RegAddress);
    IIC_ReceiveAck();

    IIC_Start();
    IIC_SendByte(MPU6050_ADDR | 0x01);
    IIC_ReceiveAck();
    Data = IIC_ReceiveByte();
    IIC_SendAck(1);
    IIC_Stop();
    return Data;    
}

/****
	* @brief    ���ᴫ���� ��ʼ��		  
	* @param   	��
	* @return   ��	
	* Sample usage:MPU6050_Init();
    */
void MPU6050_Init()
{
    IIC_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);		//��Դ����Ĵ���1  �������״̬ ѡ��X��������ʱ��
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);		//��Դ����Ĵ���2  6���������
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x07);		//�����ʷ�Ƶ       ������125hz
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);			//��ͨ�˲�Ƶ��
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);		//������        2000��/��  16.4
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);	//���ٶȼ�     16g  2048
}

/****
	* @brief    ���ᴫ���� ID		  
	* @param   	��
	* @return   ID��          0X68
	* Sample usage:MPU6050_GetID();
    */
uint8_t MPU6050_GetID()
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/****
	* @brief    ���ᴫ���� ��ȡ����		  
	* @param   	Data    �ṹ���ַ
	* @return   ��
	* Sample usage:MPU6050_GetData(&Data);
    */
void MPU6050_GetData(MPU6050_Data *Data)
{
    int16_t Temp;
	Data->ACCEL_XOUT = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8;
    Data->ACCEL_XOUT |= MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L); 

    Data->ACCEL_YOUT = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8;
    Data->ACCEL_YOUT |= MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);

    Data->ACCEL_ZOUT = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8;
    Data->ACCEL_ZOUT |= MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);

    Data->GYRO_XOUT = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8;
    Data->GYRO_XOUT |= MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);

    Data->GYRO_YOUT = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8;
    Data->GYRO_YOUT |= MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);

    Data->GYRO_ZOUT = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8;
    Data->GYRO_ZOUT |= MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);

    Temp = MPU6050_ReadReg(MPU6050_TEMP_OUT_H) << 8;
    Temp |= MPU6050_ReadReg(MPU6050_TEMP_OUT_L);
    Data->Temperature=((double) Temp / 340.0) + 36.53;

}

int g_x=0,g_y=0,g_z=0;						//�����ǽ�������
float a_x=0,a_y=0;							//�ǶȽ�������
float Pitch=0,Roll=0;						//��Ԫ���������ŷ����
float Angle_gx=0,Angle_gy=0,Angle_gz=0;		//�ɽ��ٶȼ���Ľ�����(�Ƕ���)
float Angle_ax=0,Angle_ay=0,Angle_az=0;		//�ɼ��ٶȼ���ļ��ٶ�(������)
void MPU6050_Dispose()
{
	MPU6050_Data Data;
	MPU6050_GetData(&Data);
	Angle_ax = Data.ACCEL_XOUT / 2048.0;
	Angle_ay = Data.ACCEL_YOUT / 2048.0;
	Angle_az = Data.ACCEL_ZOUT / 2048.0;
	
	Angle_gx = Data.ACCEL_XOUT / 16.4;
	Angle_gy = Data.ACCEL_YOUT / 16.4;
	Angle_gz = Data.ACCEL_ZOUT / 16.4;
	
	IMUupdate(Angle_gx*0.0174533f,Angle_gy*0.0174533f,Angle_gz*0.0174533f,Angle_ax,Angle_ay,Angle_az);
}


#define	pi		3.14159265f                           
#define	Kp		0.8f                        
#define	Ki		0.001f                         
#define	halfT	0.004f           

float q0=1,q1=0,q2=0,q3=0;   
float exInt=0,eyInt=0,ezInt=0;  


void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
	float norm;
	float vx, vy, vz;
	float ex, ey, ez;

	norm = sqrt(ax*ax + ay*ay + az*az);	//�Ѽ��ٶȼƵ���ά����ת�ɵ�ά����   
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

		//	�����ǰ���Ԫ������ɡ��������Ҿ����еĵ����е�����Ԫ�ء� 
		//	�������Ҿ����ŷ���ǵĶ��壬��������ϵ������������ת����������ϵ��������������Ԫ��
		//	���������vx vy vz����ʵ���ǵ�ǰ��ŷ���ǣ�����Ԫ�����Ļ����������ϵ�ϣ����������
		//	������λ������
	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 + q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3 ;

	ex = (ay*vz - az*vy) ;
	ey = (az*vx - ax*vz) ;
	ez = (ax*vy - ay*vx) ;

	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;

	q0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	q1 = q1 + ( q0*gx + q2*gz - q3*gy) * halfT;
	q2 = q2 + ( q0*gy - q1*gz + q3*gx) * halfT;
	q3 = q3 + ( q0*gz + q1*gy - q2*gx) * halfT;

	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;

	Pitch= asin(2*(q0*q2 - q1*q3 )) * 57.2957795f; // ����   ����ɶ�
	Roll = asin(2*(q0*q1 + q2*q3 )) * 57.2957795f; // ���
}

int Map(int val,int in_min,int in_max,int out_min,int out_max)
{
	return (int)(val-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

void MPU6050_SendData()
{
	uint8_t MPU6050_Buff[20] = "0";
	int Map_pitch=0,Map_roll=0;//ӳ����ƫ����
	Map_pitch=Map((int)Pitch,-90,90,0,100);
	Map_roll=Map((int)Roll,-90,90,0,100);
    MPU6050_Buff[0] = 'G';
	MPU6050_Buff[1] = 'R';
	MPU6050_Buff[2] = 'P';
    MPU6050_Buff[3] = Map_pitch;
    MPU6050_Buff[4] = 'R';
	MPU6050_Buff[5] = Map_roll;
    MPU6050_Buff[6] = '0';

    NRF24L01_TX_Mode();
	if(NRF24L01_TxPacket(MPU6050_Buff) == NRF24L01_TX_DS)
	{
		LED1_TOGGLE;
	}
	else
	{										   	
 		printf("ROCKER Send failed !\n");	
	}
}