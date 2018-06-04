#include "control.h" 
#include "pwm.h"

//麦克纳木轮车型的方向控制函数
void lun1zheng()
{
	EN1=0;
	FR1=1;
	BK1=1;
}
void lun2zheng()
{
	EN2=0;
	FR2=1;
	BK2=1;
}
void lun3zheng()
{
	EN3=0;
	FR3=1;
	BK3=1;
}
void lun4zheng()
{
	EN4=0;
	FR4=1;
	BK4=1;
}
void lun1fan()
{
	EN1=0;
	FR1=0;
	BK1=1;
}
void lun2fan()
{
	EN2=0;
	FR2=0;
	BK2=1;
}
void lun3fan()
{
	EN3=0;
	FR3=0;
	BK3=1;
}
void lun4fan()
{
	EN4=0;
	FR4=0;
	BK4=1;
}
void lun1stop()
{
	EN1=1;
	FR1=1;
	BK1=1;
}
void lun2stop()
{
	EN2=1;
	FR2=1;
	BK2=1;
}
void lun3stop()
{
	EN3=1;
	FR3=1;
	BK3=1;
}
void lun4stop()
{
	EN4=1;
	FR4=1;
	BK4=1;
}
void qianjin()
{
	lun1zheng();
	lun2zheng();
	lun3zheng();
	lun4zheng();
}

void houtui()
{
	lun1fan();
	lun2fan();
	lun3fan();
	lun4fan();
}
void tingzhi()
{
	lun1stop();
	lun2stop();
	lun3stop();
	lun4stop();
}
void zuoyi()
{
	lun1zheng();
	lun2fan();
	lun3zheng();
	lun4fan();
}
void youyi()
{
	lun1fan();
	lun2zheng();
	lun3fan();
	lun4zheng();
}
void zuoshang()
{
	lun1zheng();
	lun2stop();
	lun3zheng();
	lun4stop();
}
void youshang()
{
	lun1stop();
	lun2zheng();
	lun3stop();
	lun4zheng();
}
void zuoxia()
{
	lun1stop();
	lun2fan();
	lun3stop();
	lun4fan();		
}
void youxia()
{
	lun1fan();
	lun2stop();
	lun3fan();
	lun4stop();
}
void zuoxuan()
{
	lun1zheng();
	lun2fan();
	lun3fan();
	lun4zheng();
}
void youxuan()
{
	lun1fan();
	lun2zheng();
	lun3zheng();
	lun4fan();
}
