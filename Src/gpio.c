/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_Output_ARM_CONT_P24_Pin|GPIO_Output_LED5_P10_Pin|GPIO_Output_LED4_P9_Pin|GPIO_Output_LED3_P8_Pin 
                          |GPIO_Output_Projection_P7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_Output_LED8_P14_Pin|GPIO_Output_LED7_P13_Pin|GPIO_Output_LED6_P12_Pin|GPIO_Output_Power_DR4_P25_Pin 
                          |GPIO_Output_Power_DR3_P4_Pin|GPIO_Output_Power_DR2_P26_Pin|GPIO_Output_Power_DR1_P27_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_Output_LED1_P5_Pin|GPIO_Output_ARM_CONT_J3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin 
                           PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = GPIO_Input_DET3_P17_Pin|GPIO_Input_DET4_P18_Pin|GPIO_Input_KEY_CON1_P19_Pin|GPIO_Input_KEY_CON2_P20_Pin 
                          |GPIO_Input_KEY_CON3_P21_Pin|GPIO_Input_DET1_P15_Pin|GPIO_Input_DET2_P16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = GPIO_Input_KEY_CON4_P22_Pin|GPIO_Input_ARM_BACK_P23_Pin|GPIO_Input_DET5_P28_Pin|GPIO_Input_DET6_P29_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin 
                           PCPin */
  GPIO_InitStruct.Pin = GPIO_Output_ARM_CONT_P24_Pin|GPIO_Output_LED5_P10_Pin|GPIO_Output_LED4_P9_Pin|GPIO_Output_LED3_P8_Pin 
                          |GPIO_Output_Projection_P7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = GPIO_Input_SENSOR_OUT1_P30_Pin|GPIO_Input_SENSOR_OUT2_P31_Pin|GPIO_Input_ARM_BACK_J3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin 
                           PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = GPIO_Output_LED8_P14_Pin|GPIO_Output_LED7_P13_Pin|GPIO_Output_LED6_P12_Pin|GPIO_Output_Power_DR4_P25_Pin 
                          |GPIO_Output_Power_DR3_P4_Pin|GPIO_Output_Power_DR2_P26_Pin|GPIO_Output_Power_DR1_P27_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = GPIO_Output_LED1_P5_Pin|GPIO_Output_ARM_CONT_J3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
