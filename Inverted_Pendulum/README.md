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

* ギアボックスを組み立てました。
ギア比はTypeCの 114.7 : 1 回転トルク809gf•cm 回転数115rpm
細かい・複雑・固い・図面分かりにくい・間違えたら面倒、で1時間以上かかった。細かい設計は説明書をみよ。mmで設計を指定してくるが、それに従わないと後悔することになるぞ。  
[ギアボックス組み立て前](pictures/IMG_7443.jpeg)   
[ギアボックス完成](pictures/IMG_7444.jpeg) 

* タイアを組み立てて、ギアとつなげてみました。嬉しい。タイアの匂いがして良いタイアだと思った。  
[タイア組み立て前](pictures/IMG_7445.jpeg)   
[タイア完成](pictures/IMG_7446.jpeg) 

* ユニバーサルプレートに切り込みを入れました。L字アームをくっつけました。  
 [ユニバーサルプレート組み立て前](pictures/IMG_7452.jpeg)   
[ユニバーサルプレート完成](pictures/IMG_7453.jpeg)  

* 電池ボックスを組み立てた。細かい。電池２個×２でスイッチも２個ある。左右スイッチ1つずつつけるということでしょう。  
　[スイッチ組み立て前](pictures/IMG_7454.jpeg)
　[スイッチ組み立て途中](pictures/IMG_7455.jpeg)    
　[スイッチ完成](pictures/IMG_7456.jpeg)  

* ここに来てギアからポロリ。やり直しファック。[ポロリお宝画像はこちら](pictures/IMG_7457.jpeg)  
* ジャイロモジュールの出力をテストしてみた。  

```c  
/* https://www.petitmonte.com/robot/howto_gyro_sensor.html 参照。
  ジャイロセンサの出力をみるスケッチ　*/


void setup() {
  Serial.begin(9600);

}

void loop() {
  // 静止時出力の実測値(本来は1.35V)
  // ※机の上など環境により異なりますので適宜、変更して下さい。
  float base_voltage1 = 1.44;
  float base_voltage2 = 1.44;

  // ジャイロ(G1)
  float voltage = (analogRead(A0) / 1024.0) * 5;
  voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て

  Serial.print("G1:");
  Serial.print(voltage);
  Serial.print("V 角速度:");
  Serial.print((voltage - base_voltage1) / (0.67 / 1000));
  Serial.print(" deg/sec");

  // ジャイロ(G2)
  voltage = (analogRead(A1) / 1024.0) * 5;
  voltage = (float)((int)((voltage) * 100)) / 100; // 小数点第3位以降は切り捨て

  Serial.print(" G2:");
  Serial.print(voltage);
  Serial.print("V 角速度:");
  Serial.print((voltage - base_voltage2) / (0.67 / 1000));
  Serial.print(" deg/sec");
  Serial.println("");
  delay(1000);
}

```  

倒立振子走行用プログラム  

```




