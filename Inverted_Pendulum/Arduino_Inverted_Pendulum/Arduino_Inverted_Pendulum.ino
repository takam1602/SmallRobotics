2/* "A very easy and simple inverted pendulum balancing robot" You need only half a day to make it, if you have some Materials.
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
