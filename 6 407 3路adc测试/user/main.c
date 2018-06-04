#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"


//ALIENTEK ̽����STM32F407������ ʵ��18
//ADCģ��ת��ʵ��-�⺯���汾  
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

u16 power=0,dwq1=0,dwq2=0;
float dw2=0;
float temp=0;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(9600);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
	Adc_Init();         //��ʼ��ADC   
	while(1)
	{ 
		power=Get_Adc_Average(ADC_Channel_11,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
		temp=(float)power*(3.3/4096.0);
		temp=11*temp;
		printf("power=%.3f\t",temp);
		
		dwq1=Get_Adc_Average(ADC_Channel_12,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
		printf("dwq1=%d\t",dwq1);
		
		dwq2=Get_Adc_Average(ADC_Channel_13,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
		printf("dwq2=%d\r\n",dwq2);
		delay_ms(1000);	
	}
}



