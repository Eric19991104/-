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
void display_led(int *flag)
{
  for(int i = 35 ; i >= 0 ; i--) //讓LED逐漸變亮，設35是觀測過最合適的。
  {
    reset(); //反正其他的本來就不需要亮，為了節省空間直接呼叫此函式。
    delay(i);
    digitalWrite(L0,flag[0]);
    digitalWrite(L1,flag[1]);
    digitalWrite(L2,flag[2]);
    digitalWrite(L3,flag[3]);
    digitalWrite(L4,flag[4]);
    digitalWrite(L5,flag[5]);
    digitalWrite(L6,flag[6]);
    digitalWrite(L7,flag[7]);
    delay(35 - i);
  }
}
void run(int *flag)
{
  display_led(flag);
  delay(delay_time);
  reset();
}