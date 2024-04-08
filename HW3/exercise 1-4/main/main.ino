#include"library.h"
int flag[8] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW}; //控制每個LED亮/暗
bool control[8] = {false,false,false,false,false,false,false,false}; //從下一個step起一直到step7為止都要亮的就設為true
int step = 0;

void setup()
{
  initial();
}

void loop()
{
  if(step % 2) //step如果是奇數
  {
    for(int i = 0 ; i <= 7 - step ; i++)
    {
      flag[i] = HIGH;
    }
    control[7 - step] = true; //7為最高位元LED也就是L7，7 - step的這個LED一直到step7為止每一次都會亮。
  }
  for(int i = 0 ; i < 8 ; i++)
  {
    if(control[i])
    {
      flag[i] = HIGH; //只要被設定成之後每一步都要亮的就設為高電位
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    flag[i] = LOW; //不重置成低電位會一直亮著
    if((step + 1) % 8 == 0)
    {
      control[i] = false; //一輪結束後再重置一維陣列control
    }
  }
  step = (step + 1) % 8;
}