#include"library.h"

void setup()
{
  initial();
}

void loop()
{
  int num = (int)pow(2,1); //LED 0~7 共8個，用位元算術左移控制LED閃爍，每一輪一開始都是最低位元LED都亮因此在loop迴圈最開始處設定num為2 ^ 1 = 2，只是要透過取log決定位元數因此不需要減1，其中pow為float型態所以轉換會int。
  while(num <= 256) //至多會亮8個LED，所以如果num已經是(2 ^ 8)就不必再執行。
  {
    run(num); //執行後
    num <<= 1; //左移
  }
}