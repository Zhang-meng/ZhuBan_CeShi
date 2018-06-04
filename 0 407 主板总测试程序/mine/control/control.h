#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

//麦克纳木轮车型的方向控制函数

void lun1zheng(void);//第1个轮子正转
void lun2zheng(void);//第2个轮子正转
void lun3zheng(void);//第3个轮子正转
void lun4zheng(void);//第4个轮子正转

void lun1fan(void);	 //第1个轮子反转
void lun2fan(void);  //第2个轮子反转
void lun3fan(void);  //第3个轮子反转
void lun4fan(void);  //第4个轮子反转

void lun1stop(void); //第1个轮子停止
void lun2stop(void); //第2个轮子停止
void lun3stop(void); //第3个轮子停止
void lun4stop(void); //第4个轮子停止

void qianjin(void);	 //车前进
void houtui(void);	 //车后退
void tingzhi(void);	 //车停止
void zuoyi(void);		 //车左移
void youyi(void);		 //车右移

void zuoshang(void); //车左上45°移动
void youshang(void); //车右上45°移动
void zuoxia(void);	 //车左下45°移动
void youxia(void);	 //车右下45°移动

void zuoxuan(void);	 //车左旋转
void youxuan(void);	 //车右旋转

#endif
