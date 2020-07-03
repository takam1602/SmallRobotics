String rotation;
int rot;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  rotation = Serial.readString();
  rot = rotation.toInt();

  if ( rot != 0) {
    
//    正の向きに回転
    if (rot > 0 && rot <= 255) {
      analogWrite(6, rot);
      analogWrite(9, rot);
      analogWrite(5, 0);
      analogWrite(11, 0);
      Serial.println(rot);
    }

//    逆向きに回転
    else if (rot < 0 && rot >= -255) {
//      プラスの値しか読み込まないことに注意
      rot = -rot;
      analogWrite(5, rot);
      analogWrite(11, rot);
      analogWrite(6, 0);
      analogWrite(9, 0);
      Serial.println(-rot);
    }
  }
}
