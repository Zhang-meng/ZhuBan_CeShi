#ifndef __OUTPUT_H
#define __OUTPUT_H
#include "sys.h"

#define BEEP PAout(3)	// DS0

#define OUTPUT1 PDout(4)	// DS0
#define OUTPUT2 PDout(3)	// DS1
#define OUTPUT3 PDout(1)	// DS0
#define OUTPUT4 PDout(0)	// DS1	 
#define OUTPUT5 PAout(15)	// DS1
#define OUTPUT6 PAout(8)	// DS1
#define OUTPUT7 PBout(10)	// DS1
#define OUTPUT8 PBout(0)	// DS1
#define OUTPUT9 PCout(5)	// DS1
#define OUTPUT10 PCout(4)	// DS1


//D 1/3/4
//A 8/15 D 0
//B 10
//C 4 5 B 0

void OUTPUT_Init(void);//≥ı ºªØ		 				    
#endif
