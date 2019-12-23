#include "kettlescan.h"

/**
  * @brief 水壶检测函数
  * @param 
  * @retval 
  */    
	
/*
SENSOR_OUT2 //检测有无瓶子
SENSOR_OUT1 //检测低液位

DET_6 //检测有无瓶子
DET_5 //检测低液位

LED_8_H //右灯置高
LED_8_L //置低
LED_7_H //左灯置高
LED_7_L //置低

det5 det6 sen2 sen1

*/

void Kettle_Scan_Level(void)//检测低液位
{
#if 1	
		if(1==DET_5)//检测右低液位
		{
			LED_8_H;
		}
		if(0==DET_5)
		{
			LED_8_L;
		}
		
		if(1==SENSOR_OUT1)//检测左低液位
		{
			LED_7_H;
		}
		
		if(0==SENSOR_OUT1)
		{
			LED_7_L;
		}
#endif				
}

void Kettle_Scan_Kettle(void)//检测有无瓶子
{
#if 0	
	if(1==DET_6)//检测有无瓶子
		{
			LED_7_H;//左灯
		}
		if(0==DET_6)
		{
			LED_7_L;
		}
	
		if(1==SENSOR_OUT2)
		{
			LED_8_H;
		}
		
		if(0==SENSOR_OUT2)
		{
			LED_8_L;
		}
#endif		
}

















