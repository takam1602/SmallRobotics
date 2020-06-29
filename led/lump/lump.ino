const int SENSOR = 0;
const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;
const int BUTTON = 12;

int val = 0;
int btn = LOW;
int old_btn = LOW;
bool isOn = false;
char buffer[7];
int pointer = 0;
byte inByte = 0;

byte r = 0;
byte g = 0;
byte b = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop() {
  val = analogRead(SENSOR);
  Serial.println(val);

  if ( Serial.available() > 0) {
    inByte = Serial.read();
  }

  if ( inByte == '#' ) {
    while ( pointer < 6 ) {
      buffer[pointer] = Serial.read();
      pointer++;
    }
    r = hex2dec(buffer[1]) + hex2dec(buffer[0]);
    g = hex2dec(buffer[3]) + hex2dec(buffer[2]);
    b = hex2dec(buffer[5]) + hex2dec(buffer[4]);

    pointer = 0;
  }

  btn = digitalRead(BUTTON);
  if ( (btn == HIGH) && (old_btn == LOW)) {
    isOn = !isOn;
  }

  old_btn = btn;

  if ( isOn == true ) {
    analogWrite(R_LED, r);
    analogWrite(G_LED, g);
    analogWrite(B_LED, b);
  }
  else {
    analogWrite(R_LED, 0);
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
  }
  delay(100);
}

int hex2dec(byte c) {
  if ( c >= '0' && c <= '9' ) {
    return c;
  }
  else if (c >= 'A' && c <= 'F' ) {
    return c - 'A' + 10;
  }
}
