#include "motor.h"
#include "usart.h"
#include "bluetooth.h"
#include "tim.h"

#define PI 3.1415926f
#define WHEEL_DIAMETER 0.065

Car_Structure_Def Car_Structure;
float vx_PID[3] = {2300.0f,30.0f,200.0f};	
float vx_max_out = 1000.0f;
float vx_max_iout = 200.0f;

void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_2);
	Car_Structure.vx_set.float_data = 0.0f;
	Car_Structure.turn_angle.float_data = 0.0f;
	Car_Structure.vx[0] = 0.0f;
	Car_Structure.vx[1] = 0.0f;
	Car_Structure.wz[0] = 0.0f;
	Car_Structure.wz[1] = 0.0f;
	Car_Structure.speed_L = 0.0f;
	Car_Structure.speed_R = 0.0f;
	Car_Structure.angle = 0.0f;
	PID_Init(&Car_Structure.vx_PID,PID_POSITION,vx_PID,vx_max_out,vx_max_iout);
}

void Motor_Drive(void)
{
	PID_Calc(&Car_Structure.vx_PID,Car_Structure.speed_L,Car_Structure.vx_set.float_data);
	if(Car_Structure.vx_PID.out == 0.0f)
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,1000);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,1000);
	}
	else if(Car_Structure.vx_PID.out > 0.0f)
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,(uint16_t)Car_Structure.vx_PID.out);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,(uint16_t)(-Car_Structure.vx_PID.out));
	}
	PID_Calc(&Car_Structure.vx_PID,Car_Structure.speed_R,Car_Structure.vx_set.float_data);
	if(Car_Structure.vx_PID.out == 0.0f)
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,1000);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1000);
	}
	else if(Car_Structure.vx_PID.out > 0.0f)
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,(uint16_t)(-Car_Structure.vx_PID.out));
	}
	else
	{
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,(uint16_t)Car_Structure.vx_PID.out);
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
	}
	int32_t wz_pwm = 700;
	if(Car_Structure.turn_angle.float_data >= 0.0f)
		wz_pwm = 700 + 400 * (Car_Structure.turn_angle.float_data  * 30 / 30);
	else
		wz_pwm = 700 + 200 * (Car_Structure.turn_angle.float_data * 30 / 30);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,wz_pwm);
}

void Get_Car_Speed(void)
{
	Car_Structure.speed_L = 100 * PI * WHEEL_DIAMETER * (short)__HAL_TIM_GetCounter(&htim4) / 13 / 30 / 4;
	Car_Structure.speed_R = -100 * PI * WHEEL_DIAMETER * (short)__HAL_TIM_GetCounter(&htim8) / 13 / 30 / 4;
	__HAL_TIM_SET_COUNTER(&htim4,0);
	__HAL_TIM_SET_COUNTER(&htim8,0);
}
