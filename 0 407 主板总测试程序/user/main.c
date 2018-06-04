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

#if 1//��������Ķ��忪ʼ

//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//�������ȼ�
#define Task1_TASK_PRIO		 4
//�����ջ��С	
#define Task1_STK_SIZE 		 128
//������ƿ�
OS_TCB Task1_TaskTCB;
//�����ջ	
__align(8) CPU_STK Task1_TASK_STK[Task1_STK_SIZE];
void Task1_task(void *p_arg);

//�������ȼ�
#define Task2_TASK_PRIO		 5
//�����ջ��С	
#define Task2_STK_SIZE 		 128
//������ƿ�
OS_TCB Task2_TaskTCB;
//�����ջ	
__align(8) CPU_STK Task2_TASK_STK[Task2_STK_SIZE];
void Task2_task(void *p_arg);

//�������ȼ�
#define Task3_TASK_PRIO		 6
//�����ջ��С	
#define Task3_STK_SIZE 		 128
//������ƿ�
OS_TCB Task3_TaskTCB;
//�����ջ	
__align(8) CPU_STK Task3_TASK_STK[Task3_STK_SIZE];
void Task3_task(void *p_arg);


//�������ȼ�
#define Task4_TASK_PRIO		7
//�����ջ��С	
#define Task4_STK_SIZE 		128
//������ƿ�
OS_TCB Task4_TaskTCB;
//�����ջ	
CPU_STK Task4_TASK_STK[Task4_STK_SIZE];
//������
void Task4_task(void *p_arg);

//�������ȼ�
#define Task5_TASK_PRIO		 8
//�����ջ��С	
#define Task5_STK_SIZE 		 128
//������ƿ�
OS_TCB Task5_TaskTCB;
//�����ջ	
__align(8) CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
void Task5_task(void *p_arg);

//�������ȼ�
#define Task6_TASK_PRIO		 9
//�����ջ��С	
#define Task6_STK_SIZE 		 128
//������ƿ�
OS_TCB Task6_TaskTCB;
//�����ջ	
__align(8) CPU_STK Task6_TASK_STK[Task6_STK_SIZE];
void Task6_task(void *p_arg);

#endif



u16 power_count=0,dwq1_count=0,dwq2_count=0;//������·ADC�ɼ��ı����ֱ��ǵ�Դ����λ��1����λ��2
float powerV=0.0,dwq1V=0,dwq2V=0;//����ĵ�ѹֵ

CanRxMsg can1_key,can2_key;
u8 can1_buf[8]={0},can2_buf[8]={0};

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  															//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�жϷ�������
	
	LED_Init();         														//LED��ʼ��
	BEEP_Init();																		//�������˿ڳ�ʼ��
	INPUT_Init();
	OUTPUT_Init();
	Adc_Init();         														//��ʼ��ADC
	TLC5620_Init();																	//��ʼ��	DAC
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN1��ʼ����ͨģʽ,������500Kbps    
 	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN2��ʼ����ͨģʽ,������500Kbps
	uart_init(9600);  															//����1��ʼ��
	uart6_init(9600);  															//����6��ʼ��

	Control_Init();																//��������źų�ʼ��
	PWM_Init(TIM4,1,10000,0);											//���PWM�˿�1��ʼ��
	PWM_Init(TIM4,2,10000,0);											//���PWM�˿�2��ʼ��
	PWM_Init(TIM4,3,10000,0);											//���PWM�˿�3��ʼ��
	PWM_Init(TIM4,4,10000,0);											//���PWM�˿�4��ʼ��
	
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,					//������ƿ�	
				 (CPU_CHAR	* )"start task", 							//��������	
                 (OS_TASK_PTR )start_task, 				//������	
                 (void		* )0,										//���ݸ��������Ĳ���	
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�	
                 (CPU_STK   * )&START_TASK_STK[0],//�����ջ����ַ	
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ	
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С	
                 (OS_MSG_QTY  )0,									//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ	
                 (OS_TICK	  )0,										//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�	
                 (void   	* )0,										//�û�����Ĵ洢��	
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);								//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
								 
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//�����ٽ���
#if 1	
	
		//����Task1����
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
								 
	//����Task2����
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

	//����Task3����
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

	
	//����Task4����
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
			
	//����Task5����
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
		
	//����Task6����
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
								 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�����ٽ���
}


//Task1����
void Task1_task(void *p_arg)
{
	u8 t1=0,num=0,num1=0;
	p_arg = p_arg;
	LED2=0;
	LED3=0;
	LED4=0;
	while(1)
	{	
		/*****************�ĸ�LEDָʾ��******************/
		if(t1==20)
		{
				LED1=~LED1;
				
				printf("�������USART6��ӡTask1���ַ�\r\n");
				t1=0;
		}
		/****************20������ڵĲ���****************/
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
		/*****************10������ڲ���*****************/
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
		/****************���PWM�����źŲ���*************/
		if(num1==100)
		{
				Change_IO(0);//�ĸ�����ĸ��������źŸ�ֵΪ0
				PWM_val(TIM4,1,500);
				PWM_val(TIM4,2,500);
				PWM_val(TIM4,3,500);
				PWM_val(TIM4,4,500);
		}
		else if(num1==200)
		{
				Change_IO(1);//�ĸ�����ĸ��������źŸ�ֵΪ1
				PWM_val(TIM4,1,900);
				PWM_val(TIM4,2,900);
				PWM_val(TIM4,3,900);
				PWM_val(TIM4,4,900);
				num1=0;
		}
		
		
		/****************��·DAC���Ƶ�ѹ����*************/
		TLC5620_OUT(1,1.4);
		TLC5620_OUT(2,2.5);
		TLC5620_OUT(3,3.6);
		TLC5620_OUT(4,4.7);
		
		t1++;//�����ĸ�LED����ʱ��
		num++;//����10������ڲ���ʱ��
		num1++;//����PWM�͵�������ź�����ڲ���ʱ��

		osdelay_ms(20); 
	}
}
//Task2����
void Task2_task(void *p_arg)
{
	u8 num2=0;
	p_arg = p_arg;
	while(1)
	{	
		/******************��·ADC�źŲ���***************/
		power_count=Get_Adc_Average(ADC_Channel_11,10);//��ȡͨ��11��ת��ֵ��20��ȡƽ��
		powerV=(float)(power_count*3.3/4096.0);
		powerV=11*powerV;//���������ѹֵ
			
		dwq1_count=Get_Adc_Average(ADC_Channel_12,20);//��ȡͨ��12��ת��ֵ��20��ȡƽ��
		dwq1V=(float)(dwq1_count*3.3/4096.0);//��λ������1�ĵ�ѹ
		
		dwq2_count=Get_Adc_Average(ADC_Channel_13,20);//��ȡͨ��13��ת��ֵ��20��ȡƽ��
		dwq2V=(float)(dwq2_count*3.3/4096.0);//��λ������2�ĵ�ѹ
		if(num2==2)
		{
			printf("powerV=%.3f\t",powerV);
			osdelay_ms(200); 
			printf("dwq1V=%.3f\t",dwq1V);
			osdelay_ms(200); 
			printf("dwq2V=%.3f\r\n",dwq2V);
			num2=0;
		}
		num2++;//ADC�Ĵ�ӡʱ��
		osdelay_ms(20); 
	}
}
//Task3����
void Task3_task(void *p_arg)
{
	u8 t=0;
	p_arg = p_arg;
	while(1)
	{	
		can1_key=CAN1_Receive_Msg(can1_buf);//CAN1�������ݺ���
		can2_key=CAN2_Receive_Msg(can2_buf);//CAN2�������ݺ���
		
		if(can1_key.StdId==1&&can1_key.DLC)//��IDΪ1���豸���ղ���������
		{		
			LED2=~LED2;
		}
		if(can2_key.StdId==2&&can2_key.DLC)//��IDΪ2���豸���ղ���������
		{		
			LED4=~LED4;	
		}
		if(t==100)
		{
			CAN1_Send_Msg(can1_buf,8);//CAN1����8���ֽ�
			CAN2_Send_Msg(can2_buf,8);//CAN2����8���ֽ�
			t=0;
		}	 
		t++;
		osdelay_ms(20); 
	}
}
//Task4����
void Task4_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{

		osdelay_ms(20); //��ʱ20ms
	}
}

//Task5����
void Task5_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)																	
	{    

		osdelay_ms(20);	
	}
}
//Task6����
void Task6_task(void *p_arg)
{
	p_arg = p_arg;
	while(1)
	{	
		osdelay_ms(20); 
	}
}



