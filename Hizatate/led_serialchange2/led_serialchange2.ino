String rotation;
int rotate, rotate1, rotate2 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  rotation = Serial.readString();
  rotate = rotation.toInt();
  rotate1 = rotate - 1000;
  rotate2 = rotate - 2000;

  if (rotate >= 1000 && rotate <= 1255)
  {
    analogWrite (5, rotate1);
    analogWrite(9, rotate1);
    analogWrite (6, 0);
    analogWrite(10, 0);
    Serial.print (rotate1);
    Serial.println("right");
  }
  else if (rotate >= 2000 && rotate <= 2255)
  {
    analogWrite (5, 0);
    analogWrite (9, 0);
    analogWrite (6, rotate2);
    analogWrite (10, rotate2);
    Serial.print (rotate2);
    Serial.println("left");
  }
  else if (rotate >= 2256 && rotate <= 999)
  {
    Serial.println ("err");
    analogWrite (5, 0);
    analogWrite (9, 0);
    analogWrite (6, 0);
    analogWrite (10, 0);
  }


}
