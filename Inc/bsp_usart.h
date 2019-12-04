#ifndef __BSP_USART_H__
#define __BSP_USART_H__


#include "stm32f4xx_hal.h"

//#include "bsp_led.h"

/* 通道数量定义 */
#define UART_CHANNEL_TOTAL  3


/* 数据结构定义 */
typedef struct
{
  uint8_t *pBuff;	/* 接收BUFF */
  uint16_t BuffSize; 	/* 接收BUFF大小 */
  uint16_t RxCnt;   /* 接收数据长度 */ 
  uint8_t flag_PkgIsReady;	/* 数据帧接收完成标志 1：完成 0：未完成 */
}UART_RX_PKG_t;

extern UART_HandleTypeDef huart2;

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

int UartBsp_RxPkg_Register(uint8_t UartNo,UART_RX_PKG_t *pRxPkg);
void Uart_BspWrite(uint8_t UartNo, uint8_t *pu8TxBuf, uint32_t u32WriteBytes);
int UartBsp_RxPkg_IsReady(uint8_t UartNo);
void UartBsp_RxPkg_EndProcess(uint8_t UartNo );
void UartBsp_RxPkg_Complete_TimeIT_Callback(uint8_t UartNo);


#endif  


