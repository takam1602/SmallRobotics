//ultrasonic sensorのお試しコード

int trg = 3; //pinassignを間違えにくい
int echo = 5;

double duration = 0; //初期化
double distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trg,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trg,LOW);　//試し打ち
  delayMicroseconds(1);

  digitalWrite(trg,HIGH);　//11microsec発射
  delayMicroseconds(11);

  digitalWrite(trg,LOW); //発射終わり

  duration = pulseIn(echo,HIGH);
  distance = duration*0.017;　//音速340m/sとして、音波が返ってくるまでの時間の半分が距離

  Serial.println(distance);

  

}
