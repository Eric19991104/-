#include"library.h"
#include<Arduino.h>
#include<FastLED.h>

CRGB leds[NUM_LEDS];

void initial()
{
  for(int i = Green ; i <= Red ; i++) //共陽LED腳位
  {
    pinMode(i,OUTPUT);
  }

  //WS2832B
  pinMode(DATA_PIN,OUTPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); //初始化
  FastLED.setBrightness(BRIGHTNESS); //設定亮度
}
void run(int *A,int *B)
{
  leds[0] = CRGB(B[0], B[1], B[2]); //第N個WS2832B的顏色，因為只有1個所以只用到第0個。
  FastLED.show(); //要顯示出顏色
  analogWrite(Red, A[0]); //3個腳位的duty cycle
  analogWrite(Blue, A[1]);
  analogWrite(Green, A[2]);
  delay(delay_time);
}