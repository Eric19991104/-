#include"library.h"
int flag[8]; //控制每個LED亮/暗

void setup()
{
  initial();
}

void loop()
{
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 2 || i == 5)
    {
      flag[i] = LOW;
    }
    else
    {
      flag[i] = HIGH;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 2 || i == 5)
    {
      flag[i] = HIGH;
    }
    else
    {
      flag[i] = LOW;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 0 || i == 2 || i == 5 || i == 7)
    {
      flag[i] = HIGH;
    }
    else
    {
      flag[i] = LOW;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 1 || i == 4 || i == 7)
    {
      flag[i] = HIGH;
    }
    else
    {
      flag[i] = LOW;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 0 || i == 3 || i == 6)
    {
      flag[i] = HIGH;
    }
    else
    {
      flag[i] = LOW;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 0 || i == 2 || i == 5)
    {
      flag[i] = HIGH;
    }
    else
    {
      flag[i] = LOW;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 1 || i == 3 || i == 6)
    {
      flag[i] = HIGH;
    }
    else
    {
      flag[i] = LOW;
    }
  }
  run(flag);
  for(int i = 0 ; i < 8 ; i++)
  {
    if(i == 2 || i == 5)
    {
      flag[i] = LOW;
    }
    else
    {
      flag[i] = HIGH;
    }
  }
  run(flag);
}