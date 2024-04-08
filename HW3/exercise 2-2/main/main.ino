#include"library.h"
int LED[] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW}; //控制每個LED亮/暗
bool flag = true; //去 or 折返回來
int step = 0;
int add; //下一次移動步數要增加多少
int shift; //移動步數
int first; //第一個LED在一維陣列中的index
int second; //第二個LED在一維陣列中的index
int count; //已經移動的次數，去的時候逐漸遞增，折返時逐漸遞減。

void setup()
{
  initial();
}

void loop()
{
  if(step == 0) //最一開始
  {
    count = 0;
    first = 7; //最高位元LED
    second = 6; //次高位元LED
    add = 1; //下一輪要增加一步
    shift = 2; //最一開始移動2步
  }

  if(step % 2) //16個step中最低位元LED的閃爍
  {
    LED[0] = LOW;
  }
  else
  {
    LED[0] = HIGH;
  }

  LED[first] = HIGH; //把要亮的設成HIGH
  LED[second] = HIGH;
  run(LED);

  //因為是移動前就已經加/減count，所以這個判斷要放在加/減count還有index的前面，避免多移動或少移動。
  if(count == shift && shift != 5) //已經移動的步數已經達到要移動的步數，因為step11 ~ 15要移動5步而且沒有折返所以只有要移動的步數不是5步才會進行折返。
  {
    flag = false; //false表示折返
  }

  if(flag) //去
  {
    count++;
    first--;
    second--;
  }
  else //折返
  {
    count--;
    first++;
    second++;
  }

  if(count == 0) //折返後當已經折返回來準備進行下一輪，add會是這一輪要移動的步數，而shift必須加上add所以用一個temp暫存add。
  {
    int temp = add;
    add = shift;
    shift += temp;
    flag = true; //flag重新設定成去
  }

  for(int i = 0 ; i < 8 ; i++)
  {
    LED[i] = LOW; //要全部都先關掉不然會一直都亮著
  }
  step = (step + 1) % 16;
}