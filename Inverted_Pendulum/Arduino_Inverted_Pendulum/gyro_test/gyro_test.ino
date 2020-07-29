/* https://www.petitmonte.com/robot/howto_gyro_sensor.html を参考にした。
  ジャイロセンサの出力をみるスケッチ　*/

//  ジャイロの出力は1024以下の非負整数なので、それを角速度に変換する
//感度: 0.67[mV/deg/sec]

float baseVol1 = 1.35;
float baseVol2 = 1.35;

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (( millis() > 1000 ) && ( millis() < 4000 )) {
    //  起動後1〜4秒は静止時出力を決める。出力の平均値を取る
    int i;
    float volForBaseVol1[300];
    float volForBaseVol2[300];
    float sumVolForBaseVol1 = 0;
    float sumVolForBaseVol2 = 0;

    for ( i = 0; i < 300; i++ ) {
      volForBaseVol1[i] = analogRead(A0);
      volForBaseVol2[i] = analogRead(A1);
      sumVolForBaseVol1 += volForBaseVol1[i];
      sumVolForBaseVol2 += volForBaseVol2[i];
      i++;
      delay(20);
    }

    //確からしい値にするために二倍しているが、なぜこうなってしまうのか？そして、Serial.printが２回もされてしまうのが意味不明。
    baseVol1 = sumVolForBaseVol1 / 1023.0 * 5 / 300 * 2;
    baseVol2 = sumVolForBaseVol2 / 1023.0 * 5 / 300 * 2;
    Serial.print("baseVol1 = ");
    Serial.println(baseVol1);
    Serial.print("baseVol2 = ");
    Serial.println(baseVol2);
  }

  else if ( millis() >= 4000 ) {

    // ジャイロ(G1)
    float voltage = analogRead(A0) / 1023.0 * 5;  // voltageは０〜５をとる
    //    voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て
    Serial.print("G1:");
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("角速度:");
    Serial.print((voltage - baseVol1) * 1000 / 0.67);
    Serial.print(" deg/sec  ");

    // ジャイロ(G2)
    voltage = (analogRead(A1) / 1023.0) * 5;
    //    voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て
    Serial.print("G2:");
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("角速度:");
    Serial.print((voltage - baseVol2) * 1000 / 0.67);
    Serial.println(" deg/sec");
    delay(3000);
  }

  else {
  }

}
