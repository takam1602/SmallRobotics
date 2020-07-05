//ultrasonic sensorの温度補正ver c=331.5+0.6*temp　を使う
#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 2
#define DHTTYPE DHT11
#define trg 3
#define echo 5

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DHT dht(DHTPIN, DHTTYPE);


double duration = 0; //初期化
double distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo,INPUT);
  pinMode(trg,OUTPUT);
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
//超音波センサ
  digitalWrite(trg,HIGH); //発射
  delayMicroseconds(9);
  digitalWrite(trg,LOW); //発射終わり
  duration = pulseIn(echo,HIGH);

//温湿度度計  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

//演算
  duration = duration*0.5*0.000001; //半分にしてmicrosec2sec
  distance = duration*(331.5+0.6*t)*100; //m2cm

//LCD表示。もっとスマートなやり方ありそう
  lcd.setCursor(0,0);
  lcd.print(t);
  lcd.setCursor(5,0);
  lcd.print("*C");

  lcd.setCursor(9,0);
  lcd.print(h);
  lcd.setCursor(14,0);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("D:");
  lcd.setCursor(2,1);
  lcd.print(distance);
  lcd.setCursor(7,1);
  lcd.print("CM");

  delay(300);
}
