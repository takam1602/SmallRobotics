void setup() {
  // put your setup code here, to run once:
 pinMode(10,INPUT);
 pinMode(11,INPUT);
 pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(10)==HIGH)
  {
    analogWrite(3,255);
  }
  else
  {
    analogWrite(3,0);
  }
  
  if(digitalRead(11)==HIGH)
  {
    analogWrite(3,100);
  }
  else
  {
    analogWrite(3,0);
  }
}
