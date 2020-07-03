String brightness;
int brt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}

void loop() {
  brightness = Serial.readString();
   brt = brightness.toInt();
  if(brt != 0)
  {
    if(brt >= 0 && brt <= 255)
    {
      analogWrite(3,brt);  
      Serial.println(brt);
    }
    else
    {
      analogWrite(3,0);
      Serial.println("err"); 
    }
  }
  else
  {
  
  }

}
