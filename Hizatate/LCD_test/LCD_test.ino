
#include <LiquidCrystal.h>

// rs:7 en:8 d4:9 d5:10 d6:11 d7:12　に対応
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
// LCDの行と列を設定
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("ref:");
lcd.setCursor(0, 1);
lcd.print("rpm:");
}

void loop() {
  
}
