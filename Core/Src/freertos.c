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
#include "usart.h"
#include "Global_include.h"
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
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osSemaphoreId myBinarySem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void Uart2RecvProcess(void);  
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

void uart_test(void);
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

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

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
    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_14);
		osDelay(200);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(myBinarySem01Handle,100);
		Uart2RecvProcess();
//		uart_test();
//		printf("a\r\n");
    

  }
  /* USER CODE END StartTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

//void uart_test(void)
//{
//  if(RxFlag==1)
//	{
////		HAL_UART_Transmit(&huart2,RxBuffer,RxCounter,0xffff);	
//		uint8_t UartTxPkg[32];
//		uint8_t UartTxCnt = 0;
//		uint8_t frame_head,frame_cmd;
//		int diff_norel;
//		int diff_rel;
//		uint8_t i;
//		uint8_t temp_light;
//		uint8_t temp_projection;
//		uint8_t temp_valve;
//		
//		UartTxCnt = RxCounter;//获取帧长
//		for(i = 0; i < UartTxCnt; i++)
//		{
//			UartTxPkg[i] = RxBuffer[i];
//		}
//		frame_head = UartTxPkg[0];
//		frame_cmd = UartTxPkg[1];


////		printf("frame_head:%X\r\n", UartTxPkg[0]);
////		printf("frame_cmd:%X\r\n", UartTxPkg[1]);
////		printf("third:%X\r\n", UartTxPkg[2]);
////		printf("fourth:%X\r\n", UartTxPkg[3]);
////		printf("fifth:%X\r\n", UartTxPkg[5]);
////		printf("sixth:%X\r\n", UartTxPkg[6]);
////		printf("head long:%d\r\n",UartTxCnt);
////		printf("judge head\r\n");
//		if(frame_head == FRAME_START)/* 帧起始 */
//		{
////			printf("enter the head\r\n");
//			if(Crc8_Calc(UartTxPkg, UartTxCnt) == 0)	/* CRC8校验 正确*/
//			{
////				printf("crc is true\r\n");
//				switch(frame_cmd)
//				{
//					case CMD_CONN:  
//						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);//校验
//					  UartTxPkg[2]=0X00;
//					  Uart_BspWrite(&huart2,UartTxPkg ,UartTxCnt);
//						break;
//				  
//					case CMD_QUERY:  
//						UartTxPkg[2]=0X08;					
//						UartTxPkg[3]=0X00;
//					  UartTxPkg[4]=0X00;
//						UartTxPkg[5]=0Xff;
//						UartTxPkg[6]=0X80;
//						UartTxPkg[7]=0X63;
//					  UartTxPkg[8]=0X00;
//						UartTxPkg[9]=0X63;
//						UartTxPkg[10]=0X00;	
//					  UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg,UartTxCnt-1);//校验
//					  Uart_BspWrite(&huart2,UartTxPkg,UartTxCnt);
//						break;
//					  
//					case CMD_ARM_CONTROL_RELEASE:
//											
//						UartTxPkg[2]=0X02;					
//						UartTxPkg[3]=0X80;
//						diff_rel=UartTxPkg[4]-UartTxPkg[4];
//				
//						if(0<=diff_rel&&diff_rel<3)					
//						{
//							UartTxPkg[5]=0X00;
//						}else{
//							UartTxPkg[5]=0X01;
//						}
//					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt+1);
//					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
//						osDelay(100);
//						UartTxPkg[4]=0x07;
//					  if(UartTxPkg[4]<=0x0A)
//						{
//							UartTxPkg[5]=0X00;
//						}else{
//							UartTxPkg[5]=0X01;
//						}
//						UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt+1);
//						HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
//						break;
//					
//					case CMD_ARM_CONTROL_NORELEASE:
//						UartTxPkg[2]=0X02;					
//						UartTxPkg[3]=0X80;
//						diff_norel=UartTxPkg[4]-UartTxPkg[4];
//						if(0<=diff_norel&&diff_norel<3)
//						{
//							UartTxPkg[5]=0X00;
//						}else{
//							UartTxPkg[5]=0X01;
//						}
//					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt+1);
//					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
//					
//						break;
//					
//					case CMD_LIGHT_CONTROL:
//						UartTxPkg[2]=0X01;					
//						UartTxPkg[3]=0X84;
//					  temp_light=0X84;

//						if(temp_light==UartTxPkg[3])
//						{
//							UartTxPkg[4]=0X00;
//						}else{
//							UartTxPkg[4]=0X01;
//						}
//					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt+1);
//					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
//						break;
//															
//					case CMD_VALVE_SWITCH_CONTROL:
//						UartTxPkg[2]=0X01;					
//						UartTxPkg[3]=0X40;
//					  temp_valve=0X40;

//						if(temp_valve==UartTxPkg[3])
//						{
//							UartTxPkg[4]=0X00;
//						}else{
//							UartTxPkg[4]=0X01;
//						}
//					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt+1);
//					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
//						break;
//					
//					case CMD_PROJECTION_SWITCH_CONTROL:
//						UartTxPkg[2]=0X01;					
//						UartTxPkg[3]=0X01;
//					  temp_projection=0X01;

//						if(temp_projection==UartTxPkg[3])
//						{
//							UartTxPkg[4]=0X00;
//						}else{
//							UartTxPkg[4]=0X01;
//						}
//					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt+1);
//					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
//						break;
//	
//					default:
//						break;
//				}

//			}	
//			else 
//			{
////				printf("crc is error\r\n");
//				uint8_t UartCrcError[1]={0XFF};
//				Uart_BspWrite(&huart2,UartCrcError,1);
//			}
//		}
//		else 
//		{
////			printf("head is error！\r\n");
//				uint8_t UartCrcError[1]={0XEE};
//				Uart_BspWrite(&huart2,UartCrcError,1);
//		}
//		
//		RxFlag=0;
//		RxCounter=0;
//		memset(RxBuffer,0,MAX_REC_LENGTH);
//	}
//		osDelay(1);
//		
//}	

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
