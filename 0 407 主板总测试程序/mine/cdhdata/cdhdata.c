#include "CDHdata.h"

void CDH_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//前两个磁导航的端口初始化
 	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//


	//后两个磁导航的端口初始化
 	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4| GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOF, &GPIO_InitStructure);//
//	
//	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
}

u8 CDH_read_datan(u8 CDH_num)
{
	u8 n=0;
	switch(CDH_num)
	{
		case 1:
					n<<=1;
					n=n|PEin(3);
					n<<=1;
					n=n|PEin(2);
					n<<=1;
					n=n|PEin(5);
					n<<=1;
					n=n|PEin(4);
					n<<=1;
					n=n|PCin(13);
					n<<=1;
					n=n|PEin(6);
					n<<=1;
					n=n|PFin(1);
					n<<=1;
					n=n|PFin(0);
					break;
		case 2:
					n<<=1;
					n=n|PFin(3);
					n<<=1;
					n=n|PFin(2);
					n<<=1;
					n=n|PFin(5);
					n<<=1;
					n=n|PFin(4);
					n<<=1;
					n=n|PFin(7);
					n<<=1;
					n=n|PFin(6);
					n<<=1;
					n=n|PFin(9);
					n<<=1;
					n=n|PFin(8);
					break;
		case 3:
					n<<=1;
					n=n|PCin(0);
					n<<=1;
					n=n|PFin(10);
					n<<=1;
					n=n|PAin(5);
					n<<=1;
					n=n|PAin(4);
					n<<=1;
					n=n|PAin(7);
					n<<=1;
					n=n|PAin(6);
					n<<=1;
					n=n|PCin(5);
					n<<=1;
					n=n|PCin(4);
					break;
		case 4:
					n<<=1;
					n=n|PBin(1);
					n<<=1;
					n=n|PBin(0);
					n<<=1;
					n=n|PFin(12);
					n<<=1;
					n=n|PFin(11);
					n<<=1;
					n=n|PFin(14);
					n<<=1;
					n=n|PFin(13);
					n<<=1;
					n=n|PGin(0);
					n<<=1;
					n=n|PFin(15);
					break;
	}
	return n;
}
u8 CDH_read_dataa(u8 CDH_num)
{
	u8 n=0,a=0;
	switch(CDH_num)
	{
		case 1:
					n<<=1;
					n=n|PEin(3);
					n<<=1;
					n=n|PEin(2);
					n<<=1;
					n=n|PEin(5);
					n<<=1;
					n=n|PEin(4);
					n<<=1;
					n=n|PCin(13);
					n<<=1;
					n=n|PEin(6);
					n<<=1;
					n=n|PFin(1);
					n<<=1;
					n=n|PFin(0);
		
					switch(n)
					{
						case 0xff: a=0; break;
						case 0xfe: a=1; break;
						case 0xfc: a=2; break;
						case 0xf8: a=3; break;
						case 0xf0: a=4; break;
						case 0xe0: a=5; break;
						case 0xe1: a=6; break;
						case 0xc1: a=7; break;
						
						case 0xc3: a=8; break;
						case 0x83: a=9; break;
						case 0x87: a=10;break;
						case 0x07: a=11;break;
						case 0x0f: a=12;break;
						case 0x1f: a=13;break;
						case 0x3f: a=14;break;
						case 0x7f: a=15;break;
						
						default :	 a=0; break;
		
					}
					break;
		case 2:
					n<<=1;
					n=n|PFin(3);
					n<<=1;
					n=n|PFin(2);
					n<<=1;
					n=n|PFin(5);
					n<<=1;
					n=n|PFin(4);
					n<<=1;
					n=n|PFin(7);
					n<<=1;
					n=n|PFin(6);
					n<<=1;
					n=n|PFin(9);
					n<<=1;
					n=n|PFin(8);
					
					switch(n)
					{
						case 0xff: a=0; break;
						case 0xfe: a=1; break;
						case 0xfc: a=2; break;
						case 0xf8: a=3; break;
						case 0xf0: a=4; break;
						case 0xe0: a=5; break;
						case 0xe1: a=6; break;
						case 0xc1: a=7; break;
						
						case 0xc3: a=8; break;
						case 0x83: a=9; break;
						case 0x87: a=10;break;
						case 0x07: a=11;break;
						case 0x0f: a=12;break;
						case 0x1f: a=13;break;
						case 0x3f: a=14;break;
						case 0x7f: a=15;break;
						
						default :	 a=0; break;
					}
					break;
		case 3:
					n<<=1;
					n=n|PCin(0);
					n<<=1;
					n=n|PFin(10);
					n<<=1;
					n=n|PAin(5);
					n<<=1;
					n=n|PAin(4);
					n<<=1;
					n=n|PAin(7);
					n<<=1;
					n=n|PAin(6);
					n<<=1;
					n=n|PCin(5);
					n<<=1;
					n=n|PCin(4);
				
					switch(n)
					{
						case 0xff: a=0; break;
						case 0xfe: a=1; break;
						case 0xfc: a=2; break;
						case 0xf8: a=3; break;
						case 0xf0: a=4; break;
						case 0xe0: a=5; break;
						case 0xe1: a=6; break;
						case 0xc1: a=7; break;
						
						case 0xc3: a=8; break;
						case 0x83: a=9; break;
						case 0x87: a=10;break;
						case 0x07: a=11;break;
						case 0x0f: a=12;break;
						case 0x1f: a=13;break;
						case 0x3f: a=14;break;
						case 0x7f: a=15;break;
						
						default :	 a=0; break;
					}
					break;
		case 4:
					n<<=1;
					n=n|PBin(1);
					n<<=1;
					n=n|PBin(0);
					n<<=1;
					n=n|PFin(12);
					n<<=1;
					n=n|PFin(11);
					n<<=1;
					n=n|PFin(14);
					n<<=1;
					n=n|PFin(13);
					n<<=1;
					n=n|PGin(0);
					n<<=1;
					n=n|PFin(15);
		
					switch(n)
					{
						case 0xff: a=0; break;
						case 0xfe: a=1; break;
						case 0xfc: a=2; break;
						case 0xf8: a=3; break;
						case 0xf0: a=4; break;
						case 0xe0: a=5; break;
						case 0xe1: a=6; break;
						case 0xc1: a=7; break;
						
						case 0xc3: a=8; break;
						case 0x83: a=9; break;
						case 0x87: a=10;break;
						case 0x07: a=11;break;
						case 0x0f: a=12;break;
						case 0x1f: a=13;break;
						case 0x3f: a=14;break;
						case 0x7f: a=15;break;
						
						default :	 a=0; break;
						
					}
					break;
	}		
	return a;
}
