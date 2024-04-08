#ifndef _LIBRARY_H
#define _LIBRARY_H
#include<Arduino.h>
#define L0 4
#define L1 5
#define L2 6
#define L3 7
#define L4 8
#define L5 9
#define L6 10
#define L7 11
#define delay_time 250

void initial(); //初始化

void reset(); //重置所有的LED為低電位

void display_led(int,int); //讓LED逐漸變亮，傳入的參數分別為LED亮的起始及終點。

void run(); //執行LED，傳入的參數分別為LED亮的起始及終點。

#endif