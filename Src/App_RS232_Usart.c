
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

#include "Global_include.h"

//extern uint8_t TimCount;

uint8_t RxBuffer[MAX_REC_LENGTH]={0};
uint8_t RxFlag=0;
uint16_t RxCounter=0;
uint8_t RxTemp[REC_LENGTH]={0};
extern uint8_t valve_flag_left;//左侧水阀由底层控制
extern uint8_t valve_flag_right;//右侧水阀由底层控制

void Uart_BspWrite(UART_HandleTypeDef* uart, uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{  
	uart = &huart2;
	USART2->CR1 &= ~0x02;//关闭接收
	HAL_UART_Transmit(uart, pu8TxBuf, u32WriteBytes, 0x0018);
	USART2->CR1 |= 0x02;//打开接收	
}


/* 串口1 RS232接收处理 */
void Uart2RecvProcess(void)   
{	
	if(RxFlag==1)
	{
//		HAL_UART_Transmit(&huart2,RxBuffer,RxCounter,0x0018);	
		uint8_t UartTxPkg[32];
		uint16_t UartTxCnt = 0;
		uint8_t frame_head,frame_cmd;
		int diff_norel;
		int diff_rel;
		uint8_t i;

		uint8_t UartCrcError[4]={0X5A,0XFF,0X00,0X36};
		uint8_t UartHeadError[4]={0X5A,0XEE,0X00,0X74};
		uint8_t UartTimeOut[4]={0X5A,0XFE,0X00,0X61};	
		

		
		UartTxCnt = RxCounter;//获取帧长
		for(i = 0; i < UartTxCnt; i++)
		{
			UartTxPkg[i] = RxBuffer[i];
		}
		frame_head = UartTxPkg[0];
		frame_cmd = UartTxPkg[1];
		HAL_TIM_Base_Start(&htim2);

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
					/*** 握手 ***/
					case CMD_CONN:  
						UartTxPkg[UartTxCnt-1]= Crc8_Calc(UartTxPkg, UartTxCnt-1);//校验
					  UartTxPkg[2]=0X00;
					  Uart_BspWrite(&huart2,UartTxPkg ,UartTxCnt);
						break;
				  /*** 心跳包 ***/
					case CMD_QUERY:  
						UartTxPkg[2]=0X08;	//数据长度				
						
					  /* 状态一 */	
						UartTxPkg[3]=0X00;	
					  //灯光
						if(1==LED_READ_7)//左灯亮
						{
								UartTxPkg[3]|=0X80;													
						}
						if(0==LED_READ_7)//
						{
								UartTxPkg[3]&=0X7F;												
						}					
						if(1==LED_READ_8)//
						{
								UartTxPkg[3]|=0X08;															
						}						
						if(0==LED_READ_8)//
						{
								UartTxPkg[3]&=0XF7;													
						}	
						//投影
						if(1==PROJECTION_READ)
						{
								UartTxPkg[3]|=0X01;	
						}
						if(0==PROJECTION_READ)
						{
								UartTxPkg[3]&=0XFE;
						}
						
						
						
						
						/* 状态二 */		
						/* 检测耳朵1xxx 1xxx */				
						UartTxPkg[4]=0X00;
						if(1==KEY_3)
						{
							UartTxPkg[4]|=0X80;
						}
						
						if(1==KEY_4)
						{
							UartTxPkg[4]|=0X08;
						}
												
						if(0==KEY_3)
						{
							UartTxPkg[4]&=0X7F;
						}
						
						if(0==KEY_4)
						{
							UartTxPkg[4]&=0XF7;
						}  
						/* 低液位 xx1x xx1x */		
						if(1==DET_5)//检测右低液位
						{
							UartTxPkg[4]|=0X02;
						}
						if(0==DET_5)
						{
							UartTxPkg[4]&=0XFD;//1111 1101
						}
						
						if(1==SENSOR_OUT1)//检测左低液位
						{
							UartTxPkg[4]|=0X20;
						}
						
						if(0==SENSOR_OUT1)
						{
							UartTxPkg[4]&=0XDF;//1101 1111 
						}
						
						
						
						/* 状态三 */		
																	
						UartTxPkg[5]=0X00;
						/* 检测控制状态 1xxx 1xxx */	
						if(1==valve_flag_left)//左边由底层控制
						{
							UartTxPkg[5]|=0X80;
						}
						if(0==valve_flag_left)//左边由Android控制
						{
							UartTxPkg[5]&=0X7F;
						}					
						if(1==valve_flag_right)
						{
							UartTxPkg[5]|=0X08;
						}						
						if(0==valve_flag_right)
						{
							UartTxPkg[5]&=0XF7;
						}							
						
						/* 检测出水按钮 x1xx x1xx */	
						if(1==KEY_1)//
						{
							UartTxPkg[5]|=0X40;
						}
						if(0==KEY_1)//
						{
							UartTxPkg[5]&=0XBF;
						}					
						if(1==KEY_2)
						{
							UartTxPkg[5]|=0X04;
						}						
						if(0==KEY_2)
						{
							UartTxPkg[5]&=0XFB;
						}	
						
						/* 检测水泵状态 x1xx x1xx */	
						if(1==POWER_READ_3)//出水
						{
							UartTxPkg[5]|=0X20;
						}
						if(0==POWER_READ_3)//
						{
							UartTxPkg[5]&=0XDF;
						}					
						if(1==POWER_READ_4)
						{
							UartTxPkg[5]|=0X02;
						}						
						if(0==POWER_READ_4)
						{
							UartTxPkg[5]&=0XFD;
						}							
						
						
						
						UartTxPkg[6]=0X80;
						UartTxPkg[7]=0X63;
					  UartTxPkg[8]=0X00;
						UartTxPkg[9]=0X63;
						UartTxPkg[10]=0X00;	
					  UartTxPkg[11]= Crc8_Calc(UartTxPkg,11);//校验
					  Uart_BspWrite(&huart2,UartTxPkg,12);
						break;
					/*** 手臂控制+释放 ***/  
					case CMD_ARM_CONTROL_RELEASE:
						/* 超时处理 */
					  TimCount=0;
						while(1)
						{
							if(0 == 0)	/* 从机返回数据处理成功 */
							{
								break;
							}	
							else /*这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
								{
									Uart_BspWrite(&huart2,UartTimeOut,4);
									break ;								
								}
							}	
						}					
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
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0x0018);
						osDelay(50);
						
						/* 超时处理 */
					  TimCount=0;
						while(1)
						{
							if(0 == 0)	/* 从机返回数据处理成功 */
							{
								break;
							}	
							else /*这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
								{
									Uart_BspWrite(&huart2,UartTimeOut,4);
									break ;								
								}
							}	
						}	
						UartTxPkg[4]=0x07;
					  if(UartTxPkg[4]<=0x0A)
						{
							UartTxPkg[5]=0X00;
						}else{
							UartTxPkg[5]=0X01;
						}
						
						
						UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
						HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0x0018);
						break;
						/*** 手臂控制+不释放 ***/
					case CMD_ARM_CONTROL_NORELEASE:
						/* 超时处理 */
					  TimCount=0;
						while(1)
						{
							if(0 == 0)	/* 从机返回数据处理成功 */
							{
								break;
							}	
							else /*这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
								{
									Uart_BspWrite(&huart2,UartTimeOut,4);
									break ;								
								}
							}	
						}	
					
						UartTxPkg[2]=0X03;					
						UartTxPkg[3]=0X80;
						diff_norel=UartTxPkg[4]-UartTxPkg[4];
						if(0<=diff_norel&&diff_norel<3)
						{
							UartTxPkg[5]=0X00;
						}else{
							UartTxPkg[5]=0X01;
						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0x0018);
					
						break;
					/*** 灯光控制 ***/
					case CMD_LIGHT_CONTROL:
						/* 超时处理 */
					  TimCount=0;
						while(1)
						{
							if(0 == 0)	/* 从机返回数据处理成功 */
							{
								break;
							}	
							else /*这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
								{
									Uart_BspWrite(&huart2,UartTimeOut,4);
									break ;								
								}
							}	
						}	
					
						UartTxPkg[2]=0X02;
						
						//打开左侧红灯 1xxx xxxx
					  if(((UartTxPkg[3]&0X80)>>7)==0X01)//判断状态位
						{
									LED_8_H;		
						}
						//关闭左侧红灯 0xxx xxxx
					  if(((UartTxPkg[3]&0X80)>>7)==0X00)//判断状态位
						{
									LED_8_L;
						}						
					  //打开右侧红灯 xxxx 1xxx	
						if(((UartTxPkg[3]&0X08)>>3)==0X01)//判断状态位
						{
								  LED_7_H;			
						}
					  //关闭右侧红灯 xxxx 0xxx	
						if(((UartTxPkg[3]&0X08)>>3)==0X00)//判断状态位
						{
							  	LED_7_L;			
						}						
						UartTxPkg[4]=0X00;

					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0x0018);
						break;
						
					/*** 水阀控制 ***/										
					case CMD_VALVE_SWITCH_CONTROL:
						UartTxPkg[2]=0X02;
					  //左侧水阀由平板控制0xxx xxxx
						
					
					  if(((UartTxPkg[3]&0X80)>>7)==0X00)//判断状态位
						{
							valve_flag_left = 0;
//							printf("进入标志位：%X",((UartTxPkg[3]&0X80)>>7));
							if(((UartTxPkg[3]&0X40)>>6)==0X01)	//判断控制位
							{
							   POWER_3_H;
//								printf("进入控制位:%X",((UartTxPkg[3]&0X40)>>6));
							}
							if(((UartTxPkg[3]&0X40)>>6)==0X00)	//判断控制位
							{
							   POWER_3_L;
							}											
						}
						
					  //右侧水阀由平板控制0xxx xxxx
						if(((UartTxPkg[3]&0X08)>>3)==0X00)	
						{
							valve_flag_right = 0;
							if(((UartTxPkg[3]&0X04)>>2)==0X01)	//判断控制位
							{
							   POWER_4_H;
							}
							
							if(((UartTxPkg[3]&0X04)>>2)==0X00)	//判断控制位
							{
							   POWER_4_L;
							}
						}
						
						//左侧水阀由底层控制1xxx xxxx
					  if(((UartTxPkg[3]&0X80)>>7)==0X01)	
						{
							POWER_3_L;
							POWER_4_L;
							valve_flag_left = 1;
						}
						
					  //右侧水阀由底层控制1xxx xxxx
						if(((UartTxPkg[3]&0X08)>>3)==0X01)	
						{
							POWER_3_L;
							POWER_4_L;							
							valve_flag_right = 1;
						}						
						
						UartTxPkg[4]=0X00;
						
					/* 超时处理 */
//					  TimCount=0;
//						while(1)
//						{
//							if(0 == 0)	/* 从机返回数据处理成功 */
//							{
//								break;
//							}	
//							else /*这里加入超时20*50=1000ms退出判断 */
//							{
//								if(TimCount >= 40)
//								{
//									Uart_BspWrite(&huart2,UartTimeOut,4);
//									break ;								
//								}
//							}	
//						}	
					  

											
//						UartTxPkg[3]=0X40;
//					  temp_valve=0X40;

//						if(temp_valve==UartTxPkg[3])
//						{
//							UartTxPkg[4]=0X00;
//						}else{
//							UartTxPkg[4]=0X01;
//						}
					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0x0018);
						break;
						
					/*** 投影电源控制 ***/
					case CMD_PROJECTION_SWITCH_CONTROL:
						/* 超时处理 */
					  TimCount=0;
						while(1)
						{
							if(0 == 0)	/* 从机返回数据处理成功 */
							{
								break;
							}	
							else /*这里加入超时20*50=1000ms退出判断 */
							{
								if(TimCount >= 40)
								{
									Uart_BspWrite(&huart2,UartTimeOut,4);
									break ;								
								}
							}	
						}	
					
						UartTxPkg[2]=0X02;	

						/*  判断控制位 */
						if(0X01==UartTxPkg[3])
						{
							PROJECTION_H;
						}
						
						if(0X00==UartTxPkg[3])
						{
							PROJECTION_L;
						}

						UartTxPkg[4]=0X00;

					  UartTxPkg[UartTxCnt]=Crc8_Calc(UartTxPkg, UartTxCnt);
					  HAL_UART_Transmit(&huart2,UartTxPkg,UartTxCnt+1,0x0018);
						break;
	
					default:
						break;
				}
				  HAL_TIM_Base_Stop(&htim2);
			}	
			else 
			{
//				printf("crc is error\r\n");
				Uart_BspWrite(&huart2,UartCrcError,4);
			}
		}
		else 
		{
//			printf("head is error！\r\n");
				Uart_BspWrite(&huart2,UartHeadError,4);
		}
		
		RxFlag=0;
		RxCounter=0;
		memset(RxBuffer,0,MAX_REC_LENGTH);
	}
		osDelay(1);
		
}



