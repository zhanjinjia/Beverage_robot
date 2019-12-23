
/******************************************************************************/
#ifndef __GLOBAL_INCLUDE_H__
#define __GLOBAL_INCLUDE_H__
/******************************************************************************/

#include "stm32f4xx_hal.h"
#include "main.h"

/* RTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* C standard library includes. */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Hardware includes. */
//#include "Board_HardwareConfig.h"
#include "gpio.h"
//#include "bsp_usart.h"
#include "usart.h"
#include "tim.h"

#include "Board_BspApi_Crc8.h"
//#include "Board_BspApi_Crc16.h"


// App
#include "keyscan.h"
#include "App_RS232_Usart.h"
#include "kettlescan.h"
#include "armcontrol.h"



/******************************************************************************/
#endif
/******************************************************************************/

