#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define LED1 PBout(8)	// DS0
#define LED2 PBout(9)	// DS1
#define LED3 PEout(0)	// DS0
#define LED4 PEout(1)	// DS1	 
#define LED5 PEout(2)	// DS1
#define LED6 PEout(3)	// DS1

void LED_Init(void);//��ʼ��		 				    
#endif
