#ifndef _LIBRARY_H
#define _LIBRARY_H

#define delay_time 5

#define debounce 50 //機械彈跳等待的毫秒數
#define switched true //按鈕被按下

void initial(); //初始化

bool read_switch_method(int); //去除機械彈跳

void run(int); //執行7段顯示器

#endif