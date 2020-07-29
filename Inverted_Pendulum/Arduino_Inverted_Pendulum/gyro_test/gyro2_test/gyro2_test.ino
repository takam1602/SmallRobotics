/* https://www.petitmonte.com/robot/howto_gyro_sensor.html を参考にした。
  ジャイロセンサの出力をみるスケッチ　*/

//  ジャイロの出力は1024以下の非負整数なので、それを角速度に変換する
//感度: 0.67[mV/deg/sec]  //この感度は温度によって変わる。

// 配列作った方が可読性上がる。桁数揃えるのないかな

float baseVol1;
float baseVol2;
float baseVol3;
float baseVol4;
#define MINRATIO 0.999  //ジャイロの値が安定しているか比をとって判別する際使う
#define MAXRATIO 1.001

bool isBaseDecided = false;

void setup() {
  Serial.begin(9600);
}

void loop() {

  if (isBaseDecided == false) {
    //  起動後、A0からの出力が安定したら静止電圧を決めることとする。せいぜい20秒あれば安定するだろう。判断するために比を見る。

    float newVolFor1 = 1;  float oldVolFor1 = 1;
    float newVolFor2 = 1;  float oldVolFor2 = 1;
    float newVolFor3 = 1;  float oldVolFor3 = 1;
    float newVolFor4 = 1;  float oldVolFor4 = 1;

//はじめ十分時間経過後の出力をとる方針であった。しかし、実際にanalogReadしないとおそらく温度が上がらないからダメ。
    do {
      newVolFor1 = analogRead(A0);
      newVolFor2 = analogRead(A1);
      newVolFor3 = analogRead(A2);
      newVolFor4 = analogRead(A3);
      float ratioVol1 = newVolFor1 / oldVolFor1;
      float ratioVol2 = newVolFor2 / oldVolFor2;
      float ratioVol3 = newVolFor3 / oldVolFor3;
      float ratioVol4 = newVolFor4 / oldVolFor4;

      Serial.println(ratioVol1);

      //このifの条件を満たした時に安定したとみなし、静止電圧を決める。

      if ( (ratioVol1 < MAXRATIO && ratioVol1 > MINRATIO) && (ratioVol2 < MAXRATIO && ratioVol2 > MINRATIO) && (ratioVol3 < MAXRATIO && ratioVol3 > MINRATIO) && (ratioVol4 < MAXRATIO && ratioVol4 > MINRATIO)) {
        break;
      }

      //変数をswap
      oldVolFor1 = newVolFor1;
      oldVolFor2 = newVolFor2;
      oldVolFor3 = newVolFor3;
      oldVolFor4 = newVolFor4;
    } while (1);

    //breakによりdo-whileを抜けるとここに来る。ここからここから静止電圧を決める
    int i;
    float volForBaseVol1[100];
    float volForBaseVol2[100];
    float volForBaseVol3[100];
    float volForBaseVol4[100];

    float sumVolForBaseVol1 = 0;
    float sumVolForBaseVol2 = 0;
    float sumVolForBaseVol3 = 0;
    float sumVolForBaseVol4 = 0;
    
    //8秒間、１００個のデータをとり平均する。
    for (i = 0; i < 80; i++) {
      volForBaseVol1[i] = analogRead(A0);
      volForBaseVol2[i] = analogRead(A1);
      volForBaseVol3[i] = analogRead(A2);
      volForBaseVol4[i] = analogRead(A3);

      sumVolForBaseVol1 += volForBaseVol1[i];
      sumVolForBaseVol2 += volForBaseVol2[i];
      sumVolForBaseVol3 += volForBaseVol3[i];
      sumVolForBaseVol4 += volForBaseVol4[i];

      delay(100);
    }


    baseVol1 = sumVolForBaseVol1 / 1023.0 * 5 / 80;
    baseVol2 = sumVolForBaseVol2 / 1023.0 * 5 / 80;
    baseVol3 = sumVolForBaseVol3 / 1023.0 * 5 / 80;
    baseVol4 = sumVolForBaseVol4 / 1023.0 * 5 / 80;

    //静止電圧をシリアル表示
    Serial.print("baseVol1 = ");
    Serial.println(baseVol1);
    Serial.print("baseVol2 = ");
    Serial.println(baseVol2);
    Serial.print("baseVol3 = ");
    Serial.println(baseVol3);
    Serial.print("baseVol4 = ");
    Serial.println(baseVol4);

    isBaseDecided = true;
  }

//ここから計測する。
  else if (isBaseDecided == true) {

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
}
