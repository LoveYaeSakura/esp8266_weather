#include <stdlib.h>
#include "weather.h"
#include "./lcd/bsp_ili9341_lcd.h"
//#include "malloc.h"

#define      macUser_ESP8266_ApSsid           "TP-LINK_F956" 

//要连接的热点的密钥
#define      macUser_ESP8266_ApPwd            "13795979826" 

WeatherType weather_data;

extern int SwitchToGbk(const unsigned char* pszBufIn, int nBufInLen, unsigned char* pszBufOut, int* pnBufOutLen);

static int cJSON_NowWeatherParse(char *JSON, WeatherType *result)
{
	cJSON *json, *results, *location, *now, *item, *object;
	char *utf8str,*gbkstr;
	int len;
	char displayBuff[100];
	

	utf8str = (char*)malloc(50);
	gbkstr = (char*)malloc(50);
	

	memset(utf8str, 0, 50);
	memset(gbkstr, 0, 50);
	
	json = cJSON_Parse(JSON);
	
	results = cJSON_GetObjectItem(json, "results");	
	object = cJSON_GetArrayItem(results, 0);
	
	location = cJSON_GetObjectItem(object, "location");
	now = cJSON_GetObjectItem(object, "now");
	

	item = cJSON_GetObjectItem(location, "name");
	utf8str = item->valuestring;
	SwitchToGbk((const u8*)utf8str, strlen(utf8str),(u8*)gbkstr,&len);
	sprintf(displayBuff, "城    市: %s", gbkstr);
	ILI9341_DispStringLine_EN_CH(LINE(1), displayBuff);
	memset(gbkstr, 0, 50);
	memset(displayBuff, 0, 50);
	
	item = cJSON_GetObjectItem(location, "path");
	utf8str = item->valuestring;
	SwitchToGbk((const u8*)utf8str, strlen(utf8str),(u8*)gbkstr,&len);
	sprintf(displayBuff, "地    区: %s", gbkstr);
	ILI9341_DispStringLine_EN_CH(LINE(2), displayBuff);
	memset(gbkstr, 0, 50);
	memset(displayBuff, 0, 50);
	
	item = cJSON_GetObjectItem(now, "text");
	utf8str = item->valuestring;
	SwitchToGbk((const u8*)utf8str, strlen(utf8str),(u8*)gbkstr,&len);
	sprintf(displayBuff, "天    气: %s", gbkstr);
	ILI9341_DispStringLine_EN_CH(LINE(3), displayBuff);
	memset(gbkstr, 0, 50);
	memset(displayBuff, 0, 50);
	
	item = cJSON_GetObjectItem(now, "code");
	utf8str = item->valuestring;
	sprintf(displayBuff, "天气代码：%s", utf8str);
	ILI9341_DispStringLine_EN_CH(LINE(5), displayBuff);
	memset(displayBuff, 0, 50);
	
	item = cJSON_GetObjectItem(now, "temperature");
	utf8str = item->valuestring;
	sprintf(displayBuff, "温    度：%s", utf8str);
	ILI9341_DispStringLine_EN_CH(LINE(4), displayBuff);
	memset(displayBuff, 0, 50);
	
	cJSON_Delete(json);
	cJSON_Delete(results);
	cJSON_Delete(now);
	cJSON_Delete(item);
	cJSON_Delete(object);
	
	free(utf8str);
	free(gbkstr);
}


void GetNowWeather ( void )
{	
//  PC_Usart ( "\r\n本测试以访问心知天气为例\r\n" );
	Delay_ms ( 300 );
	ESP8266_Choose ( ENABLE );
	ESP8266_AT_Test ();

	ESP8266_Net_Mode_Choose ( STA );
	
  ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd );	

	ESP8266_Link_Server ( enumTCP, (char*)WEATHER_IP, (char*)WEATHER_PORT, Single_ID );
	ESP8266_UnvarnishSend();
	
	ESP8266_SendString(ENABLE,"GET https://api.seniverse.com/v3/weather/now.json?key=S9HUFUh0TH5dj6SH1&location=beijing&language=zh-Hans&unit=c\r\n\r\n",NULL,Single_ID);
	strEsp8266_Fram_Record .InfBit .FramLength = 0;
	Delay_ms(1000);
	strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
	
	cJSON_NowWeatherParse((char*)strEsp8266_Fram_Record .Data_RX_BUF, &weather_data);
}

