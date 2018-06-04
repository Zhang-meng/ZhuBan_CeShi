#ifndef __MYUART_H
#define __MYUART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART6_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART6_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART6_RX_BUF[USART6_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART6_RX_STA;         				//����״̬���	
void uart6_init(u32 bound);

#endif


