#include"library.h"
#include<Arduino.h>
int LED[] = {NULL,L0,L1,L2,L3,L4,L5,L6,L7}; //決定要亮哪2個LED，因為step 1只亮L0為了配合run()中的for迴圈所以把LED[0]設為NULL。

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
  digitalWrite(start,HIGH);
  digitalWrite(end,HIGH);
}
void run()
{
  for(int i = 1 ; i < 9 ; i++)
  {
    display_led(LED[i - 1],LED[i]); //每一次亮2個LED
    delay(delay_time); //每一step都間隔3秒
    reset(); //關掉所有的LED
  }
}