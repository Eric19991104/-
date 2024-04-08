#include"library.h"
#include<Arduino.h>

byte count = 0; //byte type的值只會在0 ～ 255，超過就會回到0。

void initial()
{
  for(int i = L0 ; i <= L7 ; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}
void run()
{
  binary(count++); //不斷遞增count
  delay(delay_time); //delay完後因為是自動做位元AND運算直接設定，所以不需要特地把腳位設定成LOW。
}
void binary(byte num)
{
  //只有8個位元，從最低位元開始設定，每次與1做位元AND運算，結果不是0就是1，0就相當於LOW，1相當於HIGH，依序設定8個LED，每個LED設定完就右移1個位元。
  for(int i = L0 ; i <= L7 ; i++)
  {
    digitalWrite(i,num & 1);
    num >>= 1;
  }
}