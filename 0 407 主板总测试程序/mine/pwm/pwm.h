#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


#define EN1 PBout(3)	// ���1ʹ��
#define FR1 PGout(15)	// ���1����
#define BK1 PFout(0)  // ���1ɲ��

#define EN2 PGout(14) // ���2ʹ��
#define FR2 PGout(13) // ���2����
#define BK2 PFout(1)  // ���2ɲ��
											
#define EN3 PBout(7)  // ���3ʹ��
#define FR3 PBout(4)  // ���3����
#define BK3 PFout(2)  // ���3ɲ��
											
#define EN4 PGout(11) // ���4ʹ��
#define FR4 PGout(10) // ���4����
#define BK4 PFout(3)  // ���4ɲ��


void Control_Init(void);
void PWM_Init(TIM_TypeDef* TIMx,u16 x,u16 arr,u16 val);//PWM��ʼ������
void PWM_val(TIM_TypeDef* TIMx,u16 x,u16 val);//����ռ�ձȺ���
void Change_IO(u8 num);//PWM�����õ��л�����

#endif
