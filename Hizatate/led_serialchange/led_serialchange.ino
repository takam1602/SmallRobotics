void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}

int brightness;

void loop() {
   brightness = Serial.read();
   
  if(brightness != 0)
  {
    switch(brightness)
    {
      case '0':
      Serial.println("255");
      analogWrite(3,255);
      break;  

      case '1':
      Serial.println("200");
      analogWrite(3,200);
      break;

      case '2':
      Serial.println("150");
      analogWrite(3,150);
      break;

      case '3':
      Serial.println("100");
      analogWrite(3,100);
      break;

      case '4':
      Serial.println("50");
      analogWrite(3,50);
      break;

      case '5':
      Serial.println("25");
      analogWrite(3,25);
      break;

      case '6':
      Serial.println("0");
      analogWrite(3,0);
      break;
      
    }
  }
  else
  {
  
  }

}
