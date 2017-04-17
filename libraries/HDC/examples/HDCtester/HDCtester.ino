// 湿度センサ(HDC1000)から湿度と温度を読み取るサンプル
#include <Wire.h>
#include "HDC.h"

#define HDC1000_ADRS     0x40      // HDC1000のI2Cアドレス

HDC hdc(HDC1000_ID, HDC1000_ADRS) ;// HDC1000ライブラリを生成する

void setup()
{
     int ans ;

     // シリアルモニターの設定
     Serial.begin(9600) ;
     // Ｉ２Ｃの初期化
     Wire.begin() ;                // マスターとする
     delay(3000) ;                 // 3Sしたら開始
     // HDC1000の初期化
     ans = hdc.Init() ;
     if (ans != 0) {
          Serial.print("HDC Initialization abnormal ans=") ;
          Serial.println(ans) ;
     } else Serial.println("HDC Initialization normal !!") ;
}
void loop()
{
     int ans ;

     // HDC1000から湿度と温度を読み取る
     // 読み取った値は、Humi/Temp変数に格納される
     ans = hdc.Read() ;
     if (ans == 0) {
          Serial.print("HDC1000: ") ;
          Serial.print(Humi) ;
          Serial.print("%  ") ;
          Serial.print(Temp) ;
          Serial.println("'C") ;
     } else {
          Serial.print("Failed to read from HDC ans=") ;
          Serial.println(ans) ;
     }
     delay(1000) ;                      // １秒後に繰り返す
}
