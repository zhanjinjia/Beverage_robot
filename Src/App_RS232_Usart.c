#include "Global_include.h"


extern uint8_t TimCount;

#define RS232_RX_BUFF_SIZE		(32)		/* 串口1    232串口接收BUFF大小 */
static uint8_t RS232_RxBuff[RS232_RX_BUFF_SIZE];	/* 串口1  232数据接收BUFF*/
static UART_RX_PKG_t RS232_UartRxPkg;
uint8_t ButtonPressSuccess=0;

void RS232_UartRxPkg_Init(void)
{
	
	memset(RS232_RxBuff, 0, RS232_RX_BUFF_SIZE);
  RS232_UartRxPkg.pBuff = RS232_RxBuff;
	RS232_UartRxPkg.BuffSize = RS232_RX_BUFF_SIZE;
	RS232_UartRxPkg.RxCnt = 0;
	RS232_UartRxPkg.flag_PkgIsReady = 0;
	if (UartBsp_RxPkg_Register(RS232_UART_NO,&RS232_UartRxPkg))
	{
		RS232_Usart_PRINTF("RS232uart channel Rx package FAIL!\n");
	}
}

void Uart2_Respond_CMD_CONN(uint8_t *sendbuf, uint32_t sendlenth)
{
	Uart_BspWrite(RS232_UART_NO,sendbuf ,sendlenth);
}

/* 串口1 RS232接收处理 */
void Uart2RecvProcess(void)   
{	
//	uint8_t L01REG_addr = 0;
		printf("a\r\n");
    if(RS232_UartRxPkg.flag_PkgIsReady == 1)
    {	
		uint8_t UartTxPkg[32];
		uint8_t UartTxCnt = 0;
		uint8_t frame_head,frame_cmd;
		uint8_t i;
		
		UartTxCnt = RS232_UartRxPkg.RxCnt;//获取帧长
		for(i = 0; i < UartTxCnt; i++)
		{
			UartTxPkg[i] = RS232_UartRxPkg.pBuff[i];
		}
		frame_head = UartTxPkg[0];
		frame_cmd = UartTxPkg[1];

//		HAL_TIM_Base_Start(&htim2);
		printf("c\r\n");
		if(frame_head == FRAME_START)/* 帧起始 */
		{
			printf("d\r\n");
			if(Crc8_Calc(UartTxPkg, UartTxCnt) == 0)	/* CRC8校验 正确*/
			{
				printf("e\r\n");
				switch (frame_cmd)
				{
					case CMD_QUERY:  
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);//校验
						Uart2_Respond_CMD_CONN(UartTxPkg, UartTxCnt);
						break;
					
					case CMD_ARM_CONTROL_RELEASE:
						printf("0x01\r\n");
						break;
					
					case CMD_ARM_CONTROL_NORELEASE:
						printf("0x02\r\n");
						break;
					
					case CMD_LIGHT_CONTROL:
						printf("0x03\r\n");
						break;
															
					case CMD_VALVE_SWITCH_CONTROL:
						printf("0x04\r\n");
						break;
					
					case CMD_PROJECTION_SWITCH_CONTROL:
						printf("0x05\r\n");
						break;
	
					default:
						break;
				}

			}	
			else 
			{
				printf("crc err\r\n");
			}
		}
		UartBsp_RxPkg_EndProcess(RS232_UART_NO);
	}
}



