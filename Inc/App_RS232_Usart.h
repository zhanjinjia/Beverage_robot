/******************************************************************************/
#ifndef __APP_RS232_USART__
#define __APP_RS232_USART__
/******************************************************************************/
#include <stdint.h>




// 调试定义
#if 0
    #define RS232_Usart_PRINTF   printf
#else
    #define RS232_Usart_PRINTF(...);
#endif

// 串口定义
#define RS232_UART_NO               2   // 串口通道2

#define FRAME_START		(0X5A)	/* 帧起始 */

#define CMD_CONN     0x01	/* 握手 */
#define CMD_OPEN     0x02	/* 开盖 */
#define CMD_CLOSE    0x03	/* 关盖 */
#define CMD_READ_STATUS    0x04	/* 读盖子状态 */
#define CMD_READ_SENSOR    0x05	/* 读光电传感器值 */
#define CMD_READ_WEIGHT    0x06	/* 读称重值 */
#define CMD_WEIGHT_CALIBRATION    0x07	/* 称重传感器校准(方法) */
#define CMD_WEIGHT_CALIBRATION1    0x08	/* 称重传感器校准(方法2) */
#define CMD_START_PWM_CALIBRATION    0x09	/* 起始位置校准 */
#define CMD_STOP_PWM_CALIBRATION    0x0A	/* 终止位置校准 */
#define CMD_PWM_SAVE	0x0B	/* 保存PWM值 */
#define CMD_READ_PWM	0x0C	/* 读取实时PWM值 */
#define CMD_SET_NRF_ADDR	0x0D	/* 上位机发nRF24L01的物理接收地址给下位机 */
#define CMD_READ_NRF_ADDR	0x0E	/*上位机读取nRF24L01的物理接收地址 */
#define CMD_RETURN_BUTTON_PRESS 	0x0F	/*下位机接收到按钮按下后返回给上位机 */

extern uint8_t ButtonPressSuccess;
void RS232_UartRxPkg_Init(void);
void Uart1RecvProcess(void);

#endif
