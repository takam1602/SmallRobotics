void setup() {
  // put your setup code here, to run once:
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(8,OUTPUT);
pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(3)==HIGH)
  {
    digitalWrite(7,1);
  }
  else
  {
    digitalWrite(7,0);
  }

    if(digitalRead(4)==HIGH)
  {
    digitalWrite(8,1);
  }
  else
  {
    digitalWrite(8,0);
  }
    
}
