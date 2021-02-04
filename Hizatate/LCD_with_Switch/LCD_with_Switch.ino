
#include <LiquidCrystal.h>

// rs:7 en:8 d4:9 d5:10 d6:11 d7:12　に対応
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(A0,INPUT);
  pinMode(1,INPUT_PULLUP);
pinMode(2,INPUT_PULLUP);
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("ref:");
lcd.setCursor(0, 1);
lcd.print("rpm:");
}


void loop() {
 static int ref = 130;
  int Switch  = digitalRead(1);
  int Switch2 = digitalRead(2);
if(Switch == LOW)
{
  ref+=1;
}
else{
}
if(Switch2 == LOW)
{
  ref-=1;
}
else{
}



  
lcd.setCursor(4, 0);
lcd.print(ref);
lcd.setCursor(4, 1);
lcd.print("tacho");

}
