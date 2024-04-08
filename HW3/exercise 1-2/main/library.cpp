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
void run(int A)
{
  int bits = log(A) / log(2); //位元數,因為log()是natural log，所以要以2為底的就用log公式代替。
  switch(bits) //依照不同的位元數決定要從L0開始亮幾個LED
  {
    case 1:
      digitalWrite(L0,HIGH);
      break;
    case 2:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      break;
    case 3:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      break;
    case 4:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      break;
    case 5:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,HIGH);
      break;
    case 6:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,HIGH);
      digitalWrite(L5,HIGH);
      break;
    case 7:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,HIGH);
      digitalWrite(L5,HIGH);
      digitalWrite(L6,HIGH);
      break;
    case 8:
      digitalWrite(L0,HIGH);
      digitalWrite(L1,HIGH);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,HIGH);
      digitalWrite(L5,HIGH);
      digitalWrite(L6,HIGH);
      digitalWrite(L7,HIGH);
      break;
    default:
      break;
  }
  delay(delay_time);
  reset();
}