/*******************************************************************************
*  HDC - 湿度センサ(HDC1000)用関数ライブラリ                                   *
*                                                                              *
*    HDC     - この関数ライブラリを生成する時の初期化処理                      *
*    Init    - デバイスの初期化を行う処理                                      *
*    Read    - 湿度･温度を読込む処理                                           *
*    Receive - デバイスのレジスターからデータを読込む処理                      *
*    Send    - デバイスのレジスターへデータを書込む処理                        *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   1.00     2015-04-20  きむ茶工房     Create                                 *
* ============================================================================ *
*   Arduino IDE 1.0.5-r2 (Ardino Duemilanove 328/UNO)                          *
*   Arduino IDE 1.7.0    (Arduino Zero Pro)                                    *
*******************************************************************************/
#include <Wire.h>
#include "arduino.h"
#include "HDC.h"

float Humi ;                  // 湿度の値を保存する変数
float Temp ;                  // 温度の値を保存する変数

/*******************************************************************************
*  HDC(id,address)                                                             *
*    この関数ライブラリを生成する時の初期化処理(コンストラクタ)                *
*    id      : デバイスの識別IDを指定します                                    *
*    address : デバイス(スレーブ)のI2Cアドレスを指定します                     *
*******************************************************************************/
HDC::HDC(int id ,int address)
{
     Device_ID = id ;
     Sensor_adrs = address ;
}
/*******************************************************************************
*  ans = Init()                                                                *
*    デバイスの初期化を行う処理                                                *
*    デバイスの動作を確かめる為にデバイスIDのチェックを行います。              *
*    温度(14bit)･湿度(14bit)を個別に読出す様に設定を初期化します。             *
*    設定データを変更する場合は、HDC.hのCONFIG_DT_Hを書き換え変更して下さい。  *
*    ans  : 戻り値、0=正常終了　それ以外I2C通信エラー下記                      *
*                   1=送ろうとしたデータが送信バッファのサイズを超えた         *
*                   2=スレーブ・アドレスを送信し、NACKを受信した               *
*                   3=データ・バイトを送信し、NACKを受信した                   *
*                   4=その他のエラー                                           *
*                   5=データ受信エラー                                         *
*                   6=デバイスのIDチェックエラー                               *
*******************************************************************************/
int HDC::Init(void)
{
     union {
          uint16_t  i ;
          uint8_t   c[2] ;
     } data ;
     int  ans ;

     // 電源投入後15ms待ち
     delay(15) ;
     // デバイスの識別ＩＤをチェックする処理
     ans = Receive(DEVICE_ID_ADRS,data.c) ;
     if (ans == 0) {
          if (data.i == Device_ID) {
               // ＩＤは一致したならデバイスを初期化する処理
               data.c[0] = CONFIG_DT_H ;
               data.c[1] = CONFIG_DT_L ;
               Send(CONFIG_ADRS,data.c) ;
          } else ans = 6 ; // ＩＤが一致しない
     }
     return ans ;
}
/*******************************************************************************
*  ans = Read()                                                                *
*  湿度･温度を読込む処理                                                       *
*  読み込まれた湿度(％)はHumi変数に、温度値(℃)はTemp変数に其々格納されます。  *
*  この処理は約15ms程時間が掛かります。                                        *
*    ans  : 戻り値、0=正常終了　それ以外Init()のans値を参照                    *
*******************************************************************************/
int HDC::Read(void)
{
     union {
          uint16_t  i ;
          uint8_t   c[2] ;
     } data ;
     int ans ;

     // 湿度データを受信する
     ans = Receive(HUMI_ADRS,data.c) ;
     if (ans == 0) {
          Humi = (float)data.i / 65536.0 ;
          Humi = Humi * 100.0 ;
          // 温度データを受信する
          ans = Receive(TEMP_ADRS,data.c) ;
          if (ans == 0) {
               Temp = (float)data.i / 65536.0 ;
               Temp = (Temp * 165.0) - 40.0 ;
          }
     }
     return ans ;
}
/*******************************************************************************
*  ans = Receive(reg_adrs,*data)                                               *
*  デバイスのレジスターからデータを読込む処理                                  *
*    reg_adrs : 読出すデータのレジスターアドレスを指定する                     *
*    *data    : 読出したデータの格納先を指定する(2byte読込む)                  *
*    ans      : 戻り値、0=正常終了　それ以外Init()のans値を参照                *
*******************************************************************************/
int HDC::Receive(char reg_adrs,unsigned char *data)
{
     int ans ;

     Wire.beginTransmission(Sensor_adrs) ;        // 通信の開始
     Wire.write(reg_adrs) ;                       // レジスタアドレスを指定
     ans = Wire.endTransmission() ;               // データの送信と通信の終了
     if (ans == 0) {
          if ( (reg_adrs == TEMP_ADRS) || (reg_adrs == HUMI_ADRS) )  {
               // 温度・湿度の読出しなら変換が完了するまで待つ
               delay(7) ;
          }
          ans = Wire.requestFrom(Sensor_adrs,2) ; // データの受信を行う
          if (ans == 2) {
               data++ ;
               *data = Wire.read() ;              // HIGHバイト読出し
               data-- ;
               *data = Wire.read() ;              // LOWバイト読出し
               ans = 0 ;
          } else ans = 5 ;                        // 受信バイト数がおかしい？
     }
     return ans ;
}
/*******************************************************************************
*  ans = Send(reg_adrs,*data)                                                  *
*  デバイスのレジスターへデータを書込む処理                                    *
*    reg_adrs : 書出すデータのレジスターアドレスを指定する                     *
*    *data    : 書出すデータの格納先を指定する(2byte書込む)                    *
*    ans      : 戻り値、0=正常終了　それ以外Init()のans値を参照                *
*******************************************************************************/
int HDC::Send(char reg_adrs,unsigned char *data)
{
     int  ans , i ;

     Wire.beginTransmission(Sensor_adrs) ;        // 通信の開始
     Wire.write(reg_adrs) ;                       // レジスタのアドレスを通知
     for (i=0 ; i<2 ; i++) {
          Wire.write(*data) ;                     // データを通知
          data++ ;
     }
     ans = Wire.endTransmission() ;               // データの送信と通信の終了
     return ans ;
}
