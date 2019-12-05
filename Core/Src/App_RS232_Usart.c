
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"
#include "Global_include.h"

//extern uint8_t TimCount;

//#define RS232_RX_BUFF_SIZE		(32)		/* 串口1    232串口接收BUFF大小 */
//static uint8_t RS232_RxBuff[RS232_RX_BUFF_SIZE];	/* 串口1  232数据接收BUFF*/
//static UART_RX_PKG_t RS232_UartRxPkg;
//uint8_t ButtonPressSuccess=0;

//void RS232_UartRxPkg_Init(void)
//{
//	
//	memset(RS232_RxBuff, 0, RS232_RX_BUFF_SIZE);
//  RS232_UartRxPkg.pBuff = RS232_RxBuff;
//	RS232_UartRxPkg.BuffSize = RS232_RX_BUFF_SIZE;
//	RS232_UartRxPkg.RxCnt = 0;
//	RS232_UartRxPkg.flag_PkgIsReady = 0;
//	if (UartBsp_RxPkg_Register(RS232_UART_NO,&RS232_UartRxPkg))
//	{
//		RS232_Usart_PRINTF("RS232uart channel Rx package FAIL!\n");
//	}
//}

//void Uart2_Respond_CMD_CONN(uint8_t *sendbuf, uint32_t sendlenth)
//{
//	Uart_BspWrite(RS232_UART_NO,sendbuf ,sendlenth);
//}


void Uart_BspWrite(UART_HandleTypeDef* uart, uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{  
	uart = &huart2;
	USART2->CR1 &= ~0x02;//关闭接收
	HAL_UART_Transmit(uart, pu8TxBuf, u32WriteBytes, 0xffff);
	USART2->CR1 |= 0x02;//打开接收	
}


/* 串口1 RS232接收处理 */
void Uart2RecvProcess(void)   
{	
	if(RxFlag==1)
	{
//		HAL_UART_Transmit(&huart2,RxBuffer,RxCounter,0xffff);	
		uint8_t UartTxPkg[32];
		uint8_t UartTxCnt = 0;
		uint8_t frame_head,frame_cmd;
		int diff_norel;
		int diff_rel;
		uint8_t i;
		uint8_t temp_light;
		uint8_t temp_projection;
		uint8_t temp_valve;
		
		UartTxCnt = RxCounter;//获取帧长
		for(i = 0; i < UartTxCnt; i++)
		{
			UartTxPkg[i] = RxBuffer[i];
		}
		frame_head = UartTxPkg[0];
		frame_cmd = UartTxPkg[1];


//		printf("frame_head:%X\r\n", UartTxPkg[0]);
//		printf("frame_cmd:%X\r\n", UartTxPkg[1]);
//		printf("third:%X\r\n", UartTxPkg[2]);
//		printf("fourth:%X\r\n", UartTxPkg[3]);
//		printf("fifth:%X\r\n", UartTxPkg[5]);
//		printf("sixth:%X\r\n", UartTxPkg[6]);
//		printf("head long:%d\r\n",UartTxCnt);
//		printf("judge head\r\n");
		if(frame_head == FRAME_START)/* 帧起始 */
		{
//			printf("enter the head\r\n");
			if(Crc8_Calc(UartTxPkg, UartTxCnt) == 0)	/* CRC8校验 正确*/
			{
//				printf("crc is true\r\n");
				switch(frame_cmd)
				{
					case CMD_CONN:  
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);//校验
					  UartTxPkg[2]=0X00;
					  Uart_BspWrite(&huart2,UartTxPkg ,UartTxCnt);
						break;
				  
					case CMD_QUERY:  
						UartTxPkg[2]=0X08;					
						UartTxPkg[3]=0X00;
					  UartTxPkg[4]=0X00;
						UartTxPkg[5]=0Xff;
						UartTxPkg[6]=0X80;
						UartTxPkg[7]=0X63;
					  UartTxPkg[8]=0X00;
						UartTxPkg[9]=0X63;
						UartTxPkg[10]=0X00;	
					  UartTxPkg[11]= Crc8_Calc(UartTxPkg,11);//校验
					  Uart_BspWrite(&huart2,UartTxPkg,12);
						break;
					  
					case CMD_ARM_CONTROL_RELEASE:
											
						UartTxPkg[2]=0X02;					
						UartTxPkg[3]=0X80;
						diff_rel=UartTxPkg[4]-UartTxPkg[4];
				
						if(0<=diff_rel&&diff_rel<3)					
						{
							UartTxPkg[5]=0X00;
						}else{
							UartTxPkg[5]=0X01;
						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
						osDelay(100);
						UartTxPkg[4]=0x07;
					  if(UartTxPkg[4]<=0x0A)
						{
							UartTxPkg[5]=0X00;
						}else{
							UartTxPkg[5]=0X01;
						}
						UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
						HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
						break;
					
					case CMD_ARM_CONTROL_NORELEASE:
						UartTxPkg[2]=0X02;					
						UartTxPkg[3]=0X80;
						diff_norel=UartTxPkg[4]-UartTxPkg[4];
						if(0<=diff_norel&&diff_norel<3)
						{
							UartTxPkg[5]=0X00;
						}else{
							UartTxPkg[5]=0X01;
						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
					
						break;
					
					case CMD_LIGHT_CONTROL:
						UartTxPkg[2]=0X01;					
						UartTxPkg[3]=0X84;
					  temp_light=0X84;

						if(temp_light==UartTxPkg[3])
						{
							UartTxPkg[4]=0X00;
						}else{
							UartTxPkg[4]=0X01;
						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
						break;
															
					case CMD_VALVE_SWITCH_CONTROL:
						UartTxPkg[2]=0X01;					
						UartTxPkg[3]=0X40;
					  temp_valve=0X40;

						if(temp_valve==UartTxPkg[3])
						{
							UartTxPkg[4]=0X00;
						}else{
							UartTxPkg[4]=0X01;
						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
						break;
					
					case CMD_PROJECTION_SWITCH_CONTROL:
						UartTxPkg[2]=0X01;					
						UartTxPkg[3]=0X01;
					  temp_projection=0X01;

						if(temp_projection==UartTxPkg[3])
						{
							UartTxPkg[4]=0X00;
						}else{
							UartTxPkg[4]=0X01;
						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0xffff);
						break;
	
					default:
						break;
				}

			}	
			else 
			{
//				printf("crc is error\r\n");
				uint8_t UartCrcError[1]={0XFF};
				Uart_BspWrite(&huart2,UartCrcError,1);
			}
		}
		else 
		{
//			printf("head is error！\r\n");
				uint8_t UartCrcError[1]={0XEE};
				Uart_BspWrite(&huart2,UartCrcError,1);
		}
		
		RxFlag=0;
		RxCounter=0;
		memset(RxBuffer,0,MAX_REC_LENGTH);
	}
		osDelay(1);
		
}



