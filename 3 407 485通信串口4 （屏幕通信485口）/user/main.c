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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);   //初始化延时函数
	//uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
	KEY_Init(); 				//按键初始化  
	RS485_Init(9600);		//初始化RS485串口2

	while(1)
	{
		RS485_Receive_Data(rs485buf,&key);
		if(key)//接收到有数据
		{
			if(key>10)key=10;		//最大是5个数据.
 			for(i=0;i<key;i++);//显示数据
			RS485_Send_Data(rs485buf,key);
		}
		t++; 
		delay_ms(10);
		if(t==20)
		{
			RS485_Send_Data(rs485buf,10);//发送5个字节 
			LED0=!LED0;//提示系统正在运行	
			t=0;
		}		   
	}   
}
