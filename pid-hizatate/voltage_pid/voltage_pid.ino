const float Target=3;//目標電圧
const float Kp=10;//比例ゲイン
const float Ki=0;//積分ゲイン
const float Kd=0.1;//微分ゲイン

float x;
float dt;
float pretime;//過去時間
float P, I, D, preP;
char buf[100];
uint8_t duty;

uint8_t a;
uint8_t b;

void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT);

}

void loop() {
  analogWrite(10, duty);
  for(int i=0;i<1000;i++){
  x+=analogRead(A0);
  }
  x=5*x/1000/1023;

  
  dt =(micros() - pretime)/1000000;
  pretime = micros();
  P=Target-x;
  I+=P*dt;
  D=(P-preP)/dt;
  preP=P;
  
  duty+= Kp*P+Kd*D+Ki*I;

  Serial.println(x);

}
