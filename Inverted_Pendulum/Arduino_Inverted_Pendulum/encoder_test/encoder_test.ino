//void setup() {
//  // put your setup code here, to run once:
//
//  Serial.begin(9600);
//  pinMode(2, INPUT);
//  pinMode(3, INPUT);
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  int x = digitalRead(2) + digitalRead(3);
//  Serial.println(x);
//
//}


//#define PIN_A 2
//#define PIN_B 3
//const int8_t ENCODER_TABLE[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
//volatile bool StatePinA = 1;
//volatile bool StatePinB = 1;
//volatile uint8_t State = 0;
//volatile long Count = 0;
//void setup() {
//  pinMode(PIN_A, INPUT_PULLUP);
//  pinMode(PIN_B, INPUT_PULLUP);
//
//  attachInterrupt(0, ChangePinAB, CHANGE);
//  attachInterrupt(1, ChangePinAB, CHANGE);
//  Serial.begin(9600);
//}
//
//void loop() {
//  Serial.println(Count);
//}
//void ChangePinAB() {
//  StatePinA = PIND & 0b00000100;
//  StatePinB = PIND & 0b00001000;
//  State = (State << 1) + StatePinA;
//  State = (State << 1) + StatePinB;
//  State = State & 0b00001111;
//  Count += ENCODER_TABLE[State];
//}



//
//
////ピン番号宣言
//int const ENCA = 2;
//int const ENCB = 3;
//
////変数の宣言
//byte valenc;
//byte val;
//
//void setup(void) {
//  pinMode(ENCA, INPUT_PULLUP);
//  pinMode(ENCB, INPUT_PULLUP);
//  Serial.begin(9600);
//}
//
//void loop(void) {
//  valenc = valenc << 2 & B00001100;
//  valenc += (digitalRead(ENCA) << 1) + (digitalRead(ENCB));
//
//  /*
//    L 0010 1011 1101 0100
//    R 0001 0111 1110 1000
//  */
//
//  switch (valenc) {
//    //反時計回り
//    case B00000010 : //fallthrough
//    case B00001011 : //fallthrough
//    case B00001101 : //fallthrough
//    case B00000100 :
//      if (val > 0) {
//        val--;
//      }
//      Serial.print("L ");
//      Serial.println(val);
//      break;
//
//    //時計回り
//    case B00000001 : //fallthrough
//    case B00000111 : //fallthrough
//    case B00001110 : //fallthrough
//    case B00001000 :
//      if (val < 255) {
//        val++;
//      }
//      Serial.print("R ");
//      Serial.println(val);
//      break;
//
//    default:
//      break;
//  }
//}
