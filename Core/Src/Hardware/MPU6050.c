#include "MPU6050.h"
#include "MPU6050_Reg.h"
#include "motor.h"

#define MPU6050_ADDRESS		0xD0

int16_t ACCX0,GYROZ0;

void MyI2C_W_SCL(uint8_t BitValue)
{
	if(BitValue)
		HAL_GPIO_WritePin(MPU_SCL_GPIO_Port,MPU_SCL_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(MPU_SCL_GPIO_Port,MPU_SCL_Pin,GPIO_PIN_RESET);
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	if(BitValue)
		HAL_GPIO_WritePin(MPU_SDA_GPIO_Port,MPU_SDA_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(MPU_SDA_GPIO_Port,MPU_SDA_Pin,GPIO_PIN_RESET);
}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = HAL_GPIO_ReadPin(MPU_SDA_GPIO_Port, MPU_SDA_Pin);
	return BitValue;
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;
	MyI2C_W_SDA(1);
	for (i = 0; i < 8; i ++)
	{
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	
	return Data;
}

void MPU6050_Init(void)
{
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x00);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);

	uint8_t DataH, DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	ACCX0 = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	GYROZ0 = (DataH << 8) | DataL;
}

void MPU6050_GetData(void)
{
	Car_Structure.vx[1] = Car_Structure.vx[0];
	Car_Structure.wz[1] = Car_Structure.wz[0];

	uint8_t DataH, DataL;
	int16_t temp_data;

	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	temp_data = (DataH << 8) | DataL;
	temp_data -= ACCX0;
	Car_Structure.vx[0] = (float)temp_data / 16.4f;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	temp_data = (DataH << 8) | DataL;
	temp_data -= GYROZ0;
	Car_Structure.wz[0] = (float)temp_data / 16.4f;
	if(Car_Structure.wz[0] > -0.1f && Car_Structure.wz[0] < 0.1f)
		Car_Structure.wz[0] = 0.0f;
		
	Car_Structure.angle += (Car_Structure.wz[0] + Car_Structure.wz[1]) * 0.001f / 2.0f;
}
