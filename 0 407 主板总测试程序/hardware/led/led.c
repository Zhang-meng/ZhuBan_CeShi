#include "led.h" 
	    
//LED IO��ʼ��
void LED_Init(void)
{    	 
		GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��

		//GPIOB8,9��ʼ������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;//LED0��LED1��ӦIO��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
		//GPIOE8,9��ʼ������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//LED0��LED1��ӦIO��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO

		LED1=1;
		LED2=1;
		LED3=1;
		LED4=1;
}






