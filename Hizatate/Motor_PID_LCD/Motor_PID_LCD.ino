
#include <LiquidCrystal.h>

// rs:7 en:8 d4:9 d5:10 d6:11 d7:12　に対応
LiquidCrystal lcd(7, 8, 9, 13, 11, 12);
volatile unsigned long tachoBefore = 0;//クランクセンサーの前回の反応時の時間
  volatile unsigned long tachoAfter = 0;//クランクセンサーの今回の反応時の時間
  volatile unsigned long tachoWidth = 0;//クランク一回転の時間　tachoAfter - tachoBefore
  volatile float tachoRpm = 0;//エンジンの回転数[rpm]
double pre_err = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(1,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("ref:");
lcd.setCursor(0, 1);
lcd.print("rpm:");
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  attachInterrupt(0,tacho,RISING);
}

 

  void tacho()
  {
  tachoAfter = micros();//現在の時刻を記録
  tachoWidth = tachoAfter - tachoBefore;//前回と今回の時間の差を計算
  tachoBefore = tachoAfter;//今回の値を前回の値に代入する
  tachoRpm = 60000000.0 / (75*tachoWidth);//タイヤの回転数[rpm]を計算
  }
  

int PID(int MAX,int MIN,float current,float ref)
{
  double dt = 0.001;
  int Width = MAX-MIN;
  int Pgain= 15;
  int Igain =2;
  int Dgain =0;
  static double P = 0;
  static double I = 0;
  static double D = 0;
  static double controll = 0;
  double err = ref - current;
  P = Pgain*err;
  I += Igain*err*dt;
  D = Dgain*(err-pre_err)/dt;
  controll = P + I + D;

  if(controll > MAX)
  {
    return MAX; 
    }
  if(controll < MIN)
  {
    return MIN;
  }
  if(controll < MAX && controll > MIN)
  {
  return controll;
  }
  pre_err = err;
 }


void loop()
{
   static int ref = 130;
  int Switch  = digitalRead(1);
  int Switch2 = digitalRead(10);
if(Switch == LOW)
{
  ref+=1;
}
else{
}
if(Switch2 == LOW)
{
  ref-=1;
}
else{
}

int manu = PID(255,10,tachoRpm,ref);
  analogWrite(5,manu);
  analogWrite(6,0);
Serial.println();
  lcd.setCursor(4, 0);
lcd.print(ref);
lcd.setCursor(4, 1);
lcd.print(tachoRpm);

}
