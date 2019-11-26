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

void Uart1_Respond_CMD_CONN(uint8_t *sendbuf, uint32_t sendlenth)
{
	Uart_BspWrite(RS232_UART_NO,sendbuf ,sendlenth);
}

/* 串口1 RS232接收处理 */
void Uart2RecvProcess(void)   
{	
	uint8_t L01REG_addr = 0;
    if(RS232_UartRxPkg.flag_PkgIsReady == 1)
    {	
		uint8_t UartTxPkg[32];
		uint8_t UartTxCnt = 0;
		uint8_t frame_head,frame_cmd;
		uint8_t i;
		uint8_t ApuAddr;
		uint16_t RegVal;
		
		UartTxCnt = RS232_UartRxPkg.RxCnt;//获取帧长
		for(i = 0; i < UartTxCnt; i++)
		{
			UartTxPkg[i] = RS232_UartRxPkg.pBuff[i];
		}
		frame_head = UartTxPkg[0];
		frame_cmd = UartTxPkg[1];

//		HAL_TIM_Base_Start(&htim2);
		
		if(frame_head == FRAME_START)/* 帧起始 */
		{
			if(Crc8_Calc(UartTxPkg, UartTxCnt) == 0)	/* CRC8校验 正确*/
			{
				switch (frame_cmd)
				{
					case CMD_CONN:  
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);//校验
						Uart1_Respond_CMD_CONN(UartTxPkg, UartTxCnt);
						break;
					case CMD_OPEN: 
//						MB_RTU_Master_WriteHoldingRegister(UartTxPkg[3],0x000A, UartTxPkg[4]);
//						osDelay(100);//必须要延时
						
						UartTxPkg[2] = UartTxPkg[2] + 1;	
						UartTxPkg[UartTxCnt-1] = 0x00;	/* 开盖成功 */
						UartTxPkg[UartTxCnt] = Crc8_Calc(UartTxPkg, UartTxCnt);
						Uart_BspWrite(RS232_UART_NO, UartTxPkg , UartTxCnt + 1);
						break;
					case CMD_CLOSE: 
//						MB_RTU_Master_WriteHoldingRegister(UartTxPkg[3],0x000B,  UartTxPkg[4]);
						osDelay(100);//必须要延时
						
						UartTxPkg[2] = UartTxPkg[2] + 1;
						UartTxPkg[UartTxCnt-1] = 0x00;	/* 关盖成功 */
						UartTxPkg[UartTxCnt] = Crc8_Calc(UartTxPkg, UartTxCnt);
						Uart_BspWrite(RS232_UART_NO, UartTxPkg, UartTxCnt + 1);
						break;
					case CMD_READ_STATUS:
//						MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD1, 0x001A, 1);
						TimCount=0;
						while(1)
						{
//							if(MB_RTU_Master_RxPkgProcess(0x001A) == 0)	/* 从机返回数据处理成功 */
//							{
//								break;
//							}	
//							else /*这这里加入超时20*50=1000ms退出判断 */
//							{
//								if(TimCount >= 40)
//									break ;
//							}	
						}
						osDelay(100);//必须要延时
//						MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD2, 0x001A,  1);
						TimCount=0;
						while(1)
						{
							if(MB_RTU_Master_RxPkgProcess(0x001A)==0)
							{
								break;
							}	
							else /*这这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
									break ;
							}
						}
						osDelay(100);//必须要延时
//						MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD3, 0x001A,  1);
						TimCount=0;
						while(1)
						{
							if(MB_RTU_Master_RxPkgProcess(0x001A)==0)
							{
								break;
							}	
							else /*这这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
								{
//									printf("time out err\n");
									break;
								}
							}
						}
						UartTxPkg[2] = 0x01;	/* 数据长度 */
//						UartTxPkg[UartTxCnt-1] = (u16_Board_StatusReg[0] | (u16_Board_StatusReg[1] << 2) | (u16_Board_StatusReg[2] << 4));
						UartTxPkg[UartTxCnt] = Crc8_Calc(UartTxPkg, UartTxCnt);
						Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt + 1);
						break;
					case CMD_READ_SENSOR:
						if(UartTxPkg[3]!=0)
						{
							MB_RTU_Master_ReadHoldingRegister(UartTxPkg[3], 0x001B,  1);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001B)==0)
//								{
//									//CommLed_On();
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							UartTxPkg[2]=0x02;
//							UartTxPkg[UartTxCnt-1]= u16_Board_SensorReg[UartTxPkg[3]-1];
							UartTxPkg[UartTxCnt]= Crc8_Calc(UartTxPkg, UartTxCnt);
							Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt+1);
						}
						else
						{
//							MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD1, 0x001B,  1);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001B)==0)
//								{
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							osDelay(100);//必须要延时
//							MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD2, 0x001B,  1);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001B)==0)
//								{
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							osDelay(100);//必须要延时
//							MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD3, 0x001B,  1);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001B)==0)
//								{
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							UartTxPkg[2]=0x04;
//							UartTxPkg[4]=u16_Board_SensorReg[0];
//							UartTxPkg[5]=u16_Board_SensorReg[1];
//							UartTxPkg[6]=u16_Board_SensorReg[2];
							UartTxPkg[7]= Crc8_Calc(UartTxPkg, 7);
							Uart_BspWrite(RS232_UART_NO,UartTxPkg ,8);
							/* code */
						}	
						break;
					case CMD_READ_WEIGHT:
						if(UartTxPkg[3]!=0)
						{
							MB_RTU_Master_ReadHoldingRegister(UartTxPkg[3], 0x001C,  4);
							TimCount=0;
							while(1)
							{
								if(MB_RTU_Master_RxPkgProcess(0x001C)==0)
								{
									break;
								}
								else /*这这里加入超时20*50=1000ms退出判断 */
								{
									if(TimCount >= 40)
										break ;
								}
							}
							UartTxPkg[2]=0x09;
							switch(UartTxPkg[3])
							{
//								case MB_DEV_ADDR_BOARD1:
//									UartTxPkg[4]=LOW(u16_Board_WeightReg[0]);
//									UartTxPkg[5]=HIGH(u16_Board_WeightReg[0]);
//									UartTxPkg[6]=LOW(u16_Board_WeightReg[1]);
//									UartTxPkg[7]=HIGH(u16_Board_WeightReg[1]);
//									UartTxPkg[8]=LOW(u16_Board_WeightReg[2]);
//									UartTxPkg[9]=HIGH(u16_Board_WeightReg[2]);
//									UartTxPkg[10]=LOW(u16_Board_WeightReg[3]);
//									UartTxPkg[11]=HIGH(u16_Board_WeightReg[3]);
//									break;
//								case MB_DEV_ADDR_BOARD2:
//									UartTxPkg[4]=LOW(u16_Board_WeightReg[4]);
//									UartTxPkg[5]=HIGH(u16_Board_WeightReg[4]);
//									UartTxPkg[6]=LOW(u16_Board_WeightReg[5]);
//									UartTxPkg[7]=HIGH(u16_Board_WeightReg[5]);
//									UartTxPkg[8]=LOW(u16_Board_WeightReg[6]);
//									UartTxPkg[9]=HIGH(u16_Board_WeightReg[6]);
//									UartTxPkg[10]=LOW(u16_Board_WeightReg[7]);
//									UartTxPkg[11]=HIGH(u16_Board_WeightReg[7]);
//									break;
//								case MB_DEV_ADDR_BOARD3:
//									UartTxPkg[4]=LOW(u16_Board_WeightReg[8]);
//									UartTxPkg[5]=HIGH(u16_Board_WeightReg[8]);
//									UartTxPkg[6]=LOW(u16_Board_WeightReg[9]);
//									UartTxPkg[7]=HIGH(u16_Board_WeightReg[9]);
//									UartTxPkg[8]=LOW(u16_Board_WeightReg[10]);
//									UartTxPkg[9]=HIGH(u16_Board_WeightReg[10]);
//									UartTxPkg[10]=LOW(u16_Board_WeightReg[11]);
//									UartTxPkg[11]=HIGH(u16_Board_WeightReg[11]);
//									break;
//							}
							UartTxPkg[12]= Crc8_Calc(UartTxPkg, 12);
							Uart_BspWrite(RS232_UART_NO,UartTxPkg ,13);
						}
						else
						{
							
//							MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD1, 0x001C,  4);
							TimCount=0;
							while(1)
							{
								if(MB_RTU_Master_RxPkgProcess(0x001C)==0)
								{
									break;
								}
								else /*这这里加入超时20*50=1000ms退出判断 */
								{
									if(TimCount >= 40)
										break ;
								}
							}
							osDelay(100);//必须要延时
//							MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD2, 0x001C,  4);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001C)==0)
//								{
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							osDelay(100);//必须要延时
//							MB_RTU_Master_ReadHoldingRegister(MB_DEV_ADDR_BOARD3, 0x001C,  4);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001C)==0)
//								{
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							UartTxPkg[2]=0x19;
							uint8_t *pU8;
							pU8=&UartTxPkg[4];
							for (i=0;i<12;i++)
							{
//								pU8[i*2] = LOW(u16_Board_WeightReg[i]);
//								pU8[i*2+1]= HIGH(u16_Board_WeightReg[i]);
							}
							// UartTxPkg[4]=HIGH(u16_Board_WeightReg[0]);
							// UartTxPkg[5]=LOW(u16_Board_WeightReg[0]);
							// UartTxPkg[6]=HIGH(u16_Board_WeightReg[1]);
							// UartTxPkg[7]=HIGH(u16_Board_WeightReg[1]);
							// UartTxPkg[8]=HIGH(u16_Board_WeightReg[2]);
							// UartTxPkg[9]=LOW(u16_Board_WeightReg[2]);
							// UartTxPkg[10]=HIGH(u16_Board_WeightReg[3]);
							// UartTxPkg[11]=HIGH(u16_Board_WeightReg[3]);
							// UartTxPkg[12]=HIGH(u16_Board_WeightReg[4]);
							// UartTxPkg[13]=LOW(u16_Board_WeightReg[4]);
							// UartTxPkg[14]=HIGH(u16_Board_WeightReg[5]);
							// UartTxPkg[15]=HIGH(u16_Board_WeightReg[5]);
							// UartTxPkg[16]=HIGH(u16_Board_WeightReg[6]);
							// UartTxPkg[17]=LOW(u16_Board_WeightReg[6]);
							// UartTxPkg[18]=HIGH(u16_Board_WeightReg[7]);
							// UartTxPkg[19]=HIGH(u16_Board_WeightReg[7]);
							// UartTxPkg[20]=HIGH(u16_Board_WeightReg[8]);
							// UartTxPkg[21]=LOW(u16_Board_WeightReg[8]);
							// UartTxPkg[22]=HIGH(u16_Board_WeightReg[9]);
							// UartTxPkg[23]=HIGH(u16_Board_WeightReg[9]);
							// UartTxPkg[24]=HIGH(u16_Board_WeightReg[10]);
							// UartTxPkg[25]=LOW(u16_Board_WeightReg[10]);
							// UartTxPkg[26]=HIGH(u16_Board_WeightReg[11]);
							// UartTxPkg[27]=HIGH(u16_Board_WeightReg[11]);	
							UartTxPkg[28]= Crc8_Calc(UartTxPkg, 28);
							Uart_BspWrite(RS232_UART_NO,UartTxPkg ,29);
						}	
						break;
					case CMD_WEIGHT_CALIBRATION :
						MB_RTU_Master_WriteHoldingRegister(UartTxPkg[3],0x000C, UartTxPkg[4]);
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);
						Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt);
						break;
		//			case CMD_WEIGHT_CALIBRATION1 :
		//				MB_RTU_Master_WriteHoldingRegister(UartTxPkg[3],0x000D, UartTxPkg[4]);
		//			    UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);
		//				Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt);
		//				break;
					case CMD_START_PWM_CALIBRATION :
						ApuAddr=UartTxPkg[3];
						RegVal=(((uint16_t)(UartTxPkg[4]&0x0f))<<12)|(((uint16_t)UartTxPkg[6])<<8)|UartTxPkg[5];
						MB_RTU_Master_WriteHoldingRegister(ApuAddr,0x000E, RegVal);
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);
						Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt);
						break;
					case CMD_STOP_PWM_CALIBRATION :
						ApuAddr=UartTxPkg[3];
						RegVal=(((uint16_t)(UartTxPkg[4]&0x0f))<<12)|(((uint16_t)UartTxPkg[6])<<8)|UartTxPkg[5];
						MB_RTU_Master_WriteHoldingRegister(ApuAddr,0x000F, RegVal);
						UartTxPkg[UartTxCnt-1] = Crc8_Calc(UartTxPkg, UartTxCnt-1);
						Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt);
						break;
					case CMD_PWM_SAVE :
						MB_RTU_Master_WriteHoldingRegister(UartTxPkg[3],0x0010, UartTxPkg[4]);
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);
						Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt);
						break;
					case CMD_READ_PWM :
						if(UartTxPkg[3]!=0)
						{
							MB_RTU_Master_ReadHoldingRegister(UartTxPkg[3], 0x001D,  4);
							TimCount=0;
							while(1)
							{
//								if(MB_RTU_Master_RxPkgProcess(0x001D)==0)
//								{
//									break;
//								}
//								else /*这这里加入超时20*50=1000ms退出判断 */
//								{
//									if(TimCount >= 40)
//										break ;
//								}
							}
							UartTxPkg[2]=0x06;
//							switch(UartTxPkg[3])
//							{
//								case MB_DEV_ADDR_BOARD1:
//									if(UartTxPkg[4]==1)
//									{
//										UartTxPkg[5]=LOW(u16_Board_PWMReg[0]);
//										UartTxPkg[6]=HIGH(u16_Board_PWMReg[0]);
//										UartTxPkg[7]=LOW(u16_Board_PWMReg[1]);
//										UartTxPkg[8]=HIGH(u16_Board_PWMReg[1]);
//									}
//									else if(UartTxPkg[4]==2)
//									{
//										UartTxPkg[5]=LOW(u16_Board_PWMReg[2]);
//										UartTxPkg[6]=HIGH(u16_Board_PWMReg[2]);
//										UartTxPkg[7]=LOW(u16_Board_PWMReg[3]);
//										UartTxPkg[8]=HIGH(u16_Board_PWMReg[3]);
//									}
//									break;
//								case MB_DEV_ADDR_BOARD2:
//									if(UartTxPkg[4]==1)
//									{
//										UartTxPkg[5]=LOW(u16_Board_PWMReg[4]);
//										UartTxPkg[6]=HIGH(u16_Board_PWMReg[4]);
//										UartTxPkg[7]=LOW(u16_Board_PWMReg[5]);
//										UartTxPkg[8]=HIGH(u16_Board_PWMReg[5]);
//									}
//									else if(UartTxPkg[4]==2)
//									{
//										UartTxPkg[5]=LOW(u16_Board_PWMReg[6]);
//										UartTxPkg[6]=HIGH(u16_Board_PWMReg[6]);
//										UartTxPkg[7]=LOW(u16_Board_PWMReg[7]);
//										UartTxPkg[8]=HIGH(u16_Board_PWMReg[7]);
//									}
//									break;
//								case MB_DEV_ADDR_BOARD3:
//									if(UartTxPkg[4]==1)
//									{
//										UartTxPkg[5]=LOW(u16_Board_PWMReg[8]);
//										UartTxPkg[6]=HIGH(u16_Board_PWMReg[8]);
//										UartTxPkg[7]=LOW(u16_Board_PWMReg[9]);
//										UartTxPkg[8]=HIGH(u16_Board_PWMReg[9]);
//									}
//									else if(UartTxPkg[4]==2)
//									{
//										UartTxPkg[5]=LOW(u16_Board_PWMReg[10]);
//										UartTxPkg[6]=HIGH(u16_Board_PWMReg[10]);
//										UartTxPkg[7]=LOW(u16_Board_PWMReg[11]);
//										UartTxPkg[8]=HIGH(u16_Board_PWMReg[11]);
//									}
//									break;
//							}
							UartTxPkg[9]= Crc8_Calc(UartTxPkg, 9);
							Uart_BspWrite(RS232_UART_NO,UartTxPkg ,10);
						}
						else
						{
						}	
						break;
					case CMD_SET_NRF_ADDR :
						//BEEP..........
						BEEP_TOGGLE();
					
						L01_CE_LOW();
//						L01_WriteSingleReg(L01REG_RF_CH, UartTxPkg[3]); 
						UartTxPkg[3] = 0;
						L01REG_addr = L01_ReadSingleReg(L01REG_RF_CH);
						UartTxPkg[3] = L01REG_addr;
//						L01_WriteSingleReg(L01REG_RF_CH, 4);// 初始化频率2.4G+60

						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);
						Uart_BspWrite(RS232_UART_NO,UartTxPkg ,UartTxCnt);
						break;
		//			case CMD_READ_NRF_ADDR :
		//				UartTxPkg[2]=0x02;
		//				UartTxPkg[3]=RF24L01_Addr[0];
		//				UartTxPkg[4]=RF24L01_Addr[1];
		//				UartTxPkg[5]=Crc8_Calc(UartTxPkg, 5);
		//				Uart_BspWrite(RS232_UART_NO,UartTxPkg ,6);
		//				break;
					case CMD_RETURN_BUTTON_PRESS :
						ButtonPressSuccess=1;
						break;	
					default:
						break;
				}

			}	
			else 
			{
//				printf("crc err\n");
			}
		}
		UartBsp_RxPkg_EndProcess(RS232_UART_NO);
	}
}



