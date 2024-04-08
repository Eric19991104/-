#include"library.h"

bool flag = true; //控制step0 ~ 3及4 ~ 7

void setup()
{
  initial();
}

void loop()
{
  if(flag)
  {
    run(L0,L7);
    run(L1,L6);
    run(L2,L5);
    run(L3,L4);
    flag = false;
  }
  else
  {
    run(L3,L4);
    run(L2,L5);
    run(L1,L6);
    run(L0,L7);
    flag = true;
  }
}