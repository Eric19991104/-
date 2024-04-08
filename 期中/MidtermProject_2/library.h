#ifndef _LIBRARY_H
#define _LIBRARY_H
#include <Arduino.h>

void Initial();         //初始化
void Counter();         //0.5秒換數字
void Display();         //顯示數字
void DisplayNumber(byte num);
void SendOne();         //Data = 1
void SendZero();        //Data = 0
void ShiftData();       //DP = 0 同時LatchPin = H
void SegZero();
void SegOne();
void SegTwo();
void SegThree();
void SegFour();
void SegFive();
void SegSix();
void SegSeven();
void SegEight();
void SegNine();

#endif
