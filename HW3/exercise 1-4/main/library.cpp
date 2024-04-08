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
void run(int *flag)
{
  digitalWrite(L0,flag[0]);
  digitalWrite(L1,flag[1]);
  digitalWrite(L2,flag[2]);
  digitalWrite(L3,flag[3]);
  digitalWrite(L4,flag[4]);
  digitalWrite(L5,flag[5]);
  digitalWrite(L6,flag[6]);
  digitalWrite(L7,flag[7]);
  delay(delay_time);
  reset();
}