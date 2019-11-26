/******************************************************************************/
#ifndef __BOARD_BSPAPI_CRC8__
#define __BOARD_BSPAPI_CRC8__
/******************************************************************************/
#include <stdint.h>

uint8_t Crc8_Calc(const uint8_t *p, uint16_t len);

// 下面函数是对CRC8进行分段计算采用的函数，前面的计算需要调用Crc8_Calc_wInitVal进行全部计算后，在采用Crc8_Calc_wInitVal_GetResult函数得到最终的8bits的CRC8值
uint16_t Crc8_Calc_wInitVal(const uint8_t *p, uint16_t len, uint16_t CrcInitVal);
uint8_t Crc8_Calc_wInitVal_GetResult(uint16_t crc);

/******************************************************************************/
#endif
/******************************************************************************/

