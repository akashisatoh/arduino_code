/*******************************************************************************
*  HDC.h - 湿度センサ(HDC1000)用関数ライブラリのインクルードファイル           *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   1.00     2015-04-20  きむ茶工房     Create                                 *
* ============================================================================ *
*   Arduino IDE 1.0.5-r2 (Ardino Duemilanove 328/UNO)                          *
*   Arduino IDE 1.7.0    (Arduino Zero Pro)                                    *
*******************************************************************************/
#ifndef HDC_h
#define HDC_h

#include "arduino.h"

#define HDC1000_ID      0x1000     // HDC1000のID

// デバイスのレジスタアドレス
#define DEVICE_ID_ADRS  0xFF       // HDC1000のデバイスID格納アドレス
#define CONFIG_ADRS     0x02       // Configurationレジスタのアドレス
#define TEMP_ADRS       0x00       // 温度読出しのレジスタのアドレス
#define HUMI_ADRS       0x01       // 湿度読出しのレジスタのアドレス

// Configurationレジスタの設定
#define CONFIG_DT_H     0b00000000 // 温度(14bit)･湿度(14bit)個別に読出し
#define CONFIG_DT_L     0b00000000 // 予約の為に全て０

extern float Humi ;                // 湿度の値を保存する変数
extern float Temp ;                // 温度の値を保存する変数

/*******************************************************************************
*	クラスの定義                                                           *
*******************************************************************************/
class HDC
{
  private:
    int Sensor_adrs ;
    int Device_ID ;

  public:
          HDC(int id ,int address) ;
    int   Init(void) ;
    int   Receive(char reg_adrs,unsigned char *data) ;
    int   Send(char reg_adrs,unsigned char *data) ;
    int   Read(void) ;
} ;

#endif
