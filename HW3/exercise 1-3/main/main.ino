#include"library.h"

bool flag = true; //控制亮哪幾個LED，true為Step 0~3，false為Step 4~7。

void setup()
{
  initial();
}

void loop()
{
  if(flag)
  {
    int num = (int)pow(2,4); //一次至多亮4個LED，所以2 ^ 4 = 16再減1為15共4個位元，其中pow結果為float型態所以要轉成int，由於只是要透過log判斷判斷位元數決定亮幾個LED所以就不減1了。
    while(num > 1) //至少會亮1個LED，所以如果num已經是(2 ^ 0)就不必再執行。
    {
      run(num,flag); //執行後
      num >>= 1; //右移
    }
    flag = false; //flag要更改
  }
  else
  {
    int num = (int)pow(2,1); //Step 4~7是亮的LED數遞增，跟前面相反，只是要從1次方開始是因為要取次方數，至少會亮1個LED，所以從(2 ^ 1)開始。
    int exponent = log(num) / log(2); //透過次方數判斷是否達到4位元了
    while(exponent <= 4) //最多4個LED所以只要次方 ≤ 4就可以
    {
      run(num,flag);
      num <<= 1; //因為是亮的LED數遞增所以用左移1位元
      exponent = log(num) / log(2); //更新次方數
    }
    flag = true;
  }
}