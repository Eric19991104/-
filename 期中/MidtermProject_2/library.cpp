#include "library.h"
#include<Arduino.h>

unsigned long previousMillis = 0;
const long interval = 500;

const byte led_Num = 2 ; // 7段顯示器的數量
byte digits[2] = {0, 0}; // 個位數, 十位數
int number=0; //計數

void Initial(){
  DDRD = 0x3C;  //PIN2、3、4、5(D0、D1、D2、D3)設為OUTPUT，0001 1100
  DDRC = 0x03;  //A0、A1(7-seg_D1、7-seg_D2)設為OUTPUT，0000 0011
}

void Counter(){
  unsigned long currentMillis = millis();
  
  // 每隔0.5秒執行一次底下的條件式內容
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (++number > 99) {  // number先加1，再比較
      number = 0;         // 若超過99則歸零
    }
    
    digits[0]= number % 10 ;       // 儲存個位數字
    digits[1]= number / 10 % 10 ;  // 十位數字
  }
}

void Display(){
  byte num; // 取出數字來顯示

  // 逐一設定每個七段顯示器
  for (byte i=0; i<led_Num; i++){
    num = digits[i];

    if (i == 0){              // D2 Open
      PORTC &= ~(1 << PC0);   //D1 LOW
      PORTC |= (1 << PC1);    //D2 HIGH
    }
    else{                     // D1 Open
      PORTC |= (1 << PC0);    //D1 HIGH
      PORTC &= ~(1 << PC1);   //D2 LOW  
    }

    DisplayNumber(num) ;
    delay(10);
  }
}

void DisplayNumber(byte num){
  switch(num){
    case 0 :
      SegZero();
      break;
    case 1 :
      SegOne();
      break;
    case 2 :
      SegTwo();
      break;
    case 3 :
      SegThree();
      break;
    case 4 :
      SegFour();
      break;
    case 5 :
      SegFive();
      break;
    case 6 :
      SegSix();
      break;
    case 7 :
      SegSeven();
      break;
    case 8 :
      SegEight();
      break;
    case 9 :
      SegNine();
      break;
    default:
      SegZero();
      break;
  }
}

void SegZero(){ // A, B, C, D, E, F
  SendZero();//G
  SendOne();//f
  SendOne();//E
  SendOne();//D
  SendOne();//C
  SendOne();//B
  SendOne();//A
  ShiftData();//DP
}

void SegOne(){ // B, C
  SendZero();//G
  SendZero();//f
  SendZero();//E
  SendZero();//D
  SendOne();//C
  SendOne();//B
  SendZero();//A
  ShiftData();//DP
}

void SegTwo() { // A, B, D, E, G
  SendOne();//G
  SendZero();//f
  SendOne();//E
  SendOne();//D
  SendZero();//C
  SendOne();//B
  SendOne();//A
  ShiftData();//DP
}

void SegThree() { // A, B, C, D, G
  SendOne();//G
  SendZero();//f
  SendZero();//E
  SendOne();//D
  SendOne();//C
  SendOne();//B
  SendOne();//A
  ShiftData();//DP
}

void SegFour() { // B, C, F, G
  SendOne();//G
  SendOne();//f
  SendZero();//E
  SendZero();//D
  SendOne();//C
  SendOne();//B
  SendZero();//A
  ShiftData();//DP
}

void SegFive() { // A, C, D, F, G
  SendOne();//G
  SendOne();//f
  SendZero();//E
  SendOne();//D
  SendOne();//C
  SendZero();//B
  SendOne();//A
  ShiftData();//DP
}

void SegSix() { // C, D, E, F, G
  SendOne();//G
  SendOne();//f
  SendOne();//E
  SendOne();//D
  SendOne();//C
  SendZero();//B
  SendZero();//A
  ShiftData();//DP
}

void SegSeven() { // A, B, C
  SendZero();//G
  SendZero();//f
  SendZero();//E
  SendZero();//D
  SendOne();//C
  SendOne();//B
  SendOne();//A
  ShiftData();//DP
}

void SegEight() { // A, B, C, D, E, F, G
  SendOne();//G
  SendOne();//f
  SendOne();//E
  SendOne();//D
  SendOne();//C
  SendOne();//B
  SendOne();//A
  ShiftData();//DP
}

void SegNine() { // A, B, C, F, G
  SendOne();//G
  SendOne();//f
  SendZero();//E
  SendZero();//D
  SendOne();//C
  SendOne();//B
  SendOne();//A
  ShiftData();//DP
}

void SendOne(){
                         //Clock   Latch   DS
  PORTD &= ~(1 << PD2);  // L        L     H
  PORTD &= ~(1 << PD3);
  PORTD |= (1 << PD4);
  PORTD &= ~(1 << PD5);

                          //Clock   Latch   DS
  PORTD |= (1 << PD2);    // H        L     H
  PORTD &= ~(1 << PD3);
  PORTD |= (1 << PD4);
  PORTD &= ~(1 << PD5);
}

void SendZero(){
                          //Clock   Latch   DS
  PORTD |= (1 << PD2);    // L        L     L
  PORTD &= ~(1 << PD3);
  PORTD &= ~(1 << PD4);
  PORTD &= ~(1 << PD5);

                          //Clock   Latch   DS
  PORTD |= (1 << PD2);    // H        L     H
  PORTD &= ~(1 << PD3);
  PORTD |= (1 << PD4);
  PORTD &= ~(1 << PD5);
}

void ShiftData(){
                          //Clock   Latch   DS
  PORTD &= ~(1 << PD2);    // L       L     H
  PORTD &= ~(1 << PD3);
  PORTD |= (1 << PD4);
  PORTD &= ~(1 << PD5);

                          //Clock   Latch   DS
  PORTD &= ~(1 << PD2);    // H       H     L
  PORTD |= (1 << PD3);
  PORTD &= ~(1 << PD4);
  PORTD &= ~(1 << PD5);
}
