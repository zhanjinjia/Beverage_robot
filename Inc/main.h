/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
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
#define GPIO_Input_DET3_P17_Pin GPIO_PIN_2
#define GPIO_Input_DET3_P17_GPIO_Port GPIOE
#define GPIO_Input_DET4_P18_Pin GPIO_PIN_3
#define GPIO_Input_DET4_P18_GPIO_Port GPIOE
#define GPIO_Input_KEY_CON1_P19_Pin GPIO_PIN_4
#define GPIO_Input_KEY_CON1_P19_GPIO_Port GPIOE
#define GPIO_Input_KEY_CON2_P20_Pin GPIO_PIN_5
#define GPIO_Input_KEY_CON2_P20_GPIO_Port GPIOE
#define GPIO_Input_KEY_CON3_P21_Pin GPIO_PIN_6
#define GPIO_Input_KEY_CON3_P21_GPIO_Port GPIOE
#define GPIO_Input_KEY_CON4_P22_Pin GPIO_PIN_13
#define GPIO_Input_KEY_CON4_P22_GPIO_Port GPIOC
#define GPIO_Input_ARM_BACK_P23_Pin GPIO_PIN_14
#define GPIO_Input_ARM_BACK_P23_GPIO_Port GPIOC
#define GPIO_Output_ARM_CONT_P24_Pin GPIO_PIN_15
#define GPIO_Output_ARM_CONT_P24_GPIO_Port GPIOC
#define GPIO_Input_DET5_P28_Pin GPIO_PIN_2
#define GPIO_Input_DET5_P28_GPIO_Port GPIOC
#define GPIO_Input_DET6_P29_Pin GPIO_PIN_3
#define GPIO_Input_DET6_P29_GPIO_Port GPIOC
#define GPIO_Input_SENSOR_OUT1_P30_Pin GPIO_PIN_3
#define GPIO_Input_SENSOR_OUT1_P30_GPIO_Port GPIOA
#define GPIO_Input_SENSOR_OUT2_P31_Pin GPIO_PIN_4
#define GPIO_Input_SENSOR_OUT2_P31_GPIO_Port GPIOA
#define GPIO_Output_LED8_P14_Pin GPIO_PIN_13
#define GPIO_Output_LED8_P14_GPIO_Port GPIOD
#define GPIO_Output_LED7_P13_Pin GPIO_PIN_14
#define GPIO_Output_LED7_P13_GPIO_Port GPIOD
#define GPIO_Output_LED6_P12_Pin GPIO_PIN_15
#define GPIO_Output_LED6_P12_GPIO_Port GPIOD
#define GPIO_Output_LED5_P10_Pin GPIO_PIN_6
#define GPIO_Output_LED5_P10_GPIO_Port GPIOC
#define GPIO_Output_LED4_P9_Pin GPIO_PIN_7
#define GPIO_Output_LED4_P9_GPIO_Port GPIOC
#define GPIO_Output_LED3_P8_Pin GPIO_PIN_8
#define GPIO_Output_LED3_P8_GPIO_Port GPIOC
#define GPIO_Output_Projection_P7_Pin GPIO_PIN_9
#define GPIO_Output_Projection_P7_GPIO_Port GPIOC
#define GPIO_Output_LED1_P5_Pin GPIO_PIN_8
#define GPIO_Output_LED1_P5_GPIO_Port GPIOA
#define GPIO_Output_ARM_CONT_J3_Pin GPIO_PIN_9
#define GPIO_Output_ARM_CONT_J3_GPIO_Port GPIOA
#define GPIO_Input_ARM_BACK_J3_Pin GPIO_PIN_10
#define GPIO_Input_ARM_BACK_J3_GPIO_Port GPIOA
#define GPIO_Output_Power_DR4_P25_Pin GPIO_PIN_0
#define GPIO_Output_Power_DR4_P25_GPIO_Port GPIOD
#define GPIO_Output_Power_DR3_P4_Pin GPIO_PIN_1
#define GPIO_Output_Power_DR3_P4_GPIO_Port GPIOD
#define GPIO_Output_Power_DR2_P26_Pin GPIO_PIN_2
#define GPIO_Output_Power_DR2_P26_GPIO_Port GPIOD
#define GPIO_Output_Power_DR1_P27_Pin GPIO_PIN_3
#define GPIO_Output_Power_DR1_P27_GPIO_Port GPIOD
#define GPIO_Input_DET1_P15_Pin GPIO_PIN_0
#define GPIO_Input_DET1_P15_GPIO_Port GPIOE
#define GPIO_Input_DET2_P16_Pin GPIO_PIN_1
#define GPIO_Input_DET2_P16_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

#define ARM_CONT_LEFT_H HAL_GPIO_WritePin(GPIO_Output_ARM_CONT_P24_GPIO_Port, GPIO_Output_ARM_CONT_P24_Pin, GPIO_PIN_SET) //øÿ÷∆◊Û ÷±€‘À∂Ø
#define ARM_CONT_LEFT_L HAL_GPIO_WritePin(GPIO_Output_ARM_CONT_P24_GPIO_Port, GPIO_Output_ARM_CONT_P24_Pin, GPIO_PIN_RESET) //øÿ÷∆ ÷±€≤ª‘À∂Ø
#define ARM_LEFT_BACK   HAL_GPIO_ReadPin(GPIO_Input_ARM_BACK_P23_GPIO_Port,GPIO_Input_ARM_BACK_P23_Pin)//∂¡»°∑µªÿ «∑ÒÕ£÷π–≈∫≈

#define ARM_CONT_RIGHT_H HAL_GPIO_WritePin(GPIO_Output_ARM_CONT_J3_GPIO_Port, GPIO_Output_ARM_CONT_J3_Pin, GPIO_PIN_SET) //øÿ÷∆ ÷±€‘À∂Ø
#define ARM_CONT_RIGHT_L HAL_GPIO_WritePin(GPIO_Output_ARM_CONT_J3_GPIO_Port, GPIO_Output_ARM_CONT_J3_Pin, GPIO_PIN_RESET) //øÿ÷∆ ÷±€≤ª‘À∂Ø
#define ARM_RIGHT_BACK   HAL_GPIO_ReadPin(GPIO_Input_ARM_BACK_J3_GPIO_Port,GPIO_Input_ARM_BACK_J3_Pin)//∂¡»°∑µªÿ «∑ÒÕ£÷π–≈∫≈

#define PROJECTION_H HAL_GPIO_WritePin(GPIO_Output_Projection_P7_GPIO_Port, GPIO_Output_Projection_P7_Pin, GPIO_PIN_SET) //ø™Õ∂”∞
#define PROJECTION_L HAL_GPIO_WritePin(GPIO_Output_Projection_P7_GPIO_Port, GPIO_Output_Projection_P7_Pin, GPIO_PIN_RESET) //
#define PROJECTION_READ HAL_GPIO_ReadPin(GPIO_Output_Projection_P7_GPIO_Port,GPIO_Output_Projection_P7_Pin)//∂¡»°Õ∂”∞◊¥Ã¨

#define LED_8_H HAL_GPIO_WritePin(GPIO_Output_LED8_P14_GPIO_Port, GPIO_Output_LED8_P14_Pin, GPIO_PIN_SET) //”“µ∆÷√∏ﬂ
#define LED_8_L HAL_GPIO_WritePin(GPIO_Output_LED8_P14_GPIO_Port, GPIO_Output_LED8_P14_Pin, GPIO_PIN_RESET) //÷√µÕ
#define LED_7_H HAL_GPIO_WritePin(GPIO_Output_LED7_P13_GPIO_Port, GPIO_Output_LED7_P13_Pin, GPIO_PIN_SET) //◊Ûµ∆÷√∏ﬂ
#define LED_7_L HAL_GPIO_WritePin(GPIO_Output_LED7_P13_GPIO_Port, GPIO_Output_LED7_P13_Pin, GPIO_PIN_RESET) //÷√µÕ
#define LED_READ_8 HAL_GPIO_ReadPin(GPIO_Output_LED8_P14_GPIO_Port,GPIO_Output_LED8_P14_Pin)//∂¡»°”“µ∆◊¥Ã¨
#define LED_READ_7 HAL_GPIO_ReadPin(GPIO_Output_LED7_P13_GPIO_Port,GPIO_Output_LED7_P13_Pin)//∂¡»°◊Ûµ∆◊¥Ã¨

#define POWER_4_H HAL_GPIO_WritePin(GPIO_Output_Power_DR4_P25_GPIO_Port, GPIO_Output_Power_DR4_P25_Pin, GPIO_PIN_SET) //÷√∏ﬂ
#define POWER_4_L HAL_GPIO_WritePin(GPIO_Output_Power_DR4_P25_GPIO_Port, GPIO_Output_Power_DR4_P25_Pin, GPIO_PIN_RESET) //÷√µÕ
#define POWER_3_H HAL_GPIO_WritePin(GPIO_Output_Power_DR3_P4_GPIO_Port, GPIO_Output_Power_DR3_P4_Pin, GPIO_PIN_SET) //÷√∏ﬂ
#define POWER_3_L HAL_GPIO_WritePin(GPIO_Output_Power_DR3_P4_GPIO_Port, GPIO_Output_Power_DR3_P4_Pin, GPIO_PIN_RESET) //÷√µÕ
#define POWER_READ_3 HAL_GPIO_ReadPin(GPIO_Output_Power_DR3_P4_GPIO_Port,GPIO_Output_Power_DR3_P4_Pin)
#define POWER_READ_4 HAL_GPIO_ReadPin(GPIO_Output_Power_DR4_P25_GPIO_Port,GPIO_Output_Power_DR4_P25_Pin)

#define SENSOR_OUT2   HAL_GPIO_ReadPin(GPIO_Input_SENSOR_OUT2_P31_GPIO_Port,GPIO_Input_SENSOR_OUT2_P31_Pin)//ºÏ≤‚”–Œﬁ∆ø◊”
#define SENSOR_OUT1   HAL_GPIO_ReadPin(GPIO_Input_SENSOR_OUT1_P30_GPIO_Port,GPIO_Input_SENSOR_OUT1_P30_Pin)//ºÏ≤‚µÕ“∫Œª

#define DET_6   HAL_GPIO_ReadPin(GPIO_Input_DET6_P29_GPIO_Port,GPIO_Input_DET6_P29_Pin)//ºÏ≤‚”–Œﬁ∆ø◊”
#define DET_5   HAL_GPIO_ReadPin(GPIO_Input_DET5_P28_GPIO_Port,GPIO_Input_DET5_P28_Pin)//ºÏ≤‚µÕ“∫Œª
#define DET_2   HAL_GPIO_ReadPin(GPIO_Input_DET2_P16_GPIO_Port,GPIO_Input_DET2_P16_Pin)//ºÏ≤‚”“π‚µÁ
#define DET_1   HAL_GPIO_ReadPin(GPIO_Input_DET1_P15_GPIO_Port,GPIO_Input_DET1_P15_Pin)//ºÏ≤‚◊Ûπ‚µÁ


#define KEY_4   HAL_GPIO_ReadPin(GPIO_Input_KEY_CON4_P22_GPIO_Port,GPIO_Input_KEY_CON4_P22_Pin)//ºÏ≤‚”“∂˙∂‰
#define KEY_3   HAL_GPIO_ReadPin(GPIO_Input_KEY_CON3_P21_GPIO_Port,GPIO_Input_KEY_CON3_P21_Pin)//ºÏ≤‚◊Û∂˙∂‰
#define KEY_2   HAL_GPIO_ReadPin(GPIO_Input_KEY_CON2_P20_GPIO_Port,GPIO_Input_KEY_CON2_P20_Pin)//ºÏ≤‚”“∞¥º¸
#define KEY_1   HAL_GPIO_ReadPin(GPIO_Input_KEY_CON1_P19_GPIO_Port,GPIO_Input_KEY_CON1_P19_Pin)//ºÏ≤‚◊Û∞¥º¸

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
