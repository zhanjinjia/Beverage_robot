#include "keyscan.h"

/**
  * @brief ����ɨ�躯��
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
		/* ����⵽����*/
		while(0 == DET_1 )
		{
			 HAL_Delay(500);
//			 //printf("��⵽����\r\n");
			 POWER_3_H;
			 if(1 == KEY_1)//���ݰ�ť������
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
	
			 if(1 == KEY_1)//���ݰ�ť������
			{
			 HAL_Delay(10);
//			 //printf("����ݰ�ť������\r\n");
			 POWER_3_H;
			}
	
			if(0== KEY_1)//���ݰ�ťδ������
			{
			 HAL_Delay(10);
//			 //printf("����ݰ�ťδ������\r\n");
			 POWER_3_L;
			}	
}
void KEY_Scan_Right(void)
{	
		/* ����⵽����*/
		while(0 == DET_2 )
		{
			 HAL_Delay(500);
//			 //printf("��⵽�ұ���\r\n");
			 POWER_4_H;
			 if(1 == KEY_2)//���ݰ�ť������
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
	
			if(1 == KEY_2)//���ݰ�ť������
			{
			 HAL_Delay(10);
			 //printf("�ҵ��ݰ�ť������\r\n");
			 POWER_4_H;
			}
	
			if(0== KEY_2)//���ݰ�ťδ������
			{
			 HAL_Delay(10);
			 //printf("�ҵ��ݰ�ťδ������\r\n");
			 POWER_4_L;
			}	
}
#elif   1 //��ͬ���Ƴ�ˮ
void KEY_Scan_Left(void)
{
		if(0 == DET_1 )//��⵽����
   {
     HAL_Delay(500);
		 //printf("��⵽����\r\n");
		 POWER_3_H;
   }else if(1 == KEY_1)//���ݰ�ť������
   {
     HAL_Delay(10);
		 //printf("����ݰ�ť������\r\n");
		 POWER_3_H;
		 HAL_Delay(10);
   }else if(0 == KEY_1&&1 == DET_1){//���ݰ�ťδ��������δ��⵽����
	   HAL_Delay(10);
		 //printf("����ݰ�ťδ��������δ��⵽����\r\n");
		 POWER_3_L;
	 }
}

void KEY_Scan_Right(void)
{
		if(0 == DET_2 )//��⵽����
   {
     HAL_Delay(500);
		 //printf("��⵽�ұ���\r\n");
		 POWER_4_H;
   }else if(1 == KEY_2)//���ݰ�ť������
   {
     HAL_Delay(10);
		 //printf("�ҵ��ݰ�ť������\r\n");
		 POWER_4_H;
		 HAL_Delay(10);
   }else if(0 == KEY_2&&1 == DET_2){//���ݰ�ťδ��������δ��⵽����
	   HAL_Delay(10);
		 //printf("�ҵ��ݰ�ťδ��������δ��⵽����\r\n");
		 POWER_4_L;
	 }
}
#elif   0
//ֻ�õ��ݰ���
void KEY_Scan_Left(void)
{
		if(1 == KEY_1)//���ݰ�ť������
   {
     HAL_Delay(10);
		 //printf("����ݰ�ť������\r\n");
		 POWER_3_H;
		 HAL_Delay(10);
   }
	 if(0 == KEY_1){//���ݰ�ťδ������
	   HAL_Delay(10);
		 //printf("����ݰ�ťδ������\r\n");
		 POWER_3_L;
	 }
}

void KEY_Scan_Right(void)
{
		if(1 == KEY_2)//���ݰ�ť������
   {
     HAL_Delay(10);
		 //printf("�ҵ��ݰ�ť������\r\n");
		 POWER_4_H;
		 HAL_Delay(10);
   }
	 if(0 == KEY_2){//���ݰ�ťδ��������δ��⵽����
	   HAL_Delay(10);
		 //printf("�ҵ��ݰ�ťδ��������δ��⵽����\r\n");
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








