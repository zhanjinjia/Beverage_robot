#include "armcontrol.h"

/**
  * @brief �ֱۿ��ƺ���
  * @param 
  * @retval 
  */    
	
/*

*/

void Armcontrol_Left(void)
{
	int count_arm=0;
	while(1)
	{
	HAL_Delay(1000);
	ARM_CONT_LEFT_L;
	HAL_Delay(2000);
	ARM_CONT_LEFT_H;
	HAL_Delay(10000);
	printf("����ִ�д���%d\r\n",count_arm++);	
	if(1==ARM_LEFT_BACK)
	{
		printf("��⵽ֹͣ�ź�\r\n");
		ARM_CONT_LEFT_L;
		HAL_Delay(2000);
	}
	}
	
}

void Armcontrol_Right(void)
{
	int count_arm=0;
	while(1)
	{
	HAL_Delay(1000);
	ARM_CONT_RIGHT_L;
	HAL_Delay(2000);
	ARM_CONT_RIGHT_H;
	HAL_Delay(10000);
	printf("����ִ�д���%d\r\n",count_arm++);	
	if(1==ARM_RIGHT_BACK)
	{
		printf("��⵽ֹͣ�ź�\r\n");
		ARM_CONT_RIGHT_L;
		HAL_Delay(2000);
	}
	}
	
}















