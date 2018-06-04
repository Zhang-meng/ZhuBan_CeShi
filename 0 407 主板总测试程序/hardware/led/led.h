#ifndef __LED_H
#define __LED_H
#include "sys.h"


//LED端口定义
#define LED1 PBout(8)	// DS0
#define LED2 PBout(9)	// DS1
#define LED3 PEout(0)	// DS0
#define LED4 PEout(1)	// DS1	 

void LED_Init(void);//初始化		 

#endif

