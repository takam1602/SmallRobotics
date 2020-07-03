void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//レートの設定
  pinMode(7,OUTPUT);
  pinMode(3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7,1);
  if(digitalRead(3)==HIGH)
  {
    Serial.print("1");
  }
  else
  {
    Serial.print("0");
  }
}
