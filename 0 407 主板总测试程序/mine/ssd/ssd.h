#ifndef __SSD_H
#define __SSD_H
#include "sys.h"

//LED端口定义
#define RED1 		PAout(8)	
#define YELLOW1 PAout(15)		 
#define GREEN1  PDout(0)	

#define RED2 		PDout(1)		
#define YELLOW2 PDout(3)	
#define GREEN2  PDout(4)		

void SSD_Init(void);//初始化	
void ssd0_sta(u8 sta);
void ssd_sta(u8 sta);//三色灯各个状态函数
#endif
