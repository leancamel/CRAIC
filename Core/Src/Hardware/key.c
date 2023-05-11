#include "key.h"

void Key_Time_Count(void)
{
	Car_Structure.key_time++;
	if(Car_Structure.key_time > 1000)
	{
		Car_Structure.key_time = 1000;
	}
}

uint8_t Key_Read(void)
{
	return HAL_GPIO_ReadPin(Key_GPIO_Port,Key_Pin);
}
