#include"library.h"
#include<Arduino.h>
#include<avr/io.h> //delay使用avr的方法
#include<util/delay.h>

int value[2] = {0,0}; //儲存數值的個位數/十位數
const int digit[][8] = //7段顯示器的每一個數字74HC595從Q7 ～ Q0所要輸出的值
{
  {0,0,1,1,1,1,1,1},
  {0,0,0,0,0,1,1,0},
  {0,1,0,1,1,0,1,1},
  {0,1,0,0,1,1,1,1},
  {0,1,1,0,0,1,1,0},
  {0,1,1,0,1,1,0,1},
  {0,1,1,1,1,1,0,1},
  {0,0,0,0,0,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,1,1,0,1,1,1,1}
};

void initial()
{
  for(int i = PB1 ; i <= PB3 ; i++) //把pin9 ~ 11設為output
  {
    DDRB |= (1 << i);
  }
  DDRC &= ~((1 << PC2) | (1 << PC3)); //A2、A3設為input
  DDRC |= ((1 << PC0) | (1 << PC1)); //A0、A1設為output
}

bool read_switch_method(int button) //button為PC2或PC3
{
  int switch_pin_reading; //讀取腳位的值
  bool switch_status; //按鈕是否有被按下
  long int elapse_timer; //前一個時間
  switch_status = !switched; //假設按鈕時沒有被按下的
  switch_pin_reading = PINC; //先讀取一次PINC的值
  do{
    //不管PINC目前的值是多少，哪些位元是1，哪些是0，要得知PCx是否為1，就將PINC和(1 << x)做位元AND運算，結果不是0就是2 ^ x，結果如果不是0就代表那個腳位為HIGH。
    if((switch_pin_reading & (1 << button)) != 0) //判斷PCx是否為HIGH
    {
      switch_status = switched; //儲存按鈕的狀態

      //實在找不到其他可以取得目前時間的方法可以替代Arduino的millis()所以只好用millis()
      elapse_timer = millis(); //按鈕被按下的時間
      do {} while(millis() - elapse_timer < debounce); //等待一點時間
      switch_pin_reading = PINC;  //再讀取一次PINC的值
    }
  }while((switch_pin_reading & (1 << button)) != 0); //等待直到放開開關
  return switch_status; //回傳是否有按下
}
void run(int num)
{
  value[0] = num % 10; //個位數
  value[1] = num / 10 % 10; //十位數
  for(int k = 0 ; k < 2 ; k++) //一次顯示一個位數，先個位數後十位數。
  {
    PORTB &= ~(1 << PB2); //latch設為LOW
    if(k == 0) //個位數
    {
      PORTC &= ~(1 << PC0); //把控制D1的PC0設為LOW
      PORTC |= (1 << PC1); //把控制D2的PC1設為HIGH
      for(int i = 0 ; i < 8 ; i++) //透過74HC595從Q7到Q0依序輸出
      {
        PORTB &= ~(1 << PB1); //clock設為LOW
        if(digit[value[0]][i]) //如果是要輸出1
        {
          PORTB |= (1 << PB3); //ds設為HIGH
        }
        else //否則
        {
          PORTB &= ~(1 << PB3); //設為LOW
        }
        PORTB |= (1 << PB1); //clock設為HIGH
      }
    }
    else //十位數
    {
      PORTC &= ~(1 << PC1);
      PORTC |= (1 << PC0);
      for(int i = 0 ; i < 8 ; i++)
      {
        PORTB &= ~(1 << PB1);
        if(digit[value[1]][i])
        {
          PORTB |= (1 << PB3);
        }
        else
        {
          PORTB &= ~(1 << PB3);
        }
        PORTB |= (1 << PB1);
      }
    }
    PORTB |= (1 << PB2); //latch設為HIGH
    _delay_ms(delay_time); //延遲5毫秒以達到視覺暫留的效果，“_delay_ms”是avr的方法。
  }
}