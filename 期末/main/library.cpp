#include"library.h"
#include<Arduino.h>
#include<Wire.h>
#include<RTClib.h>
#include<LedControl.h> 

RTC_DS1307 rtc; //建立 RTC 物件

const unsigned char eSensorCalibrateCmd[3] = {0xE1, 0x08, 0x00},eSensorMeasureCmd[3] = {0xAC, 0x33, 0x00}; //分別是校準、測量 AHT10 用的3個位址

int print_mode = 0; //顯示的東西，0是年月日，1是時：分，2是濕度及溫度。
int last_status; //上一個 Touch Sensor 的狀態
int current_status; //目前 Touch Sensor 的狀態

int touch_status; //PINB 目前的值

float temperature,humidity; //溫度及濕度，為float型態。

int value = 0;

int Set = 0;
int Count = 0;

int NowHour = 0;
int NowMinute = 0;
int NowYear = 0;
int NowMonth = 0;
int NowDay = 0;

int FinalHour = 0;
int FinaMinute = 0;
int FinalYear = 0;
int FinaMonth = 0;
int FinalDay = 0;

int CountHour = 0;
int CountMinute = 0;
int CountYear = 0;
int CountMonth = 0;
int CountDay = 0;

//十位數
const byte display_left[][8] = {
  {0x00,0x70,0x50,0x50,0x50,0x70,0x00,0x00}, // 0
  {0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x00}, // 1
  {0x00,0x70,0x10,0x70,0x40,0x70,0x00,0x00}, // 2
  {0x00,0x70,0x10,0x70,0x10,0x70,0x00,0x00}, // 3
  {0x00,0x50,0x50,0x70,0x10,0x10,0x00,0x00}, // 4
  {0x00,0x70,0x40,0x70,0x10,0x70,0x00,0x00}, // 5
  {0x00,0x70,0x40,0x70,0x50,0x70,0x00,0x00}, // 6
  {0x00,0x70,0x10,0x10,0x10,0x10,0x00,0x00}, // 7
  {0x00,0x70,0x50,0x70,0x50,0x70,0x00,0x00}, // 8
  {0x00,0x70,0x50,0x70,0x10,0x70,0x00,0x00}  // 9
};

//個位數
const byte display_right[][8] = {
  {0x00,0x07,0x05,0x05,0x05,0x07,0x00,0x00}, //0
  {0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00}, // 1
  {0x00,0x07,0x01,0x07,0x04,0x07,0x00,0x00}, // 2
  {0x00,0x07,0x01,0x07,0x01,0x07,0x00,0x00}, // 3
  {0x00,0x05,0x05,0x07,0x01,0x01,0x00,0x00}, // 4
  {0x00,0x07,0x04,0x07,0x01,0x07,0x00,0x00}, // 5
  {0x00,0x07,0x04,0x07,0x05,0x07,0x00,0x00}, // 6
  {0x00,0x07,0x01,0x01,0x01,0x01,0x00,0x00}, // 7
  {0x00,0x07,0x05,0x07,0x05,0x07,0x00,0x00}, // 8
  {0x00,0x07,0x05,0x07,0x01,0x07,0x00,0x00}  // 9
};

const byte C[] = {0x70,0x50,0x77,0x04,0x04,0x07,0x00,0x00}; //度C
const byte percent[] = {0x00,0x72,0x54,0x78,0x1E,0x2A,0x4E,0x00}; // %
const byte dot[] = {0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00}; // :

byte display[100][8]; //數字 0 ～ 99

LedControl lc = LedControl(DIN,CLK,CS,0); //LED物件，用來控制MAX7219。

void initial()
{
  DDRB &= ~(1 << PB0); //設定Touch Sensor接的腳位為INPUT
  //pinMode(5,OUTPUT);
  pinMode(Setting_Button, INPUT_PULLUP);
  pinMode(Plus_Button, INPUT_PULLUP);
  pinMode(Minus_Button, INPUT_PULLUP);
  //起初先把 Touch Sensor 前一個和目前的狀態都設成一樣，避免 MAX7219 最初顯示的不是年月日而是時：分。
  touch_status = PINB; //先取得目前PINB的值
  //因為 Touch Sensor 輸入不是 1 就是 0 ，不管是哪一個只要與前一個狀態不同就會顯示下一個要顯示的東西，所以就看目前是輸入 1 還是 0。
  last_status = touch_status & (1 << PB0);
  current_status = touch_status & (1 << PB0);

  for(int i = 0 ; i < 100 ; i++) //設定數字 0 ～ 100 的矩陣內容
  {
    int left = i / 10 % 10,right = i % 10;
    for(int j = 0 ; j < 8 ; j++)
    {
      display[i][j] = display_left[left][j] + display_right[right][j];
    }
  }

  for(int i = 0 ; i < 4 ; i++)
  {
    lc.shutdown(i,false);               // The MAX72XX is in power-saving mode on startup
    lc.setIntensity(i,brightness);      // Set the brightness to maximum value
    lc.clearDisplay(i);                 // and clear the display
  }

  Wire.begin(0);
  Serial.begin(9600);

  AHT10_Reset(); //最初先reset
  AHT10_Calibrate(); //校準

  if (!rtc.begin())
  {
    //Serial.println("Couldn't find RTC");
    while(1);
  }
  if (!rtc.isrunning())
  {
    //Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //初始化時間為上傳/編譯時的時間
  }
}
void run()
{
  //Serial.write(Serial.read());  //傳輸讀取的訊號
  //Serial.println(Serial.read());

  while(Serial.available() > 0)
  {
    byte value1 = Serial.read();
    byte value2 = Serial.read();
    Serial.flush();
    value = value1 * 256 + value2;
    Serial.println(value);
    break;
  }
  
  //沒有任何的 delay 就能即時顯示目前讀取的時間或溫濕度
  touch_status = PINB; //PINB 目前的值
  current_status = touch_status & (1 << PB0); //Touch Sensor 輸入 0 還是 1

  /*if(temperature >= 25)
  {
    digitalWrite(5,HIGH);
    Serial.println("HIGH");
  }
  else
  {
    digitalWrite(5,LOW);
    Serial.println("LOW");
  }*/
  
  if(current_status != last_status) //只要Touch Sensor有按下去，狀態就會和之前不一樣，就改變 MAX7219 顯示的東西。
  {
    clear_display(); //當有要改變顯示的東西再把之前顯示的東西清除，每輪都清除就會一直閃。
    print_mode = (print_mode + 1) % 4;
    Set = idle;
  }
  last_status = current_status; //儲存目前的狀態供下一回合用
  DateTime now = get_time();

  if(digitalRead(3) == 0){
    Count = 0;
    if(print_mode == 0){
      if(Set == Begin || Set == idle){
        Set = HourSetting;
      }
      else  if(Set == HourSetting){
        Set = MinuteSetting;
      }
      else {
        Set = idle;
      }
    }
    else if(print_mode == 1){
      if(Set == idle){
        Set = YearSetting;
      }
      else  if(Set == YearSetting){
        Set = MonthSetting;
      }
      else if(Set == MonthSetting){
        Set = DaySetting;
      }
      else {
        Set = idle;
      }
    }

  }
  delay(200);

  if(Set != idle){
    Setting(Set);
  }



  if(digitalRead(4) == 0){
    if(Set == HourSetting){
      CountHour++;
    }
    else if(Set == MinuteSetting){
      CountMinute++;
    }
    else if(Set == YearSetting){
      CountYear++;
    }
    else if(Set == MonthSetting){
      CountMonth++;
    }
    else if(Set == DaySetting){
      CountDay++;
    }
  }

  if(digitalRead(5) == 0){
    if(Set == HourSetting){
      CountHour--;
    }
    else if(Set == MinuteSetting){
      CountMinute--;
    }
    else if(Set == YearSetting){
      CountYear--;
    }
    else if(Set == MonthSetting){
      CountMonth--;
    }
    else if(Set == DaySetting){
      CountDay--;
    }
  }

  if(Set == Begin){
    NowHour = now.hour();
    NowMinute = now.minute();
    NowYear = now.year();
    NowMonth = now.month();
    NowDay = now.day();
    FinalHour = NowHour;
    FinaMinute = NowMinute;
    FinalYear = NowYear;
    FinaMonth = NowMonth;
    FinalDay = NowDay;
  }
  else {
    
    NowHour = now.hour() + CountHour;
    while(NowHour < 0){
      NowHour = NowHour + 24;
    }
    NowHour = NowHour % 24;

    NowMinute = now.minute() + CountMinute;
    while(NowMinute < 0){
      NowMinute = NowMinute + 60;
    }
    NowMinute = NowMinute % 60;

    NowYear = now.year() + CountYear;
    while(NowYear < 0){
      NowYear = NowYear + 10000;
    }
    NowYear = NowYear % 10000;
    
    NowMonth = now.month() + CountMonth;
    while(NowMonth < 1){
      NowMonth = NowMonth + 12;
    }
    NowMonth = NowMonth % 13;
    if(NowMonth == 0){
      NowMonth++;
    }

    NowDay = now.day() + CountDay;
    while(NowDay < 0){
      NowDay = NowDay + 31;
    }
    NowDay = NowDay % 32;


    FinalHour = NowHour;
    FinaMinute = NowMinute;
    FinalYear = NowYear;
    FinaMonth = NowMonth;
    FinalDay = NowDay;
  }

  if(print_mode == 0)
  {
    print_time(display[FinaMinute],dot,display[FinalHour]);
  
  }
  else if(print_mode == 1)
  {
    print_date(display[FinalDay],display[FinaMonth],display[FinalYear % 100],display[FinalYear / 100 % 100]);
  }
  else if(print_mode == 2)
  {
    get_humidity_and_temperature();
    print_humidity_and_temperature(display[round(humidity)],percent,display[round(temperature)],C);
  }
  else
  {
    //Serial.println(value);
    print_moisture(display[value % 100],display[value / 100 % 100]);
  }
}
DateTime get_time()
{
  return rtc.now();
}
void print_humidity_and_temperature(byte *humidity,byte *percent,byte *temperature,byte *C)
{
  for(int i = 0 ; i < 8 ; i++)
  {
    lc.setRow(3,i,humidity[i]);
    lc.setRow(2,i,percent[i]);
    lc.setRow(1,i,temperature[i]);
    lc.setRow(0,i,C[i]);
  }
}
void print_time(byte *minute, byte *dot, byte *hour)
{
  for(int i = 0 ; i < 8 ; i++)
  {
    lc.setRow(2,i,hour[i]);
    lc.setRow(1,i,dot[i]);
    lc.setRow(0,i,minute[i]);
  }
}
void print_date(byte *day, byte *month, byte *year_right, byte *year_left)
{
  for(int i = 0 ; i < 8 ; i++)
  {
    lc.setRow(3,i,year_left[i]);
    lc.setRow(2,i,year_right[i]);
    lc.setRow(1,i,month[i]);
    lc.setRow(0,i,day[i]);
  }
}
void print_moisture(byte *right, byte *left)
{
  for(int i = 0 ; i < 8 ; i++)
  {
    lc.setRow(1,i,left[i]);
    lc.setRow(0,i,right[i]);
  }
  /*for(int i = 0 ; i < 8 ; i++)
  {
    lc.setRow(2,i,left[i]);
    lc.setRow(1,i,right[i]);
    lc.setRow(0,i,percent[i]);
  }*/
}
void clear_display()
{
  for(int i = 0 ; i < 4 ; i++)
  {
    lc.clearDisplay(i);
  }
}
void AHT10_Reset()
{
  Wire.beginTransmission(AHT10Address);
  Wire.write(0xBA);
  Wire.endTransmission();
  delay(20);
}
void AHT10_Calibrate()
{
  Wire.beginTransmission(AHT10Address);
  Wire.write(eSensorCalibrateCmd, 3);
  Wire.endTransmission();
  delay(500);
}
void get_humidity_and_temperature()
{
  unsigned long result, temp[6];

  Wire.beginTransmission(AHT10Address);
  Wire.write(eSensorMeasureCmd, 3);
  Wire.endTransmission();
  delay(100);

  Wire.requestFrom(AHT10_I2C_ADDR, 6);

  for(unsigned char i = 0; Wire.available() > 0; i++)
  {
    temp[i] = Wire.read();
  }

  temperature = (200 * (((temp[3] & 0x0F) << 16) | (temp[4] << 8) | temp[5])) / 1048576 - 50;
  humidity = (((temp[1] << 16) | (temp[2] << 8) | temp[3]) >> 4) * 100 / 1048576;
}

void Setting(int parameter){
  if(parameter == HourSetting){
    lc.clearDisplay(2);
  }
  else if(parameter == MinuteSetting){
    lc.clearDisplay(0);
  } 
  else if(parameter == YearSetting){
    lc.clearDisplay(3);
    lc.clearDisplay(2);
  }
  else if(parameter == MonthSetting){
    lc.clearDisplay(1);
  }
  else if(parameter == DaySetting){
    lc.clearDisplay(0);
  }
}
