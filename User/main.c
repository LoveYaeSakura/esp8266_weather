/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-01-xx
  * @brief   WF-ESP8266 WiFiģ�����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
	
// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)   72M / (20000*72)
// PWM �źŵ����� T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)
	
/* ESP8266��stm32�����ӣ�
ESP8266-01 :  stm32
3v3 :   3v3
GND :   GND
RX  :   PA2  //(Rx��stm32����2��Tx��)
TX  ��  PA3  //(Tx��stm32����2��Rx��)
EN  :		PA0  //(EN�ֽ�Ƭѡ��PA1�ڣ����޸�)
RST :		PA1	 //(RST��stm32��PA0�ڣ����޸�)

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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	char *pStr;
	char value[15];
	/* ��ʼ�� */
	WiFi_Config();    						//��ʼ��WiFiģ��ʹ�õĽӿں�����
	SysTick_Init();               //���� SysTick Ϊ 1ms �ж�һ�� 
	LED_Config();
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_Mode_Config();
	ILI9341_Init (); 
	ILI9341_GramScan ( 6 );
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(WHITE,BLACK);
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* ��������ʾȫ�� */
  ILI9341_DispStringLine_EN_CH(LINE(0),"ʵʱ����");
//	ESP8266_AP_TCP_Server();
//	ESP8266_StaTcpClient_UnvarnishTest();	
	GetNowWeather();
//	PC_Usart ( "\r\n�����ֻ�����������ַ����ַ���\r\n" );
	while(1);
}

	



/*********************************************END OF FILE**********************/
