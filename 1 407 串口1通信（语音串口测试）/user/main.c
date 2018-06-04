#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "xf.h"


int main(void)
{ 
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(9600);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
	while(1)
	{
		LED1=0;
		LED2=0;
		LED3=0;
		LED4=0;
		speek("测试成功了");
		delay_ms(1000);
		delay_ms(1000);
		LED1=1;
		LED2=1;
		LED3=1;
		LED4=1;
		delay_ms(1000);

	}
}

