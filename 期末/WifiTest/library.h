#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <RTClib.h>
#define AHT10_I2C_ADDR 0x38 // I2C address of the AHT10 sensor
#define AHT10Address 0x38 //AHT10 預設的位址
#define fan 10
#define PWM_Button 4

void initial(); //初始化

void run(); //執行

void AHT10_Reset(); //AHT10 做 reset

void AHT10_Calibrate(); //AHT10 做校準

void get_humidity_and_temperature(); //讀取溫濕度

DateTime get_time(); //取得時間

void Wi_Fi();

#endif
