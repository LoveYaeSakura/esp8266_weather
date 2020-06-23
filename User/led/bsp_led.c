#include "./led/bsp_led.h"

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//��һ�����������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|LED2_GPIO_CLK, ENABLE);
	
	//�ڶ��������������ʼ���ṹ��
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	//�����������������ʼ�������������úõĽṹ���Աд���Ĵ�������
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN; 
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
}
