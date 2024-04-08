#include"library.h"
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include<Wire.h>
#include<RTClib.h>

SoftwareSerial esp8266_Serial(7,6);//設定Pin7 RX , Pin6 TX
WiFiEspClient esp_client;
RTC_DS1307 rtc; //建立 RTC 物件

const char* host = "maker.ifttt.com";
int connect_status = WL_IDLE_STATUS;
String tempe1="";
String humid1=""; 
String Soil_humidity = "";
String date1="";
String year = "";
String month = "";
String day = "";
String hour = "";
String minute = "";
float temperature,humidity; //溫度及濕度，為float型態。
int sensorValue;

int Fan_Mode = 0;
bool Fan_Open = false;
bool check_temperature = false;
unsigned long pre_time = 0,current_time = 0;

const unsigned char eSensorCalibrateCmd[3] = {0xE1, 0x08, 0x00},eSensorMeasureCmd[3] = {0xAC, 0x33, 0x00}; //分別是校準、測量 AHT10 用的3個位址

String ipAddressToString(const IPAddress& ipAddress ) {
       return String(ipAddress[0]) + String(".")+
       String(ipAddress[1]) + String(".")+
       String(ipAddress[2]) + String(".")+
       String(ipAddress[3]);
}

void initial(){
  Wire.begin(0);
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(9,OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(PWM_Button, INPUT_PULLUP);
  analogWrite(fan,0);
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
  esp8266_Serial.begin(9600);
  esp8266_Serial.listen();
  WiFi.init(&esp8266_Serial); 
  if(WiFi.status() == WL_NO_SHIELD) {
   //Serial.println(F("Esp8266 module no present"));
   while(true);
   }
  while(connect_status != WL_CONNECTED) {
   //Serial.println(F("Connect to router..."));
   //connect_status = WiFi.begin("D-Link_DIR-612","0923633693");
   //connect_status = WiFi.begin("iPhone100","12345678");
   //connect_status = WiFi.begin("Ncue_Media_Lab","20171020");
   //connect_status = WiFi.begin("Ncue_Media_Lab","20171020");
   connect_status = WiFi.begin("IOTlabE208","047232105");
   delay(2000);
  }
  ipAddressToString(WiFi.localIP());
  //Serial.println((ipAddressToString(WiFi.localIP())));
}

void run(){
  current_time = millis();
  if(current_time - pre_time >= 5000)
  {
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    Serial.write(sensorValue / 256);
    Serial.write(sensorValue % 256);
    Serial.flush();
    pre_time = current_time;
  }
  //Serial.print("value:");
  //Serial.println(String(sensorValue));
  
    //date1 = "";
    DateTime now = get_time();
    
    if(now.minute() % 2)
    {
      check_temperature = true;
      //Serial.println("text");
    }
    if(now.minute() % 2 == 0 && check_temperature)
    {
      get_humidity_and_temperature();//讀取溫濕度
      Serial.println("Enter function");
      if(temperature >= 23 || sensorValue >= 870)
      {
        //digitalWrite(9,HIGH);
        analogWrite(fan,255);
        Fan_Open = true;
        Fan_Mode = 2;
        //Serial.println("HIGH");
        //Serial.print("value:");
        //Serial.println(humidity);
        
        Serial.println("Hello");
        delay(1000);
        year = now.year();
        month = now.month();
        day = now.day();
        hour = now.hour();
        minute = now.minute();
        date1 = "";
        date1.concat(year);
        date1.concat("/");
        date1.concat(month);
        date1.concat("/");
        date1.concat(day);
        date1.concat("/");
        date1.concat(hour);
        date1.concat(":");
        date1.concat(minute);
        //Serial.println(date1);
        Wi_Fi();
      }
      else
      {
        //digitalWrite(9,LOW);
        analogWrite(fan,0);
        Fan_Open = false;
        Fan_Mode = 0;
        //Serial.println("LOW");
      }
      check_temperature = false;
    }
    //delay(500);

  if(digitalRead(PWM_Button) == 0){
    if(Fan_Open == true){
      if(Fan_Mode == 2){
        Fan_Mode = 1;
        analogWrite(fan,128);
      }
      else if(Fan_Mode == 1){
        Fan_Mode = 0;
        analogWrite(fan,0);
      }
      else {
        Fan_Mode = 2;
        analogWrite(fan,255);
      }
    }
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

DateTime get_time()
{
  return rtc.now();
}

void Wi_Fi()
{
  if(esp_client.connect("maker.ifttt.com",80))
  {
    //Serial.println("test0");

    //esp8266_Serial.listen();
    //Serial.println("test");
    delay(2000);
    //Serial.println("test");
    tempe1 = String(temperature);
    humid1 = String(humidity);
    humid1.concat("%");
    Soil_humidity = String(sensorValue);
    //Serial.println("test2");
    String getStr_line = "GET /trigger/Line_msg/with/key/b9VH4cx4u1h_nWIDVzfB2V?value1="+tempe1+"&value2="+humid1+",Soil_humidity:"+Soil_humidity+"&value3="+date1+" HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: BuildFailureDetectorESP32\r\n" + "Connection: close\r\n\r\n";
    //Serial.println("test3");
    //Serial.println(getStr_line);
    esp_client.print(getStr_line);
    esp_client.stop();
  }
}
