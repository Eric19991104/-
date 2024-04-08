#ifndef _LIBRARY_H
#define _LIBRARY_H

#include<FastLED.h>

//共陽LED腳位一定要設9 ～ 11這3個不然會有問題
#define Red 11
#define Blue 10
#define Green 9
#define delay_time 1000

//WS2832B
#define DATA_PIN    3
#define NUM_LEDS    1 //WS2832B的數量
#define BRIGHTNESS  255 //亮度
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB //RGB的順序，在WS2832B順序是G、R、B，把順序設定成這樣，在設定顏色的時候數值可以直接照著R、G、B的順序設定。

void initial(); //初始化

void run(int *,int *); //執行共陽LED及WS2832B

#endif