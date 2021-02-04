
#define MotorP 10
#define MotorN 11
#define Encoder1 2
#define Encoder2 3

  volatile unsigned long tachoBefore = 0;//クランクセンサーの前回の反応時の時間
  volatile unsigned long tachoAfter = 0;//クランクセンサーの今回の反応時の時間
  volatile unsigned long tachoWidth = 0;//クランク一回転の時間　tachoAfter - tachoBefore
  volatile float tachoRpm = 0;//エンジンの回転数[rpm]
double pre_err = 0;
  
  void tacho()
  {
  tachoAfter = micros();//現在の時刻を記録
  tachoWidth = tachoAfter - tachoBefore;//前回と今回の時間の差を計算
  tachoBefore = tachoAfter;//今回の値を前回の値に代入する
  tachoRpm = 60000000.0 / (75*tachoWidth);//タイヤの回転数[rpm]を計算
  }
  
void setup()
{
  Serial.begin(115200);
  pinMode(MotorP,OUTPUT);
  pinMode(MotorN,OUTPUT);
  pinMode(Encoder1,INPUT);
  pinMode(Encoder2,INPUT);
  attachInterrupt(0,tacho,RISING);
}

int PID(int MAX,int MIN,float current,float ref)
{
  double dt = 0.001;
  int Width = MAX-MIN;
  int Pgain= 1;
  int Igain =1;
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
int ref = 90;
int manu = PID(255,10,tachoRpm,ref);
  analogWrite(MotorP,manu);
  analogWrite(MotorN,0);
Serial.print(tachoRpm);
Serial.print(",");
Serial.println(manu);
}
