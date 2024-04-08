//const byte SEG_PIN[2]={8, 9};            // 7段顯示器的控制接腳(D1, D2)
const byte NUM_OF_SEG = 2; // 7段顯示器的數量
int Number = 0;
int Bits = 0;
byte Digits[2] = {0, 0};//個位數 和 十位數
int initial_BCD[4] = {0,0,0,0};
int i = 0;
int j = 0;
const byte DataPin = 2;    // 74HC595序列輸入
const byte LatchPin = 3;   // 74HC595暫存器時脈
const byte ClockPin = 4;   // 74HC595序列時脈

unsigned long PreviousMillis = 0;
const long Interval = 1000; 

int color = 0;

void display_color(uint8_t);

void check(uint8_t,uint8_t);

void sendone();

void sendzero();

void sendpixel(uint8_t,uint8_t,uint8_t);

void print();

// 每隔一秒數字加1並拆解數字
void Counter(){
  unsigned long CurrentMillis = millis();
  if(CurrentMillis - PreviousMillis >= Interval){// 每隔1秒執行一次底下的條件式內容
    PreviousMillis = CurrentMillis;
    Number++;
    if(Number % 5 == 0)
    {
      color = (color + 1) % 7;
    }
    if(Number > 99){//若超過99則歸零
      Number = 0;
    }
    Digits[0]= Number % 10;// 個位數
    Digits[1]= (Number / 10) % 10;// 十位數
  }
  //Serial.print(Number);
  //Serial.print("\n");
}

void Display(){
  byte Num;
  // 逐一設定每個七段顯示器
  for(byte i=0; i<2; i++){
    Num = Digits[i];
    digitalWrite(LatchPin, LOW);
    

    
    if(i==0){
      digitalWrite(ClockPin, LOW);
      digitalWrite(DataPin, 1);//D2
      //Serial.print("1");
      digitalWrite(ClockPin, HIGH);

      digitalWrite(ClockPin, LOW);
      digitalWrite(DataPin, 0);//D1
      //Serial.print("0");
      digitalWrite(ClockPin, HIGH);

    }
    else{
      digitalWrite(ClockPin, LOW);
      digitalWrite(DataPin, 0);//D2
      //Serial.print("0");
      digitalWrite(ClockPin, HIGH);

      digitalWrite(ClockPin, LOW);
      digitalWrite(DataPin, 1);//D1
      //Serial.print("1");
      digitalWrite(ClockPin, HIGH);
    }
    
    digitalWrite(ClockPin, LOW);
    digitalWrite(DataPin, 0);//dp
    //Serial.print("0");
    digitalWrite(ClockPin, HIGH);
    
    Bits = floor(log(Num)/log(2)); 
    while(Bits){
      /*digitalWrite(ClockPin, LOW);
      digitalWrite(DataPin, (Num >> Bits) & 1);
      Serial.print((Num >> Bits) & 1);
      digitalWrite(ClockPin, HIGH);
      Bits--;*/
      initial_BCD[Bits] = (Num >> Bits) & 1;
      Bits--;
    }
    initial_BCD[Bits] = Num & 1;
    for(j=3; j>=0 ; j--){
      digitalWrite(ClockPin, LOW);
      digitalWrite(DataPin, initial_BCD[j]);
      //Serial.print(initial_BCD[j]);
      digitalWrite(ClockPin, HIGH);
      initial_BCD[j] = 0;
    }
    /*digitalWrite(ClockPin, LOW);
    digitalWrite(DataPin, Num & 1);
    Serial.print(Num & 1);
    digitalWrite(ClockPin, HIGH);*/
    digitalWrite(ClockPin, LOW);
    digitalWrite(DataPin, 0);//DIN
    //Serial.print("0");
    digitalWrite(ClockPin, HIGH);

    digitalWrite(LatchPin, HIGH);
    //Serial.print("\n");
    //digitalWrite(SEG_PIN[i], LOW);     // 點亮此顯示器
    delay(5);//5

    /*for (byte j=0; j<NUM_OF_SEG; j++) {
      digitalWrite(SEG_PIN[j], HIGH);  // 關閉所有顯示器
    }*/
  }
}

void setup() {
  pinMode(LatchPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(DataPin, OUTPUT);  
  /*for(byte i=0; i<NUM_OF_SEG; i++) {
    pinMode(SEG_PIN[i], OUTPUT);
    digitalWrite(SEG_PIN[i], HIGH);
  }*/
}

void loop() {
  //Serial.begin(9600);
  print();
  Counter();
  Display();
  //delay(10);
}

void print()
{
  switch(color)
  {
    case 0:
      sendpixel(255,0,0);   //紅RGB
      break;
    case 1:
      sendpixel(255,127,0); //橙RGB
      break;
    case 2:
      sendpixel(255,255,0); //黃RGB
      break;
    case 3:
      sendpixel(0,255,0);   //綠RGB
      break;
    case 4:
      sendpixel(0,0,255);   //藍RGB
      break;
    case 5:
      sendpixel(75,0,130);  //靛RGB
      break;
    case 6:
      sendpixel(148,0,211); //紫RGB
      break;
    default:
      break;
  }
}

void display_color(uint8_t color)   //將顏色值傳入檢查函式，檢查每一個位元是不是1。
{
    check(color,0x80);
    check(color,0x40);
    check(color,0x20);
    check(color,0x10);
    check(color,0x08);
    check(color,0x04);
    check(color,0x02);
    check(color,0x01);
}

void check(uint8_t a,uint8_t b)
{
    if(a & b)
    {
        sendone(); //是1就傳送1
    }
    else
    {
        sendzero(); //否則傳送0
    }
}

void sendone() //要傳送1進去，WS2812b的電壓要是高電位2段，低電位1段。
{
    PORTD = 0b00000100;
    PORTD = 0b00011100;
    PORTD = 0b00000100;

    PORTD = 0b00000100;
    PORTD = 0b00011100;
    PORTD = 0b00000100;

    PORTD = 0b00000000;
    PORTD = 0b00011000;
    PORTD = 0b00000000;
}

void sendzero() //要傳送1進去，WS2812b的電壓要是高電位1段，低電位2段。
{
    PORTD = 0b00000100;
    PORTD = 0b00011100;
    PORTD = 0b00000100;

    PORTD = 0b00000000;
    PORTD = 0b00011000;
    PORTD = 0b00000000;

    PORTD = 0b00000000;
    PORTD = 0b00011000;
    PORTD = 0b00000000;
}

void sendpixel(uint8_t r,uint8_t g,uint8_t b)
{
    //WS2812b的順序是G、R、B
    display_color(g);
    display_color(r);
    display_color(b);

    //傳送完G、R、B後要做reset，傳送24個bit的0。
    display_color(0);
    display_color(0);
    display_color(0);
    //delay(5000);
}