void setup() {
  // put your setup code here, to run once:
  Serial.begin(11520);
  pinMode(7,INPUT);//7pinにモジュール
}

float degree,dx;
float dt=0.02;//ジャイロモジュールの応答性に依存

void loop() {
  // put your main code here, to run repeatedly:
  
 
  dx=100*analogRead(7);
  
  while(Serial)
  {
    degree+=dx*dt;
    Serial.println("degree");
  }
}
