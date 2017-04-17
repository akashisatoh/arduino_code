#include <Arduino.h>
#include "HydroCtl.h"

HydroCtl::HydroCtl(){
  
}

static void     begin(void){
  
}

static int8_t   turnOnPump(uint8_t  pumpId){
  //ポンプを動かす命令
}
static int8_t   turnOffPump(uint8_t  pumpId){
  //ポンプを止める命令
}
static int8_t   turnOnSolenoid(void){
  //電磁弁
}
static int8_t   turnOffSorenoid(void){
  //電磁弁
}

static void     update(void){
  //現在の状態を更新する
}

static uint16_t getEcValue(void){
  //EC値を取得
}
static float    getWaterTemp(void){
  //水量を取得
}
static float    getTemp(void){
  //温度を取得
}
static float    getHum(void){
  //光量を取得
}

static bool     isEmpty(void){
  //水量が無いことを伝える
}
static bool     isFull(void){
  //水量はOKであることを伝える
}

