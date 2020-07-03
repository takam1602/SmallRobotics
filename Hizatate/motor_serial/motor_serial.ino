String rotation;
int rotate, rotate1, rotate2 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  rotation = Serial.readString();
   rotate = rotation.toInt();
  if(rotate != 0)
  {
    switch(rotate >= 0 && rotate <= 1255)
    {
      rotate1 = rotate - 1000;
      analogWrite(3,rotate1);
      analogWrite(5,0);  
      Serial.println(rotate1);
      break;
    }
    switch(rotate >= 1256 && rotate <= 2255)
    {
      rotate2 = rotate - 2000;
      analogWrite(3,0);
      analogWrite(3,rotate2);
      Serial.println(rotate2); 
    }
    switch(rotate >= 2256)
    {
      Serial.println("err");
    }  
  }
  else
  {
  
  }

}
