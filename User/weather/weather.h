#ifndef __WEATHER_H
#define __WEATHER_H

#include "wifi_config.h"
#include "../Utils/cJSON.h"
#include "wifi_function.h"
#include "bsp_SysTick.h"
#include "../usart/bsp_usart1.h"

#define WEATHER_IP 		"116.62.81.138"
#define WEATHER_PORT 	"80"

typedef struct
{
	/* ʵ���������� */
	char name[32];				//����
	char text[32];				//����Ԥ������
	char code[32];				//����Ԥ������
	char temperature[32];   	//����
	
	/* ���졢���졢������������ */
//	char date[3][32];			//����
//	char text_day[3][64];	    //����������������
//	char code_day[3][32];		//���������������
//	char code_night[3][64]; 	//��������������
//	char high[3][32];			//�����
//	char low[3][32];			//�����
//	char wind_direction[3][64]; //����
//	char wind_speed[3][32];  	//���٣���λkm/h����unit=cʱ��
//	char wind_scale[3][32];  	//�����ȼ�
//	
//	char life_suggestion[128][2];	//�����
}WeatherType;

extern WeatherType weather_data;

void GetNowWeather(void);

#endif