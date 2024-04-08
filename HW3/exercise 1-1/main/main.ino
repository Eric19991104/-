#include"library.h"

int LED[][2] = {{L0,L7},{L1,L6},{L2,L5},{L3,L4}}; //要同時亮的一組
bool flag = true; //控制順向還是反向，true為順向，false為反向。

void setup()
{
  initial();
}

void loop()
{
  if(flag)
  {
    for(int i = 0 ; i < 4 ; i++) //依照LED二維陣列row順向
    {
      run(LED[i][0],LED[i][1]);
    }
    flag = false; //flag要更改
  }
  else
  {
    for(int i = 3 ; i >= 0 ; i--) //依照LED二維陣列row反向
    {
      run(LED[i][0],LED[i][1]);
    }
    flag = true;
  }
}