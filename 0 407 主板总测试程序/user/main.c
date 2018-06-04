#include "sys.h"
#include "delay.h"
#include "led.h"
#include "beep.h" 
#include "usart.h"
#include "myuart.h"	
#include "input.h"
#include "output.h" 
#include "pwm.h"
#include "adc.h"
#include "tlc5620.h"
#include "can.h"
#include "includes.h"
#include "os_app_hooks.h"

#if 1//各种任务的定义开始

//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define Task1_TASK_PRIO		 4
//任务堆栈大小	
#define Task1_STK_SIZE 		 128
//任务控制块
OS_TCB Task1_TaskTCB;
//任务堆栈	
__align(8) CPU_STK Task1_TASK_STK[Task1_STK_SIZE];
void Task1_task(void *p_arg);

//任务优先级
#define Task2_TASK_PRIO		 5
//任务堆栈大小	
#define Task2_STK_SIZE 		 128
//任务控制块
OS_TCB Task2_TaskTCB;
//任务堆栈	
__align(8) CPU_STK Task2_TASK_STK[Task2_STK_SIZE];
void Task2_task(void *p_arg);

//任务优先级
#define Task3_TASK_PRIO		 6
//任务堆栈大小	
#define Task3_STK_SIZE 		 128
//任务控制块
OS_TCB Task3_TaskTCB;
//任务堆栈	
__align(8) CPU_STK Task3_TASK_STK[Task3_STK_SIZE];
void Task3_task(void *p_arg);


//任务优先级
#define Task4_TASK_PRIO		7
//任务堆栈大小	
#define Task4_STK_SIZE 		128
//任务控制块
OS_TCB Task4_TaskTCB;
//任务堆栈	
CPU_STK Task4_TASK_STK[Task4_STK_SIZE];
//任务函数
void Task4_task(void *p_arg);

//任务优先级
#define Task5_TASK_PRIO		 8
//任务堆栈大小	
#define Task5_STK_SIZE 		 128
//任务控制块
OS_TCB Task5_TaskTCB;
//任务堆栈	
__align(8) CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
void Task5_task(void *p_arg);

//任务优先级
#define Task6_TASK_PRIO		 9
//任务堆栈大小	
#define Task6_STK_SIZE 		 128
//任务控制块
OS_TCB Task6_TaskTCB;
//任务堆栈	
__align(8) CPU_STK Task6_TASK_STK[Task6_STK_SIZE];
void Task6_task(void *p_arg);

#endif



u16 power_count=0,dwq1_count=0,dwq2_count=0;//定义三路ADC采集的变量分别是电源、电位器1、电位器2
float powerV=0.0,dwq1V=0,dwq2V=0;//具体的电压值

CanRxMsg can1_key,can2_key;
u8 can1_buf[8]={0},can2_buf[8]={0};

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  															//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组配置
	
	LED_Init();         														//LED初始化
	BEEP_Init();																		//蜂鸣器端口初始化
	INPUT_Init();
	OUTPUT_Init();
	Adc_Init();         														//初始化ADC
	TLC5620_Init();																	//初始化	DAC
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN1初始化普通模式,波特率500Kbps    
 	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN2初始化普通模式,波特率500Kbps
	uart_init(9600);  															//串口1初始化
	uart6_init(9600);  															//串口6初始化

	Control_Init();																//电机控制信号初始化
	PWM_Init(TIM4,1,10000,0);											//电机PWM端口1初始化
	PWM_Init(TIM4,2,10000,0);											//电机PWM端口2初始化
	PWM_Init(TIM4,3,10000,0);											//电机PWM端口3初始化
	PWM_Init(TIM4,4,10000,0);											//电机PWM端口4初始化
	
	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,					//任务控制块	
				 (CPU_CHAR	* )"start task", 							//任务名字	
                 (OS_TASK_PTR )start_task, 				//任务函数	
                 (void		* )0,										//传递给任务函数的参数	
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级	
                 (CPU_STK   * )&START_TASK_STK[0],//任务堆栈基地址	
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位	
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小	
                 (OS_MSG_QTY  )0,									//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息	
                 (OS_TICK	  )0,										//当使能时间片轮转时的时间片长度，为0时为默认长度，	
                 (void   	* )0,										//用户补充的存储区	
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);								//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
								 
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//进入临界区
#if 1	
	
		//创建Task1任务
	OSTaskCreate((OS_TCB 	* )&Task1_TaskTCB,		
				 (CPU_CHAR	* )"Task1 task", 		
                 (OS_TASK_PTR )Task1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Task1_TASK_PRIO,     
                 (CPU_STK   * )&Task1_TASK_STK[0],	
                 (CPU_STK_SIZE)Task1_STK_SIZE/10,	
                 (CPU_STK_SIZE)Task1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
								 
	//创建Task2任务
	OSTaskCreate((OS_TCB 	* )&Task2_TaskTCB,		
				 (CPU_CHAR	* )"Task2 task", 		
                 (OS_TASK_PTR )Task2_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Task2_TASK_PRIO,     
                 (CPU_STK   * )&Task2_TASK_STK[0],	
                 (CPU_STK_SIZE)Task2_STK_SIZE/10,	
                 (CPU_STK_SIZE)Task2_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		

	//创建Task3任务
	OSTaskCreate((OS_TCB 	* )&Task3_TaskTCB,		
				 (CPU_CHAR	* )"Task3 task", 		
                 (OS_TASK_PTR )Task3_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Task3_TASK_PRIO,     
                 (CPU_STK   * )&Task3_TASK_STK[0],	
                 (CPU_STK_SIZE)Task3_STK_SIZE/10,	
                 (CPU_STK_SIZE)Task3_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);									 

	
	//创建Task4任务
	OSTaskCreate((OS_TCB 	* )&Task4_TaskTCB,		
				 (CPU_CHAR	* )"Task4 task", 		
                 (OS_TASK_PTR )Task4_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Task4_TASK_PRIO,     
                 (CPU_STK   * )&Task4_TASK_STK[0],	
                 (CPU_STK_SIZE)Task4_STK_SIZE/10,	
                 (CPU_STK_SIZE)Task4_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
			
	//创建Task5任务
	OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,		
				 (CPU_CHAR	* )"Task5 task", 		
                 (OS_TASK_PTR )Task5_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Task5_TASK_PRIO,     
                 (CPU_STK   * )&Task5_TASK_STK[0],	
                 (CPU_STK_SIZE)Task5_STK_SIZE/10,	
                 (CPU_STK_SIZE)Task5_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
		
	//创建Task6任务
	OSTaskCreate((OS_TCB 	* )&Task6_TaskTCB,		
				 (CPU_CHAR	* )"Task6 task", 		
                 (OS_TASK_PTR )Task6_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Task6_TASK_PRIO,     
                 (CPU_STK   * )&Task6_TASK_STK[0],	
                 (CPU_STK_SIZE)Task6_STK_SIZE/10,	
                 (CPU_STK_SIZE)Task6_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	

#endif
								 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//进入临界区
}


//Task1任务
void Task1_task(void *p_arg)
{
	u8 t1=0,num=0,num1=0;
	p_arg = p_arg;
	LED2=0;
	LED3=0;
	LED4=0;
	while(1)
	{	
		/*****************四个LED指示灯******************/
		if(t1==20)
		{
				LED1=~LED1;
				
				printf("你好我是USART6打印Task1的字符\r\n");
				t1=0;
		}
		/****************20个输入口的测试****************/
		if(
			 INPUT1== 0||INPUT2== 0|| INPUT3== 0|| 
			 INPUT4== 0||INPUT5== 0|| INPUT6== 0||
			 INPUT7== 0||INPUT8== 0|| INPUT9== 0||
			 INPUT10==0||INPUT11==0|| INPUT12==0||
			 INPUT13==0||INPUT14==0|| INPUT15==0||
			 INPUT16==0||INPUT17==0|| INPUT18==0||
			 INPUT19==0||INPUT20==0)
		{
			BEEP=1;				
		}
		else
		{
			BEEP=0;				
		}
		/*****************10个输出口测试*****************/
		switch(num)
		{
			case 5:
				OUTPUT1=0;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 10:
				OUTPUT1=1;
				OUTPUT2=0;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 15:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=0;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 20:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=0;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 25:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=0; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 30:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=0; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 35:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=0;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 40:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=0; 
				OUTPUT9=1; 
				OUTPUT10=1;
				break;
			case 45:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=0; 
				OUTPUT10=1;
				break;
			case 50:
				OUTPUT1=1;
				OUTPUT2=1;
				OUTPUT3=1;
				OUTPUT4=1;
				OUTPUT5=1; 
				OUTPUT6=1; 
				OUTPUT7=1;
				OUTPUT8=1; 
				OUTPUT9=1; 
				OUTPUT10=0;
				num=0;
				break;
		}	
		/****************电机PWM控制信号测试*************/
		if(num1==100)
		{
				Change_IO(0);//四个电机的各个控制信号赋值为0
				PWM_val(TIM4,1,500);
				PWM_val(TIM4,2,500);
				PWM_val(TIM4,3,500);
				PWM_val(TIM4,4,500);
		}
		else if(num1==200)
		{
				Change_IO(1);//四个电机的各个控制信号赋值为1
				PWM_val(TIM4,1,900);
				PWM_val(TIM4,2,900);
				PWM_val(TIM4,3,900);
				PWM_val(TIM4,4,900);
				num1=0;
		}
		
		
		/****************四路DAC控制电压测试*************/
		TLC5620_OUT(1,1.4);
		TLC5620_OUT(2,2.5);
		TLC5620_OUT(3,3.6);
		TLC5620_OUT(4,4.7);
		
		t1++;//用于四个LED灯延时用
		num++;//用于10个输出口测试时用
		num1++;//用于PWM和电机控制信号输出口测试时用

		osdelay_ms(20); 
	}
}
//Task2任务
void Task2_task(void *p_arg)
{
	u8 num2=0;
	p_arg = p_arg;
	while(1)
	{	
		/******************三路ADC信号测试***************/
		power_count=Get_Adc_Average(ADC_Channel_11,10);//获取通道11的转换值，20次取平均
		powerV=(float)(power_count*3.3/4096.0);
		powerV=11*powerV;//板子输入电压值
			
		dwq1_count=Get_Adc_Average(ADC_Channel_12,20);//获取通道12的转换值，20次取平均
		dwq1V=(float)(dwq1_count*3.3/4096.0);//电位器输入1的电压
		
		dwq2_count=Get_Adc_Average(ADC_Channel_13,20);//获取通道13的转换值，20次取平均
		dwq2V=(float)(dwq2_count*3.3/4096.0);//电位器输入2的电压
		if(num2==2)
		{
			printf("powerV=%.3f\t",powerV);
			osdelay_ms(200); 
			printf("dwq1V=%.3f\t",dwq1V);
			osdelay_ms(200); 
			printf("dwq2V=%.3f\r\n",dwq2V);
			num2=0;
		}
		num2++;//ADC的打印时间
		osdelay_ms(20); 
	}
}
//Task3任务
void Task3_task(void *p_arg)
{
	u8 t=0;
	p_arg = p_arg;
	while(1)
	{	
		can1_key=CAN1_Receive_Msg(can1_buf);//CAN1接收数据函数
		can2_key=CAN2_Receive_Msg(can2_buf);//CAN2接收数据函数
		
		if(can1_key.StdId==1&&can1_key.DLC)//从ID为1的设备接收并且有数据
		{		
			LED2=~LED2;
		}
		if(can2_key.StdId==2&&can2_key.DLC)//从ID为2的设备接收并且有数据
		{		
			LED4=~LED4;	
		}
		if(t==100)
		{
			CAN1_Send_Msg(can1_buf,8);//CAN1发送8个字节
			CAN2_Send_Msg(can2_buf,8);//CAN2发送8个字节
			t=0;
		}	 
		t++;
		osdelay_ms(20); 
	}
}
//Task4任务
void Task4_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{

		osdelay_ms(20); //延时20ms
	}
}

//Task5任务
void Task5_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)																	
	{    

		osdelay_ms(20);	
	}
}
//Task6任务
void Task6_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{	
		osdelay_ms(20); 
	}
}



