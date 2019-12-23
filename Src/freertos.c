/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "Global_include.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t valve_flag_left = 1;//���ˮ���ɵײ����
uint8_t valve_flag_right = 1;//�Ҳ�ˮ���ɵײ����
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osSemaphoreId myBinarySem01Handle;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId RecvProcesTaskHandle;
osThreadId WaterControlTasHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTaskRecvProcess(void const * argument);
void StartTaskWaterControl(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
	osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of RecvProcesTask */
  osThreadDef(RecvProcesTask, StartTaskRecvProcess, osPriorityNormal, 0, 128);
  RecvProcesTaskHandle = osThreadCreate(osThread(RecvProcesTask), NULL);

  /* definition and creation of WaterControlTas */
  osThreadDef(WaterControlTas, StartTaskWaterControl, osPriorityNormal, 0, 128);
  WaterControlTasHandle = osThreadCreate(osThread(WaterControlTas), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	HAL_UART_Receive_IT(&huart2,(uint8_t *)RxTemp,REC_LENGTH);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTaskRecvProcess */
/**
* @brief Function implementing the RecvProcesTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskRecvProcess */
void StartTaskRecvProcess(void const * argument)
{
  /* USER CODE BEGIN StartTaskRecvProcess */
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(myBinarySem01Handle,100);
		Uart2RecvProcess();
		osDelay(1);
  }
  /* USER CODE END StartTaskRecvProcess */
}

/* USER CODE BEGIN Header_StartTaskWaterControl */
/**
* @brief Function implementing the WaterControlTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskWaterControl */
void StartTaskWaterControl(void const * argument)
{
  /* USER CODE BEGIN StartTaskWaterControl */
  /* Infinite loop */
	
  for(;;)
  {	
#if 1			
    if(valve_flag_left)
		{
			KEY_Scan_Left();
		}
		
		 if(valve_flag_right)
		{
			KEY_Scan_Right();
		}
#endif		
		Kettle_Scan_Level();
		osDelay(10);
		
  }

  /* USER CODE END StartTaskWaterControl */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
