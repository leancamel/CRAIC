#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "pid.h"

typedef union
{
	float float_data;
	uint8_t byte_data[4];
}Float_Byte;

typedef struct
{
	Float_Byte vx_set;
	Float_Byte turn_angle;
	float speed_L;
	float speed_R;
	float vx[2];
	float wz[2];
	float angle;
	PidTypeDef vx_PID;
}Car_Structure_Def;

extern Car_Structure_Def Car_Structure;

void Motor_Init(void);
void Motor_Drive(void);
void Get_Car_Speed(void);

#endif
