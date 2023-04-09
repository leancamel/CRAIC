#include "voltage.h"
#include "adc.h"

#define Kp_Voltage 11.0f

float Voltage_Get(void)
{
	uint16_t ADC_Value = 0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,100);
	if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC))
	{
		ADC_Value = HAL_ADC_GetValue(&hadc1);
		return (float)((float)ADC_Value / 4095.0f * 3.3f * Kp_Voltage);
	}
	return 0.0f;
}

