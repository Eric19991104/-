#include"library.h"
#include<Arduino.h>

bool flag[8]; //控制每個LED亮/暗

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
void display_led()
{
  for(int i = 35 ; i >= 0 ; i--) //逐漸變亮
  {
    reset(); //執行前先關掉所有的LED，不先關掉的話一開始就會是最亮。
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
void run(int A)
{
  int bits = log(A) / log(2); //位元數,因為log()是natural log，所以要以2為底的就用log公式代替。
  for(int i = 0 ; i < 9 ; i++) //設定一維陣列flag，因為陣列的index都是0 ～ (n - 1)，所以只要 ≤ 位元數的就是要亮否則要暗。
  {
    if(i < bits)
    {
      flag[i] = true;
    }
    else
    {
      flag[i] = false;
    }
  }
  display_led();
  delay(delay_time); //每個step都間隔3秒
}