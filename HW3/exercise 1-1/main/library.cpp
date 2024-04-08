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
void run(int A,int B)
{
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  delay(delay_time);
  digitalWrite(A,LOW);
  digitalWrite(B,LOW);
}