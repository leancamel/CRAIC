#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "pid.h"

#define turn_pwm_0 700

typedef union
{
	float float_data;
	uint8_t byte_data[4];
}Float_Byte;

typedef struct
{
	Float_Byte vx_set;
	uint16_t turn_pwm;
	float speed_L;
	float speed_R;
	float vx[2];
	float wz[2];
	float angle;
	PidTypeDef vx_PID;
	uint8_t motor_on;
	uint16_t key_time;
	uint16_t motor_time;
}Car_Structure_Def;

extern Car_Structure_Def Car_Structure;

void Motor_Init(void);
void Motor_Drive(void);
void Motor_Stop(void);
void Get_Car_Speed(void);
void Motor_Time_Count(void);

#endif
