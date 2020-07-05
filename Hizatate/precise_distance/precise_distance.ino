//ultrasonic sensorの温度補正ver c=331.5+0.6*temp　を使う
//なぜか出力がとびとびになってしまう。センサーからの入力のタイミングの問題だろうか

#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int trg = 3; //pinassignを間違えにくい
int echo = 5;

double duration = 0; //初期化
double distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trg,OUTPUT);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trg,HIGH); //発射
  delayMicroseconds(9);
  digitalWrite(trg,LOW); //発射終わり

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  duration = pulseIn(echo,HIGH);
  duration = duration*0.5*0.0000001; //半分にしてmicrosec2sec
  distance = duration*(331.5+0.6*(t+273.15))*100; //m2cm
  
  Serial.print("Humidity:"); 
  Serial.print(h);
  Serial.print("%\t_");
  Serial.print("Temperature:"); 
  Serial.print(t);
  Serial.print("*C_");
  Serial.print("distance: ");
  Serial.println(distance);


  delay(300);
}
