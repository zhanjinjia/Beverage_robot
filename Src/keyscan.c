#include "keyscan.h"

/**
  * @brief 按键扫描函数
  * @param 
  * @retval 
  */    
	
/*
P15,P19-->P4
P20,P16-->P25
*/
#if 0
int Scan_Key_Flag=0;
void KEY_Scan_Left(void)
{	
		/* 光电检测到杯子*/
		while(0 == DET_1 )
		{
			 HAL_Delay(500);
//			 //printf("检测到左杯子\r\n");
			 POWER_3_H;
			 if(1 == KEY_1)//电容按钮被按下
			 {
				 Scan_Key_Flag=!Scan_Key_Flag;
			  }
				
			 if(Scan_Key_Flag)
			 {
					POWER_3_L;
			  }else{
					POWER_3_H;			
			 }
		}
					
			 if(1 == DET_1)
			 {
					 POWER_3_L;
			 }
	
			 if(1 == KEY_1)//电容按钮被按下
			{
			 HAL_Delay(10);
//			 //printf("左电容按钮被按下\r\n");
			 POWER_3_H;
			}
	
			if(0== KEY_1)//电容按钮未被按下
			{
			 HAL_Delay(10);
//			 //printf("左电容按钮未被按下\r\n");
			 POWER_3_L;
			}	
}
void KEY_Scan_Right(void)
{	
		/* 光电检测到杯子*/
		while(0 == DET_2 )
		{
			 HAL_Delay(500);
//			 //printf("检测到右杯子\r\n");
			 POWER_4_H;
			 if(1 == KEY_2)//电容按钮被按下
			 {
				 Scan_Key_Flag=!Scan_Key_Flag;
			  }
				
			 if(Scan_Key_Flag)
			 {
					POWER_4_L;
			  }else{
					POWER_4_H;			
			 }
		}
					
			 if(1 == DET_2)
			 {
					 POWER_4_L;
			 }
	
			if(1 == KEY_2)//电容按钮被按下
			{
			 HAL_Delay(10);
			 //printf("右电容按钮被按下\r\n");
			 POWER_4_H;
			}
	
			if(0== KEY_2)//电容按钮未被按下
			{
			 HAL_Delay(10);
			 //printf("右电容按钮未被按下\r\n");
			 POWER_4_L;
			}	
}
#elif   1 //共同控制出水
void KEY_Scan_Left(void)
{
		if(0 == DET_1 )//检测到杯子
   {
     HAL_Delay(500);
		 //printf("检测到左杯子\r\n");
		 POWER_3_H;
   }else if(1 == KEY_1)//电容按钮被按下
   {
     HAL_Delay(10);
		 //printf("左电容按钮被按下\r\n");
		 POWER_3_H;
		 HAL_Delay(10);
   }else if(0 == KEY_1&&1 == DET_1){//电容按钮未被按下且未检测到杯子
	   HAL_Delay(10);
		 //printf("左电容按钮未被按下且未检测到杯子\r\n");
		 POWER_3_L;
	 }
}

void KEY_Scan_Right(void)
{
		if(0 == DET_2 )//检测到杯子
   {
     HAL_Delay(500);
		 //printf("检测到右杯子\r\n");
		 POWER_4_H;
   }else if(1 == KEY_2)//电容按钮被按下
   {
     HAL_Delay(10);
		 //printf("右电容按钮被按下\r\n");
		 POWER_4_H;
		 HAL_Delay(10);
   }else if(0 == KEY_2&&1 == DET_2){//电容按钮未被按下且未检测到杯子
	   HAL_Delay(10);
		 //printf("右电容按钮未被按下且未检测到杯子\r\n");
		 POWER_4_L;
	 }
}
#elif   0
//只用电容按键
void KEY_Scan_Left(void)
{
		if(1 == KEY_1)//电容按钮被按下
   {
     HAL_Delay(10);
		 //printf("左电容按钮被按下\r\n");
		 POWER_3_H;
		 HAL_Delay(10);
   }
	 if(0 == KEY_1){//电容按钮未被按下
	   HAL_Delay(10);
		 //printf("左电容按钮未被按下\r\n");
		 POWER_3_L;
	 }
}

void KEY_Scan_Right(void)
{
		if(1 == KEY_2)//电容按钮被按下
   {
     HAL_Delay(10);
		 //printf("右电容按钮被按下\r\n");
		 POWER_4_H;
		 HAL_Delay(10);
   }
	 if(0 == KEY_2){//电容按钮未被按下且未检测到杯子
	   HAL_Delay(10);
		 //printf("右电容按钮未被按下且未检测到杯子\r\n");
		 POWER_4_L;
	 }
	 
}


#endif

void Ear_Scan_Left(void)
{
	if(0==KEY_3)
	{
		LED_8_L;
	}
	if(1==KEY_3)
	{
		LED_8_H;
	}
}

void Ear_Scan_Right(void)
{
	if(0==KEY_4)
	{
		LED_7_L;
	}
	if(1==KEY_4)
	{
		LED_7_H;
	}
	
}








