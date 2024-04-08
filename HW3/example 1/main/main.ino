#include"library.h"

void setup()
{
  initial();
}

void loop()
{
  for(int i = L0 ; i <= L7 ; i++)
  {
    run(i);
  }
}