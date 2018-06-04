#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/6/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


#define EN1 PBout(3)	// 电机1使能
#define FR1 PGout(15)	// 电机1反向
#define BK1 PFout(0)  // 电机1刹车

#define EN2 PGout(14) // 电机2使能
#define FR2 PGout(13) // 电机2反向
#define BK2 PFout(1)  // 电机2刹车
											
#define EN3 PBout(7)  // 电机3使能
#define FR3 PBout(4)  // 电机3反向
#define BK3 PFout(2)  // 电机3刹车
											
#define EN4 PGout(11) // 电机4使能
#define FR4 PGout(10) // 电机4反向
#define BK4 PFout(3)  // 电机4刹车


void Control_Init(void);
void PWM_Init(TIM_TypeDef* TIMx,u16 x,u16 arr,u16 val);//PWM初始化函数
void PWM_val(TIM_TypeDef* TIMx,u16 x,u16 val);//更改占空比函数
void Change_IO(u8 num);//PWM测试用的切换函数

#endif
