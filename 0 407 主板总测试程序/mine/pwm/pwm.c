#include "pwm.h"
#include "led.h"
#include "usart.h"
 
#define RRECISION 1000

u16 arr1,val1,val2;

//电机控制信号端口初始化

void Control_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

/********************DJ1和DJ2的初始化配置开始**********************/
  //GPIOB3,4初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	//GPIOG13,14初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);				//初始化
	
	//GPIOF1,2初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);				//初始化
	
	GPIO_SetBits(GPIOB,GPIO_Pin_3);
	GPIO_SetBits(GPIOG,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_SetBits(GPIOF,GPIO_Pin_0 | GPIO_Pin_1);
/********************DJ1和DJ2的初始化配置结束**********************/


/********************DJ3和DJ4的初始化配置开始**********************/

  //GPIOB6,7初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	//GPIOG10,11初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);				//初始化
	
	//GPIOF3,4初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);				//初始化
	
	GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_7);
	GPIO_SetBits(GPIOG,GPIO_Pin_10 | GPIO_Pin_11);
	GPIO_SetBits(GPIOF,GPIO_Pin_2 | GPIO_Pin_3);

/********************DJ3和DJ4的初始化配置结束**********************/	

}


//函数描述:	PWM初始化函数
//TIMx:			包含TIM1、TIM8、TIM2、TIM3、TIM4、TIM5、TIM9、TIM10、TIM11、TIM12、TIM13、TIM14
//x:				在TIM2~TIM5可取值1~4，在TIM1和TIM8可取值1~7
//1、8、9、10、11挂在AHB2上其他都在AHB1上
//arr:			PWM频率
//val:			PWM占空比
void PWM_Init(TIM_TypeDef* TIMx,u16 x,u16 arr,u16 val)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	arr1=(u16)(1000000/arr-1);
	val1=(u16)(((arr1+1)*val)/RRECISION);
	
	if(TIMx==TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 3:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_TIM1);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 4:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	
	else if(TIMx==TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 3:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 4:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}	
	else if(TIMx==TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 3:
				{
					GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 4:
				{
					GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM4)
	{
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM2时钟使能    
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
//		
//		switch(x)
//			{
//				case 1:
//				{
//					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOF9
//					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
//					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
//				}break;
//				case 2:
//				{
//					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOF9
//					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
//					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
//				}break;
//				case 3:
//				{
//					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
//					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
//					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
//				}break;
//				case 4:
//				{
//					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
//					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
//					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
//				}break;
//			}
//			
//		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOF9复用为定时器14
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOF9复用为定时器14
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 3:
				{
					GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //GPIOF9复用为定时器14
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 4:
				{
					GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //GPIOF9复用为定时器14
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 3:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 4:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 3:
				{
					GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 4:
				{
					GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	
	else if(TIMx==TIM9)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM10)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM11)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM12)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
				}break;
				case 2:
				{
					GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM13)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	else if(TIMx==TIM14)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM2时钟使能    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
		
		switch(x)
			{
				case 1:
				{
					GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14);
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOF9
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
					GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
				}break;
			}
	}
	
	
	
	TIM_TimeBaseStructure.TIM_Period=arr1;   //自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler=83;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);//初始化定时器14
	
	//初始化TIMx Channex PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低

	switch(x)
			{
				case 1:
				{
					TIM_OC1Init(TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIMx OC1
					TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);  //使能TIMx在CCR1上的预装载寄存器		 
					TIM_ARRPreloadConfig(TIMx,ENABLE);//ARPE使能 			
					TIM_Cmd(TIMx, ENABLE);  //使能TIMx			
					TIM_SetCompare1(TIMx,val1);//占空比初始化
				}break;
				case 2:
				{
					TIM_OC2Init(TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
					TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器		 
					TIM_ARRPreloadConfig(TIMx,ENABLE);//ARPE使能 			
					TIM_Cmd(TIMx, ENABLE);  //使能TIM14				
					TIM_SetCompare2(TIMx,val1);
				}break;
				case 3:
				{
					TIM_OC3Init(TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
					TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器		 
					TIM_ARRPreloadConfig(TIMx,ENABLE);//ARPE使能 			
					TIM_Cmd(TIMx, ENABLE);  //使能TIM14				
					TIM_SetCompare3(TIMx,val1);
				}break;
				case 4:
				{
					TIM_OC4Init(TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
					TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器		 
					TIM_ARRPreloadConfig(TIMx,ENABLE);//ARPE使能 			
					TIM_Cmd(TIMx, ENABLE);  //使能TIM14				
					TIM_SetCompare4(TIMx,val1);
				}break;
			}
}

//函数描述:	PWM占空比调节函数
//TIMx:			包含TIM1、TIM8、TIM2、TIM3、TIM4、TIM5、TIM9、TIM10、TIM11、TIM12、TIM13、TIM14
//x:				在TIM2~TIM5可取值1~4，在TIM1和TIM8可取值1~7
//val:			PWM占空比
void PWM_val(TIM_TypeDef* TIMx,u16 x,u16 val)
{
	
	val2=(u16)(((arr1+1)*val)/RRECISION);
	switch(x)
	{
		case 1:
			TIM_SetCompare1(TIMx,val2);break;
		case 2:
			TIM_SetCompare2(TIMx,val2);break;
		case 3:
			TIM_SetCompare3(TIMx,val2);break;
		case 4:
			TIM_SetCompare4(TIMx,val2);break;
	}
}


void Change_IO(u8 num)//PWM测试用的切换函数
{
	EN1=num;
	FR1=num;
	BK1=num;
		
	EN2=num;
	FR2=num;
	BK2=num;
		
	EN3=num;
	FR3=num;
	BK3=num;
	
	EN4=num;
	FR4=num;
	BK4=num;	
	
}




