#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"


//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本  
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

u16 power=0,dwq1=0,dwq2=0;
float dw2=0;
float temp=0;

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(9600);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
	Adc_Init();         //初始化ADC   
	while(1)
	{ 
		power=Get_Adc_Average(ADC_Channel_11,20);//获取通道5的转换值，20次取平均
		temp=(float)power*(3.3/4096.0);
		temp=11*temp;
		printf("power=%.3f\t",temp);
		
		dwq1=Get_Adc_Average(ADC_Channel_12,20);//获取通道5的转换值，20次取平均
		printf("dwq1=%d\t",dwq1);
		
		dwq2=Get_Adc_Average(ADC_Channel_13,20);//获取通道5的转换值，20次取平均
		printf("dwq2=%d\r\n",dwq2);
		delay_ms(1000);	
	}
}



