#include "kettlescan.h"

/**
  * @brief ˮ����⺯��
  * @param 
  * @retval 
  */    
	
/*
SENSOR_OUT2 //�������ƿ��
SENSOR_OUT1 //����Һλ

DET_6 //�������ƿ��
DET_5 //����Һλ

LED_8_H //�ҵ��ø�
LED_8_L //�õ�
LED_7_H //����ø�
LED_7_L //�õ�

det5 det6 sen2 sen1

*/

void Kettle_Scan_Level(void)//����Һλ
{
#if 1	
		if(1==DET_5)//����ҵ�Һλ
		{
			LED_8_H;
		}
		if(0==DET_5)
		{
			LED_8_L;
		}
		
		if(1==SENSOR_OUT1)//������Һλ
		{
			LED_7_H;
		}
		
		if(0==SENSOR_OUT1)
		{
			LED_7_L;
		}
#endif				
}

void Kettle_Scan_Kettle(void)//�������ƿ��
{
#if 0	
	if(1==DET_6)//�������ƿ��
		{
			LED_7_H;//���
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

















