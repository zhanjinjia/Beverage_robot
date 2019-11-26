#include "Global_include.h"

uint8_t tmp_Uart2_Rx_Buf;
static UART_RX_PKG_t *pUartRxPkg[UART_CHANNEL_TOTAL] = {NULL,NULL,NULL};

UART_HandleTypeDef huart2;

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }

}


void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
 if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 


void MX_USART2_UART_Init(void)
{  
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
//	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);	
//  __HAL_UART_ENABLE(&huart2);
 // HAL_UART_Receive_IT(&huart1, &tmp_Uart1_Rx_Buf, 1);
}

static void __GetUartRxData(UART_RX_PKG_t *pRxPkg)
{ 
   if ((0 == pRxPkg->flag_PkgIsReady) && (pRxPkg->RxCnt < pRxPkg->BuffSize))
   {	
		
		 if (pRxPkg==pUartRxPkg[RS232_UART_NO])	/* 串口1接收 */
		{	
			pRxPkg->pBuff[pRxPkg->RxCnt++] = (USART1->DR & (uint16_t)0x01FF);
			if (pRxPkg->RxCnt >= pRxPkg->BuffSize)
			{
				pRxPkg->RxCnt = 0;
			}	
		}		
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart2)
	{
		__GetUartRxData(pUartRxPkg[RS232_UART_NO]);	
	} 
}


/**
 *    @brief        Write UART data
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    pu8TxBuf        The buffer to send the data to UART transmission FIFO.
 *    @param[out]   u32WriteBytes   The byte number of data.
 *
 *    @return       u32Count transfer byte count
 *
 *    @details      The function is to write data into TX buffer to transmit data by UART.
 */
void Uart_BspWrite(uint8_t UartNo, uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    UART_HandleTypeDef* uart;
    switch (UartNo)
	{
		/* 没用到 */
		case (1):
//			uart = &huart1;
			break;
		/* RS232 */
		case (2):
			uart = &huart2;
			break;
		default:
			break;
	}
	USART2->CR1 &= ~0x02;//关闭接收
	HAL_UART_Transmit(uart, pu8TxBuf, u32WriteBytes, 0xffff);
	USART2->CR1 |= 0x02;//打开接收	
}


int UartBsp_RxPkg_Register( uint8_t UartNo, UART_RX_PKG_t *pRxPkg)
{
    if (UartNo > UART_CHANNEL_TOTAL)
    {
		return -1;
	}	
    if (pUartRxPkg[UartNo] != NULL)
	{
		return -1;
	}
    pUartRxPkg[UartNo] = pRxPkg;
    return 0;
}

/* 串口是否接收完成查询 */
int UartBsp_RxPkg_IsReady(uint8_t UartNo)
{
	return pUartRxPkg[UartNo]->flag_PkgIsReady;
}

/* 串口帧接收完成回调函数 */
void  UartBsp_RxPkg_Complete_TimeIT_Callback(uint8_t UartNo)
{
	 pUartRxPkg[UartNo]->flag_PkgIsReady=1;
}

/* 数据处理完成 */
void UartBsp_RxPkg_EndProcess(uint8_t UartNo)
{
	pUartRxPkg[UartNo]->RxCnt = 0;
	pUartRxPkg[UartNo]->flag_PkgIsReady = 0;
}


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart2,&ch, 1, 0xffff);
  return ch;
}


