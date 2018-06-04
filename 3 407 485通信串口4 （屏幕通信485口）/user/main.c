#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "rs485.h"

int main(void)
{ 
	u8 key;
	u8 i=0,t=0;
	u8 rs485buf[10]={'a','c','b','c','c'}; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);   //��ʼ����ʱ����
	//uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
	KEY_Init(); 				//������ʼ��  
	RS485_Init(9600);		//��ʼ��RS485����2

	while(1)
	{
		RS485_Receive_Data(rs485buf,&key);
		if(key)//���յ�������
		{
			if(key>10)key=10;		//�����5������.
 			for(i=0;i<key;i++);//��ʾ����
			RS485_Send_Data(rs485buf,key);
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			RS485_Send_Data(rs485buf,10);//����5���ֽ� 
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
		}		   
	}   
}
