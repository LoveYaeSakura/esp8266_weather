/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   WF-ESP8266 WiFi模块测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
	
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)   72M / (20000*72)
// PWM 信号的周期 T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)
	
/* ESP8266与stm32的连接：
ESP8266-01 :  stm32
3v3 :   3v3
GND :   GND
RX  :   PA2  //(Rx接stm32串口2的Tx口)
TX  ：  PA3  //(Tx接stm32串口2的Rx口)
EN  :		PA0  //(EN又叫片选接PA1口，可修改)
RST :		PA1	 //(RST接stm32的PA0口，可修改)

*/
#include "stm32f10x.h"
#include "bsp_gpio.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "wifi_config.h"
#include "wifi_function.h"
#include "bsp_SysTick.h"
#include "./led/bsp_led.h"
#include "./bsp_AdvanceTIMx/bsp_AdvanceTIMx.h"
#include <stdlib.h>
#include <string.h>
#include "../Utils/cJSON.h"
#include "weather.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./flash/bsp_spi_flash.h"
 



/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	char *pStr;
	char value[15];
	/* 初始化 */
	WiFi_Config();    						//初始化WiFi模块使用的接口和外设
	SysTick_Init();               //配置 SysTick 为 1ms 中断一次 
	LED_Config();
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_Mode_Config();
	ILI9341_Init (); 
	ILI9341_GramScan ( 6 );
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(WHITE,BLACK);
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
  ILI9341_DispStringLine_EN_CH(LINE(0),"实时天气");
//	ESP8266_AP_TCP_Server();
//	ESP8266_StaTcpClient_UnvarnishTest();	
	GetNowWeather();
//	PC_Usart ( "\r\n请在手机网络调试助手发送字符串\r\n" );
	while(1);
}

	



/*********************************************END OF FILE**********************/
