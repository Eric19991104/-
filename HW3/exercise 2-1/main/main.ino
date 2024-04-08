#include"library.h"

bool flag = true; //控制亮的順序，true為Step 0~7，false為Step 8~15。

void setup()
{
  initial();
}

void loop()
{
  if(flag)
  {
    for(int i = L7 ; i >= L0 ; i--)
    {
      run(i);
    }
    flag = false; //flag要更改
  }
  else
  {
    for(int i = L0 ; i <= L7 ; i++)
    {
      run(i);
    }
    flag = true;
  }
}