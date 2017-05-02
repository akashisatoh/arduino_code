#include <Arduino.h>
#include "HydroCtl.h"
#include <Wire.h>


HydroCtlClass::HydroCtlClass(){
    freq = 0;
    waterTemp = 0;
    waterLevel = 0;
}

static void     begin(void){
  
}

static int8_t   turnOnPump(uint8_t  pumpId){
  //ポンプを動かす命令
  digitalWrite(pumpId, HIGH);
}
static int8_t   turnOffPump(uint8_t  pumpId){
  //ポンプを止める命令
  digitalWrite(pumpId, LOW);
}
static int8_t   turnOnSolenoid(uint8_t solenoidId){
  //電磁弁
  digitalWrite(solenoidId, HIGH);
}
static int8_t   turnOffSorenoid(uint8_t solenoidId){
  //電磁弁
  digitalWrite(solenoidId, LOW);
}

static uint32_t getEcValue(uint8_t data[]){
  //EC値を取得
  
  
}

static float    getWaterTemp(uint8_t data[]){
  //水温を取得
  //waterTemp = data >> 40;
  //waterTemp = data & 0xFFFFFFFF;
  //return waterTemp;
}
static float    getTemp(uint8_t tempId){
  //気温を取得
}
static float    getHum(uint8_t humId){
  //光量を取得
}

static bool     isEmpty(void){
  //水量が無いことを伝える
}
static bool     isFull(void){
  //水量はOKであることを伝える
}

static void     update(uint8_t data[]){
  //現在の状態を更新する
  float temp;
  //temp= getTemp(data);
  //freq = getEcValue(data);
  
}

