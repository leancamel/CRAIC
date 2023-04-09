/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Voltage_Pin GPIO_PIN_1
#define Voltage_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOC
#define Key_Pin GPIO_PIN_0
#define Key_GPIO_Port GPIOA
#define Motor_L1_Pin GPIO_PIN_6
#define Motor_L1_GPIO_Port GPIOA
#define Motor_L2_Pin GPIO_PIN_7
#define Motor_L2_GPIO_Port GPIOA
#define Motor_R1_Pin GPIO_PIN_0
#define Motor_R1_GPIO_Port GPIOB
#define Motor_R2_Pin GPIO_PIN_1
#define Motor_R2_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_14
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_15
#define SDA_GPIO_Port GPIOB
#define Encoder_R1_Pin GPIO_PIN_6
#define Encoder_R1_GPIO_Port GPIOC
#define Encoder_R2_Pin GPIO_PIN_7
#define Encoder_R2_GPIO_Port GPIOC
#define S20F_Pin GPIO_PIN_8
#define S20F_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_15
#define Buzzer_GPIO_Port GPIOA
#define TX_Pin GPIO_PIN_10
#define TX_GPIO_Port GPIOC
#define RX_Pin GPIO_PIN_11
#define RX_GPIO_Port GPIOC
#define Bluetooth_TX_Pin GPIO_PIN_12
#define Bluetooth_TX_GPIO_Port GPIOC
#define Bluetooth_RX_Pin GPIO_PIN_2
#define Bluetooth_RX_GPIO_Port GPIOD
#define Encoder_L1_Pin GPIO_PIN_6
#define Encoder_L1_GPIO_Port GPIOB
#define Encoder_L2_Pin GPIO_PIN_7
#define Encoder_L2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
