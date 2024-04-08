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
void run(int A,bool flag)
{
  int bits = log(A) / log(2); //位元數，因為log()是natural log，所以要以2為底的就用log公式代替。
  switch(bits) //依照不同的位元數決定要從L0開始亮幾個LED
  {
    case 1:
      if(flag) //根據flag決定哪幾個LED要亮
      {
        digitalWrite(L4,HIGH);
      }
      else
      {
        digitalWrite(L3,HIGH);
      }
      break;
    case 2:
      if(flag)
      {
        digitalWrite(L4,HIGH);
        digitalWrite(L5,HIGH);
      }
      else
      {
        digitalWrite(L3,HIGH);
        digitalWrite(L2,HIGH);
      }
      break;
    case 3:
      if(flag)
      {
        digitalWrite(L4,HIGH);
        digitalWrite(L5,HIGH);
        digitalWrite(L6,HIGH);
      }
      else
      {
        digitalWrite(L1,HIGH);
        digitalWrite(L2,HIGH);
        digitalWrite(L3,HIGH);
      }
      break;
    case 4:
      if(flag)
      {
        digitalWrite(L4,HIGH);
        digitalWrite(L5,HIGH);
        digitalWrite(L6,HIGH);
        digitalWrite(L7,HIGH);
      }
      else
      {
        digitalWrite(L0,HIGH);
        digitalWrite(L1,HIGH);
        digitalWrite(L2,HIGH);
        digitalWrite(L3,HIGH);
      }
      break;
    default:
      break;
  }
  delay(delay_time);
  reset();
}