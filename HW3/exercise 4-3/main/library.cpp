#include"library.h"
#include<Arduino.h>

void initial()
{
  for(int i = L0 ; i <= L7 ; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}
void reset()
{
  for(int i = L0 ; i <= L7 ; i++)
  {
    digitalWrite(i,LOW);
  }
}
void display_led(int start,int end)
{
  for(int i = 35 ; i >= 0 ; i--) //讓LED逐漸變亮，設35是觀測過最合適的。
  {
    reset(); //反正其他的本來就不需要亮，為了節省空間直接呼叫此函式。
    delay(i);
    for(int j = start ; j <= end ; j++) //把需要亮的打開
    {
      digitalWrite(j,HIGH);
    }
    delay(35 - i);
  }
}
void run(int start,int end)
{
  display_led(start,end);
  delay(delay_time); //每一step都間隔3秒
  reset(); //關掉所有的LED
}