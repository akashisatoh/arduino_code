#include <Arduino.h>
#include "HydroCtl.h"
#include <Wire.h>


HydroCtlClass::HydroCtlClass(int pump1, int pump2, int sole, int temp, int hum, int ill){
    freq = 0;
    waterTemp = 0;
    waterLevel = 0;
    pin_pump1 = pump1;
    pin_pump2 = pump2;
    pin_solenoid = sole;
    pin_temp = temp;
    pin_hum = hum;
    pin_ill = ill;
    pinMode(pin_pump1, OUTPUT);
    pinMode(pin_pump2, OUTPUT);
    pinMode(pin_solenoid, OUTPUT);
}

static void     HydroCtlClass::begin(void){
  
}

static int8_t   HydroCtlClass::turnOnPump(int  pumpId){
  //ポンプを動かす命令
  digitalWrite(pumpId, HIGH);
}
static int8_t   HydroCtlClass::turnOffPump(int  pumpId){
  //ポンプを止める命令
  digitalWrite(pumpId, LOW);
}
static int8_t   HydroCtlClass::turnOnSolenoid(){
  //電磁弁
  digitalWrite(pin_solenoid, HIGH);
}
 int8_t   HydroCtlClass::turnOffSolenoid(){
  //電磁弁
  digitalWrite(pin_solenoid, LOW);
}

 uint32_t HydroCtlClass::getEcValue(uint8_t data[]){
  //EC値を取得
  //I2C

  //まずは周波数を取得
  uint32_t ecValue;
  ecValue = (uint32_t)data[4];
  return ecValue;
}

 float    HydroCtlClass::getWaterTemp(uint8_t data[]){
  //水温を取得
  //I2C
}

void HydroCtlClass::getSensorValues(uint8_t data[]){
  //孫（製品版では子）基盤かI2C通信してデータを取得
  //その後値をそれぞれ取得する
}

int HydroCtlClass::waterEmpty(){
  //水が入っているかどうかを取得
  //I2C
}

static float    HydroCtlClass::getTemp(){
  //気温を取得
  //I2C
}
static float    HydroCtlClass::getHum(){
  //湿度を取得
  //I2C
}
static float    HydroCtlClass::getIll(){
  //照度を取得
  return analogRead(pin_ill);
}

bool     HydroCtlClass::isFull(void){
  //水量はOKであることを伝える
}

bool     HydroCtlClass::isEmpty(void){
  //水量が0であることを伝える
}

static void     HydroCtlClass::update(void){
  //現在の状態を更新する
  
}

