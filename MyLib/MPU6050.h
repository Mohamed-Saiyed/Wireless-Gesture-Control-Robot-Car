#ifndef MPU6050
#define MPU6050

#include <MyLib/I2C.h>
#define ACCEL_XOUT_H 0x3B
#define CONFIG 0x1A
#define PWR_MGMT_1 0x6B
#define SMPLRT_DIV 0x19
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B

int Ax ,Ay , Az , T , Gx ,Gy , Gz;
void Check(uint8_t status)
{
	if (Check_Status() != status)
	{
		PORTA |=(1<<PA0);
		
		//PORTA &=~(1<<PA0);
	}
}
void MPU_Init(uint8_t freq,uint8_t g)
{
	I2C_Init(freq);
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	I2C_Write(SMPLRT_DIV);
	Check(I2C_MT_DATA_ACK);
	I2C_Write(0x07);
	Check(I2C_MT_DATA_ACK);
	I2C_Stop();
	
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	Check(I2C_MT_SLA_W_ACK);
	I2C_Write(PWR_MGMT_1);
	Check(I2C_MT_DATA_ACK);
	I2C_Write(0x01);
	Check(I2C_MT_DATA_ACK);
	I2C_Stop();
	
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	Check(I2C_MT_SLA_W_ACK);
	I2C_Write(CONFIG);
	Check(I2C_MT_DATA_ACK);
	I2C_Write(0x00);
	Check(I2C_MT_DATA_ACK);
	I2C_Stop();
	
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	Check(I2C_MT_SLA_W_ACK);
	I2C_Write(ACCEL_CONFIG);
	Check(I2C_MT_DATA_ACK);
	if(g==2)I2C_Write(0x00);
	if (g==4)I2C_Write(0x08);
	if(g==8)I2C_Write(0x10);
	if(g==16)I2C_Write(0x18);
	Check(I2C_MT_DATA_ACK);
	I2C_Stop();
	
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	Check(I2C_MT_SLA_W_ACK);
	I2C_Write(GYRO_CONFIG);
	Check(I2C_MT_DATA_ACK);
	I2C_Write(0x18);
	Check(I2C_MT_DATA_ACK);
	I2C_Stop();
	
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	Check(I2C_MT_SLA_W_ACK);
	I2C_Write(0x38);
	Check(I2C_MT_DATA_ACK);
	I2C_Write(0x01);
	Check(I2C_MT_DATA_ACK);
	I2C_Stop();
	
}

void MPU_X_Y_Read()
{
	
	I2C_Start();
	Check(I2C_START);
	I2C_Write(0xD0);
	Check(I2C_MT_SLA_W_ACK);
	I2C_Write(ACCEL_XOUT_H);
	Check(I2C_MT_DATA_ACK);
	
	I2C_Start();
	Check(I2C_REPEAT_START);
	I2C_Write(0xD1);
	Check(I2C_MT_SLA_R_ACK);
	Ax = ((int)I2C_Read_With_ACK()<<8)  | (int)I2C_Read_With_ACK();
	Ay = ((int)I2C_Read_With_ACK()<<8)  | (int)I2C_Read_With_ACK();
	Az = (((int)I2C_Read_With_ACK()<<8) | (int)I2C_Read_With_ACK());
	T  = (((int)I2C_Read_With_ACK()<<8) | (int)I2C_Read_With_ACK());
	Gx = (((int)I2C_Read_With_ACK()<<8) | (int)I2C_Read_With_ACK());
	Gy = (((int)I2C_Read_With_ACK()<<8) | (int)I2C_Read_With_ACK());
	Gz = (((int)I2C_Read_With_ACK()<<8) | (int)I2C_Read_With_NACK());
	I2C_Stop();
}

#endif