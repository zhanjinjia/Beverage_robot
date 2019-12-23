/******************************************************************************/
#ifndef __APP_RS232_USART__
#define __APP_RS232_USART__
/******************************************************************************/
#include <stdint.h>
#include "Global_include.h"



// 调试定义
#if 0
    #define RS232_Usart_PRINTF   printf
#else
    #define RS232_Usart_PRINTF(...);
#endif

// 串口定义
#define RS232_UART_NO               2   // 串口通道2


#define FRAME_START		(0X5A)	/* 帧起始 */

#define	CMD_CONN			0x00  /*握手*/
#define CMD_QUERY     0x01	/* 心跳包，周期性查询 */
#define CMD_ARM_CONTROL_RELEASE     0x02	/* 手臂控制1 */
#define CMD_ARM_CONTROL_NORELEASE    0x03	/* 手臂控制2 */
#define CMD_LIGHT_CONTROL    0x04	/* 灯光控制 */
#define CMD_VALVE_SWITCH_CONTROL   0x05	/* 水阀开关控制 */
#define CMD_PROJECTION_SWITCH_CONTROL    0x06	/* 投影开关控制 */

#define RECEIVE_NORMAL    0x00	/* 接收指令正常 */
#define RECEIVE_ABNORMAL    0xff	/* 接收指令异常 */
#define TIMEOUT    0xfe	/* 执行超时 */



void RS232_UartRxPkg_Init(void);
void Uart2RecvProcess(void);
void Uart_BspWrite(UART_HandleTypeDef* uart, uint8_t *pu8TxBuf, uint32_t u32WriteBytes);
#endif
