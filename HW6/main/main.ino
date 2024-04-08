#include"library.h"

int number = 0;

void setup()
{
  initial();
}
void loop()
{
  if(read_switch_method(PC2)) //遞增按鈕有被按下
  {
    number++;
    number %= 100;
  }
  if(read_switch_method(PC3)) //遞減按鈕有被按下
  {
    number--;
    if(number < 0)
    {
      number += 100;
    }
  }
  run(number);
}