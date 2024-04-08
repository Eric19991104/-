#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <RTClib.h>

#define brightness 1
#define AHT10_I2C_ADDR 0x38 // I2C address of the AHT10 sensor
#define AHT10Address 0x38 //AHT10 預設的位址
#define CLK 10
#define CS 11
#define DIN 12
#define Setting_Button 3
#define Plus_Button 4
#define Minus_Button 5

#define Begin 0
#define idle 2
#define HourSetting 3
#define MinuteSetting 4
#define YearSetting 5
#define MonthSetting 6
#define DaySetting 7

void initial(); //初始化

void run(); //執行

DateTime get_time(); //取得時間

void print_humidity_and_temperature(byte *,byte *,byte *,byte *); //顯示溫度及濕度

void print_time(byte *, byte *, byte *); //顯示時：分

void print_date(byte *, byte *, byte *, byte *); //顯示年月日

void print_moisture( byte *, byte *); //顯示土壤濕度

void clear_display(); //清除 MAX7219

void AHT10_Reset(); //AHT10 做 reset

void AHT10_Calibrate(); //AHT10 做校準

void get_humidity_and_temperature(); //讀取溫濕度

void Setting(int parameter);

#endif
