/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bluetooth.h"
#include "buzzer.h"
#include "led.h"
#include "motor.h"
#include "MPU6050.h"
#include "voltage.h"
#include "usart.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for UserTask */
osThreadId_t UserTaskHandle;
const osThreadAttr_t UserTask_attributes = {
  .name = "UserTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for FeedBackTask */
osThreadId_t FeedBackTaskHandle;
const osThreadAttr_t FeedBackTask_attributes = {
  .name = "FeedBackTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MotorTask */
osThreadId_t MotorTaskHandle;
const osThreadAttr_t MotorTask_attributes = {
  .name = "MotorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for LEDTask */
osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartUserTask(void *argument);
void StartFeedBackTask(void *argument);
void StartMotorTask(void *argument);
void StartLEDTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of UserTask */
  UserTaskHandle = osThreadNew(StartUserTask, NULL, &UserTask_attributes);

  /* creation of FeedBackTask */
  FeedBackTaskHandle = osThreadNew(StartFeedBackTask, NULL, &FeedBackTask_attributes);

  /* creation of MotorTask */
  MotorTaskHandle = osThreadNew(StartMotorTask, NULL, &MotorTask_attributes);

  /* creation of LEDTask */
  LEDTaskHandle = osThreadNew(StartLEDTask, NULL, &LEDTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartUserTask */
/**
 * @brief  Function implementing the UserTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUserTask */
void StartUserTask(void *argument)
{
  /* USER CODE BEGIN StartUserTask */
	/* Infinite loop */
	for (;;)
	{
		// if(Voltage_Get() < 8.0f)
		// 	Buzzer_On();
		// else
		// 	Buzzer_Off();
		// printf("%f,%f\n",Car_Structure.wz[0],Car_Structure.angle);
		// Bluetooth_Send("%f %hd",Car_Structure.angle,Car_Structure.wz[0]);
		Bluetooth_Send("%f %f %f",Car_Structure.speed_L,Car_Structure.speed_R,Car_Structure.vx_set.float_data);
		osDelay(10);
	}
  /* USER CODE END StartUserTask */
}

/* USER CODE BEGIN Header_StartFeedBackTask */
/**
 * @brief Function implementing the FeedBackTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartFeedBackTask */
void StartFeedBackTask(void *argument)
{
  /* USER CODE BEGIN StartFeedBackTask */
	MPU6050_Init();
	Motor_Init();
	/* Infinite loop */
	for (;;)
	{
		MPU6050_GetData();
		Get_Car_Speed();
		osDelay(10);
	}
  /* USER CODE END StartFeedBackTask */
}

/* USER CODE BEGIN Header_StartMotorTask */
/**
 * @brief Function implementing the MotorTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartMotorTask */
void StartMotorTask(void *argument)
{
  /* USER CODE BEGIN StartMotorTask */
	HAL_Delay(50);
	/* Infinite loop */
	for (;;)
	{
		Motor_Drive();
		osDelay(1);
	}
  /* USER CODE END StartMotorTask */
}

/* USER CODE BEGIN Header_StartLEDTask */
/**
 * @brief Function implementing the LEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartLEDTask */
void StartLEDTask(void *argument)
{
  /* USER CODE BEGIN StartLEDTask */
	/* Infinite loop */
	for (;;)
	{
		LED1_On(1);
		osDelay(500);
		LED1_On(0);
		osDelay(500);
	}
  /* USER CODE END StartLEDTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

