#include "ssd.h" 
 
//LED IO��ʼ��
void SSD_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_15;								
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;													//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;												//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;													//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);																//��ʼ��GPIO
	
	//GPIOE0,E1��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;													//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;												//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;										//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;													//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);																//��ʼ��GPIO
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8 | GPIO_Pin_15);													//GPIOA8,A15���øߣ���ɫ����
	GPIO_SetBits(GPIOD,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4);//GPIOF9,F10���øߣ���ɫ����

}

void ssd0_sta(u8 sta)
{
	switch(sta)
	{
		case 0:
			RED1=1,YELLOW1=1,GREEN1=1;break;
		case 1:
			RED1=0,YELLOW1=1,GREEN1=1;break;
		case 2:
			RED1=1,YELLOW1=0,GREEN1=1;break;
		case 3:
			RED1=1,YELLOW1=1,GREEN1=0;break;
		case 4:
			RED1=0,YELLOW1=0,GREEN1=0;break;
	}
}

void ssd_sta(u8 sta)
{
	switch(sta)
	{
		case 0:
			RED2=1,YELLOW2=1,GREEN2=1;break;
		case 1:
			RED2=0,YELLOW2=1,GREEN2=1;break;
		case 2:
			RED2=1,YELLOW2=0,GREEN2=1;break;
		case 3:
			RED2=1,YELLOW2=1,GREEN2=0;break;
		case 4:
			RED2=0,YELLOW2=0,GREEN2=0;break;
		
	}
}






