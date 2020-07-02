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
