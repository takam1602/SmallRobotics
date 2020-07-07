/* https://www.petitmonte.com/robot/howto_gyro_sensor.html を参考にした。
  ジャイロセンサの出力をみるスケッチ　*/

//  ジャイロの出力は1024以下の非負整数なので、それを角速度に変換する
//感度: 0.67[mV/deg/sec]

// 配列作った方が可読性上がる。桁数揃えるのないかな

float baseVol1 = 1.85;
float baseVol2 = 1.94;
float baseVol3 = 1.41;
float baseVol4 = 1.42;

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (( millis() > 3000 ) && ( millis() < 4000 )) {
    //  起動後1〜4秒は静止時出力を決める。出力の平均値を取る
    int i;
    float volForBaseVol1[100];
    float volForBaseVol2[100];
    float volForBaseVol3[100];
    float volForBaseVol4[100];

    float sumVolForBaseVol1 = 0;
    float sumVolForBaseVol2 = 0;
    float sumVolForBaseVol3 = 0;
    float sumVolForBaseVol4 = 0;

    for ( i = 0; i < 70; i++ ) {

      volForBaseVol1[i] = analogRead(A0);
      volForBaseVol2[i] = analogRead(A1);
      volForBaseVol3[i] = analogRead(A2);
      volForBaseVol4[i] = analogRead(A3);

      sumVolForBaseVol1 += volForBaseVol1[i];
      sumVolForBaseVol2 += volForBaseVol2[i];
      sumVolForBaseVol3 += volForBaseVol3[i];
      sumVolForBaseVol4 += volForBaseVol4[i];

      i++;
      delay(100);
    }

    //確からしい値にするために二倍しているが、なぜこうなってしまうのか？そして、Serial.printが２回もされてしまうのが意味不明。
    baseVol1 = sumVolForBaseVol1 / 1024.0 * 5 / 70 * 2;
    baseVol2 = sumVolForBaseVol2 / 1024.0 * 5 / 70 * 2;
    baseVol3 = sumVolForBaseVol3 / 1024.0 * 5 / 70 * 2;
    baseVol4 = sumVolForBaseVol4 / 1024.0 * 5 / 70 * 2;
    Serial.print("baseVol1 = ");
    Serial.println(baseVol1);
    Serial.print("baseVol2 = ");
    Serial.println(baseVol2);
    Serial.print("baseVol3 = ");
    Serial.println(baseVol3);
    Serial.print("baseVol4 = ");
    Serial.println(baseVol4);

  }

  else if ( millis() >= 10000 ) {

    // ジャイロ1(G1)
    float voltage = analogRead(A0) / 1023.0 * 5;  // voltageは０〜５をとる
    //    voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て
    Serial.print("G1:");
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("角速度:");
    Serial.print((voltage - baseVol1) * 1000 / 0.67);
    Serial.print(" deg/sec  ");

    // ジャイロ1(G2)u
    voltage = analogRead(A1) / 1023.0 * 5;
    //    voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て
    Serial.print("G2:");
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("角速度:");
    Serial.print((voltage - baseVol2) * 1000 / 0.67);
    Serial.print(" deg/sec  ");

    // ジャイロ2(G1)
    voltage = analogRead(A2) / 1023.0 * 5;  // voltageは０〜５をとる
    //    voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て
    Serial.print("G3:");
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("角速度:");
    Serial.print((voltage - baseVol3) * 1000 / 0.67);
    Serial.print(" deg/sec  ");

    // ジャイロ2(G2)
    voltage = analogRead(A3) / 1023.0 * 5;
    //    voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て
    Serial.print("G4:");
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("角速度:");
    Serial.print((voltage - baseVol4) * 1000 / 0.67);
    Serial.println(" deg/sec");

    delay(500);

  }

  else {
  }

}
