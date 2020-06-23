#include "./led/bsp_led.h"

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//第一步：打开外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|LED2_GPIO_CLK, ENABLE);
	
	//第二步：配置外设初始化结构体
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	//第三步：调用外设初始化函数，把配置好的结构体成员写到寄存器里面
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN; 
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
}
