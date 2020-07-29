# <div style="text-align: center;">The Way to the *" Wheeled Inverted Pendulum "* </div>
###  <div style="text-align: center;"> κΥσ </div>
###  <div style="text-align: center;"> 2020.06.30 ~ 2020.08.31 </div>  

## Index

1. Ingredient
2. MVP
3. Improvement
4. Add Sensors
5. Kalman Filter
6. Operate with IR
7. 3D Mechanic Model
8. Another Way to Keep Balance - joint
9. Run Outside
10. Micheal Jackson
11. Equipped with a Smartphone
11. Apply to a Segway
12. Identified Flying Object  
  
  　  　      
  
            
## 1. Ingredient
 - 1 点 タミヤ 楽しい工作シリーズ No.157 ユニバーサルプレート 2枚セット (70157)
 - 1 点 タミヤ 楽しい工作シリーズ No.168 ダブルギヤボックス 左右独立4速タイプ
 - 1 点 タミヤ 楽しい工作シリーズ No.157 ユニバーサルプレート 2枚セット (70157)
 - 1 点 Arduinoをはじめよう 第3版 (Make:PROJECTS), Massimo Banzi
 - 1 点 Arduinoをはじめようキット
 - 1 点 タミヤ 楽しい工作シリーズ No.145 ナロータイヤセット 58mm径 (70145)
 - 2 点 タミヤ 楽しい工作シリーズ No.151 単3電池ボックス 2本用 スイッチ付 (70151)
 - 1 点 タミヤ 楽しい工作シリーズ No.143 ユニバーサルアームセット (70143)
 - 1 点 モータードライバー　TA7291P　2個セット
 - 1.【K-04912】小型圧電振動ジャイロモジュール
  
  
　 
　      
## 2. MVP
　[半日で作る倒立振子](https://www.instructables.com/id/半日で作る倒立振子/)
に従って取り敢えず簡単なものを作った。計算は全てArduino上で完結させる。そのためスケッチは1つ。ジャイロは一つだけ用いる。基本的な構造はどのサイトも一緒。処女作なので慎重にやった。配線のところは難しい。  
  
  
【組み立て編】  
　ギアボックスを組み立てました。
ギア比はTypeCの 114.7 : 1 回転トルク809gf•cm 回転数115rpm
細かい・複雑・固い・図面分かりにくい・間違えたら面倒、で1時間以上かかった。細かい設計は説明書をみよ。mmで設計を指定してくるが、それに従わないと後悔することになるぞ。  
[ギアボックス組み立て前](pictures/IMG_7443.jpeg)   
[ギアボックス完成](pictures/IMG_7444.jpeg) 

　タイアを組み立てて、ギアとつなげてみました。嬉しい。タイアの匂いがして良いタイアだと思った。  
[タイア組み立て前](pictures/IMG_7445.jpeg)   
[タイア完成](pictures/IMG_7446.jpeg) 

　ユニバーサルプレートに切り込みを入れました。L字アームをくっつけました。  
 [ユニバーサルプレート組み立て前](pictures/IMG_7452.jpeg)   
[ユニバーサルプレート完成](pictures/IMG_7453.jpeg)  

　電池ボックスを組み立てた。細かい。電池２個×２でスイッチも２個ある。左右スイッチ1つずつつけるということでしょう。  
　[スイッチ組み立て前](pictures/IMG_7454.jpeg)
　[スイッチ組み立て途中](pictures/IMG_7455.jpeg)    
　[スイッチ完成](pictures/IMG_7456.jpeg)  

　ここに来てギアからポロリ。やり直しファック。[ポロリお宝画像はこちら](pictures/IMG_7457.jpeg)  
　 配線を一気に進めました。電源はUSBから供給してるため、半田付けはいらなかったです。  
　   
　     
　       
【動かしてみる】  
　 まずはモーターだけ動かす。最初は片方の車輪、次に両車輪、そして逆回転という３段階で進めました。シリアル通信でキーボードから入力した値をモータ出力としました。  ポイントは、「全てのピンの役割を意識せよ。」これに限ります。  
　 モーターは2つのリード線に繋がっていて、逆にすると逆回転します。プラスを(6,9)、GNDを(5,11)とすると正の向き、プラスを(5,11)、GNDを(6,9)とすると逆向きに回転させるのが次のスケッチ。入力した値の正負と回転の向きを対応づけています。しかし、マイナスの値はプラスにしてやらないとアナログ入力できません。そこは if 文で分けて絶対値を取るようにします。
　

``` c 
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
    if (rot > 0 && rot <= 255) {
      analogWrite(6, rot);
      analogWrite(9, rot);
      analogWrite(5, 0);
      analogWrite(11, 0);
      Serial.println(rot);
    }
    else if (rot < 0 && rot >= -255) {
//      プラスの値しか読み込まない
      rot = -rot;
      analogWrite(5, rot);
      analogWrite(11, rot);
      analogWrite(6, 0);
      analogWrite(9, 0);
      Serial.println(-rot);
    }
  }
}
```

　これで上手く行きます。しかし、モーターの回転する速度が左右違う。それに、キーボードで入力してからそれが反映されるのに時間がかかる。原因はいくつか考えられ、これを改善する方法も複数ある。  
　回転速度の違いを解消するために、モータードライバを左右で同じものを使うことにした。すると、回転速度が一致した。並列につなぐ分、回転速度は当然落ちた。USBではなく電池にすることで回転速度の差が小さくなるかも？  
　  
　    




* ジャイロモジュールの出力をテストしてみた。  

```c  
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
```  

　同じジャイロでも、静止出力が毎回違う。ここを何らかの方法で補正しないと使い物にならない。また、付属説明書には静止出力1.35 [Vdc]となっていたが、大体 3 [Vdc]だった。ここまでずれる原因がわからない。
　そこで、起動から4秒間は静止させておき、1-４秒の出力の平均値を静止出力とした。
　未解決問題はコメントに残しておいた。  
　  
　  石井先生に聞きにいきました。  
　  ジャイロの静止電圧1.35Vdcというのは、ジャイロそのものの性能のこと。ジャイロモジュールにはオペアンプなどのフィルターが噛まされており、実際には2.5Vdcとかになる。  
　  ジャイロに電流が流れると温度が上昇し、精子電圧や感度といった定数が変わるので、静止電圧を決める前にあっためておく必要がある。温める際、実際にanalogReadする必要がある。そこで、隣り合うセンサ値の比をとって、それがある値におさまるまで待って、そこから静止電圧を決めてやることにした。
　  定数に意味はない。ジャイロの出力値と制御するエンコーダの入力値を決めておけば、感度などが変わっても関係ない。フィードバック。
　

　  
　次にロータリエンコーダ（ノンクリックタイプ）をテストした。  
　重要そうな特徴  
　　* 1個90円  
　　* 回転トルク25±15mN•m  
　　* 24パルス （分解能とは、軸を一回転させた場合に出力されるパルス数である）    
　信号を取るのに苦戦した。まずは仕様を理解する必要がある。倒立振子に組み込む際にそのままだと非常に硬い点と、タイアにどう付けるかという点で工夫が必要である。  
　  
　テストコード

　``` c
　
　```

　    




倒立振子走行用プログラム  

``` c

/* "A very easy and simple inverted pendulum balancing robot" You need only half a day to make it, if you have some Materials.
  Copyright (C) 2014 ArduinoDeXXX All Rights Reserved. */

#include <MsTimer2.h>

volatile int i = 0;
volatile byte countS = 0;
long zeroOmegaI = 0;
volatile int recOmegaI[10];
volatile int omegaI = 0;
volatile long thetaI = 0;
volatile long sumPower = 0;
volatile long sumSumP = 0;

//パラメータ重み付け係数
const int kAngle = 45;
const int kOmega = 85;
const long kSpeed = 57;
const long kDistance = 60;

volatile long powerScale;
volatile int power;
volatile long vE5 = 0;
volatile long xE5 = 0;


void setup () {
  Serial .begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  for ( i = 0 ; i < 10 ; i++ ) {
    recOmegaI[i] = 0;
    delay(300);
  }

  training();
  MsTimer2::set(5, chkAndCtl);
  MsTimer2::start();
}


void loop () {

  //モーター正回転
  if ( power > 0 ) {
    analogWrite( 6, power );
    digitalWrite( 4, HIGH );
    digitalWrite( 5, LOW );
    analogWrite( 9, power );
    digitalWrite( 7, HIGH );
    digitalWrite( 8, LOW );
  }
  //  モーター逆回転
  else {
    analogWrite( 6, - power );
    digitalWrite( 4, LOW );
    digitalWrite( 5, HIGH );
    analogWrite( 9, - power );
    digitalWrite( 7, LOW );
    digitalWrite( 8, HIGH );
  }

}

//倒立安定点を決める
void training() {
  delay (1000);
  for ( i = 0 ; i < 500 ; i++ ) {
    zeroOmegaI = zeroOmegaI + analogRead(A5);
  }
  zeroOmegaI = zeroOmegaI / i;
}

void chkAndCtl() {
  omegaI = analogRead(A5) - zeroOmegaI;
  if  (abs( omegaI ) < 5 ) {
    omegaI = 0;
  }
  recOmegaI[0] = omegaI;
  thetaI = thetaI + omegaI;
  countS = 0;//60
  for ( i = 0 ; i < 10 ; i++ ) {
    if  (abs( recOmegaI[i] ) < 8 ) {
      countS++;
    }
  }
  if ( countS > 9 ) {
    thetaI = 0;
    vE5 = 0;
    xE5 = 0;
    sumPower = 0;
    sumSumP = 0;
  }
  for ( i = 9 ; i > 0 ; i-- ) {
    recOmegaI[ i ] = recOmegaI[ i - 1 ];
  }
  powerScale = (kAngle * thetaI / 200) + (kOmega * omegaI / 78) + (kpower = max (min ( 95 * powerScale / 100 , 255 ) , -255 );
               sumPower = sumPower + power;
               sumSumP = sumSumP + sumPower;
               vE5 = ?? ?
                     xE5 = ?? ?
}  
```



