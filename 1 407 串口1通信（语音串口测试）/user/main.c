#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "xf.h"


int main(void)
{ 
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(9600);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	while(1)
	{
		LED1=0;
		LED2=0;
		LED3=0;
		LED4=0;
		speek("���Գɹ���");
		delay_ms(1000);
		delay_ms(1000);
		LED1=1;
		LED2=1;
		LED3=1;
		LED4=1;
		delay_ms(1000);

	}
}

